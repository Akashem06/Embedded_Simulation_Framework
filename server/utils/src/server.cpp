#include "server.h"

#include <string.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

Server::Server() {
  m_serverListening = false;
  m_listenPort = -1;
  m_listeningSocket = -1;
  m_epollFd = -1;
  pthread_mutex_init(&m_mutex, nullptr);
}

Server::~Server() {
  pthread_mutex_destroy(&m_mutex);
}

void Server::listenNewClientsProcedure() {
  m_listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (m_listeningSocket < 0) {
    throw std::runtime_error("Error creating socket for port " + std::to_string(m_listenPort));
  }

  int enable = 1;
  if (setsockopt(m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
    throw std::runtime_error("Error setting socket option SO_REUSEADDR");
  }
  memset((char *)&m_serverAddress, 0U, sizeof(m_serverAddress));
  m_serverAddress.sin_family = AF_INET;
  m_serverAddress.sin_port = htons(m_listenPort);
  m_serverAddress.sin_addr.s_addr = INADDR_ANY; /* Listen to all addresses */

  if (bind(m_listeningSocket, (struct sockaddr *)&m_serverAddress, sizeof(m_serverAddress)) < 0) {
    throw std::runtime_error("Error binding socket");
  }

  listen(m_listeningSocket, 5);

  while (m_serverListening) {
    ClientConnection *conn = new ClientConnection(this);

    if (!conn->acceptClient(m_listeningSocket)) {
      delete conn;
      break;
    }

    /* Add to the EPOLL list */
    struct epoll_event clientEvent;

    /* Edge-triggered input */
    clientEvent.events = EPOLLIN | EPOLLET;
    clientEvent.data.ptr = conn;

    if (epoll_ctl(m_epollFd, EPOLL_CTL_ADD, conn->getSocketFd(), &clientEvent) < 0) {
      conn->~ClientConnection();
      throw std::runtime_error("Failed to add client connection to EPOLL Interest list");
    }

    if (m_connectCallback) {
      m_connectCallback(this, conn);
    }

    updateClientName(conn, conn->getClientName());
  }

  m_serverListening = false;
}

void Server::epollClientsProcedure() {
  int numBytes = 0;
  int nfds = 0;
  char buffer[MAX_CLIENT_READ_SIZE + 1];

  if (m_epollFd < 0) {
    throw std::runtime_error("Invalid epoll FD");
    return;
  }

  while (m_serverListening) {
    nfds = epoll_wait(m_epollFd, m_epollEvents, MAX_SERVER_EPOLL_EVENTS, -1);

    if (nfds < 0) {
      throw std::runtime_error("EPOLL wait failed");
      continue;
    }

    for (int i = 0; i < nfds; i++) {
      ClientConnection *client = static_cast<ClientConnection *>(m_epollEvents[i].data.ptr);

      if (m_epollEvents[i].events & EPOLLIN) {
        numBytes = read(client->getSocketFd(), buffer, MAX_CLIENT_READ_SIZE);

        if (numBytes < 0) {
          throw std::runtime_error("EPOLL Read failed");
          continue;
        }

        buffer[numBytes] = '\0';
        std::string msg(buffer, numBytes);
        messageReceived(client, msg);
      }
    }
  }
}

void *listenNewClientsWrapper(void *param) {
  Server *server = static_cast<Server *>(param);

  try {
    server->listenNewClientsProcedure();
  } catch (std::exception &e) {
    m_serverListening = false;
    std::cerr << "Listen Thread Error: " << e.what() << std::endl;
  }

  return nullptr;
}

void *epollClientsWrapper(void *param) {
  Server *server = static_cast<Server *>(param);
  try {
    server->epollClientsProcedure();
  } catch (std::exception &e) {
    m_serverListening = false;
    std::cerr << "EPOLL Clients Error: " << e.what() << std::endl;
  }
  return nullptr;
}

void Server::listenClients(int port, messageCallback messageCallback, connectCallback connectCallback) {
  if (m_serverListening)
    return;

  m_epollFd = epoll_create1(0U);
  if (m_epollFd < 0) {
    throw std::runtime_error("Failed to create EPOLL FD");
  }

  m_listenPort = port;
  m_messageCallback = messageCallback;
  m_connectCallback = connectCallback;
  m_serverListening = true;

  if (pthread_create(&m_listenNewClientsId, nullptr, listenNewClientsWrapper, this)) {
    throw std::runtime_error("Listen new clients Error");
  }

  if (pthread_create(&m_epollClientsId, nullptr, epollClientsWrapper, this)) {
    throw std::runtime_error("EPOLL Clients Error");
  }
}

void Server::removeClient(ClientConnection *conn) {
  pthread_mutex_lock(&m_mutex);
  if (conn) {
    std::cerr << "Removed client: " << conn->getClientName() << std::endl;
    epoll_ctl(m_epollFd, EPOLL_CTL_DEL, conn->getSocketFd(), nullptr);
    m_connections.erase(conn->getClientName());
    conn->~ClientConnection();
  }
  pthread_mutex_unlock(&m_mutex);
}

void Server::updateClientName(ClientConnection *conn, std::string newName) {
  pthread_mutex_lock(&m_mutex);
  std::string oldClientName = conn->getClientName();

  if (!oldClientName.empty()) {
    m_connections.erase(oldClientName);
  }

  conn->setClientName(newName);

  /* Handle potential client duplicates */
  std::string clientName = newName;
  unsigned int clientDuplicateCount = 1U;
  while (m_connections.count(clientName)) {
    clientName = newName + " (" + std::to_string(clientDuplicateCount) + ")";
    clientDuplicateCount++;
  }

  m_connections[clientName] = conn;
  conn->setClientName(clientName);
  pthread_mutex_unlock(&m_mutex);
}

void Server::messageReceived(ClientConnection *src, std::string &message) {
  m_messageCallback(this, src, message);
}

void Server::sendMessage(ClientConnection *dst, const std::string &message) {
  dst->sendMessage(message);
}

void Server::broadcastMessage(const std::string &message) {
  pthread_mutex_lock(&m_mutex);
  for (auto &pair : m_connections) {
    if (pair.second->isConnected()) {
      pair.second->sendMessage(message);
    }
  }
  pthread_mutex_unlock(&m_mutex);
}

ClientConnection *Server::getClientByName(std::string &clientName) {
  pthread_mutex_lock(&m_mutex);
  if (m_connections.count(clientName)) {
    pthread_mutex_unlock(&m_mutex);
    return m_connections[clientName];
  }
  pthread_mutex_unlock(&m_mutex);
  return nullptr;
}

void Server::dumpClientList() {
  for (auto &pair : m_connections) {
    if (pair.second->isConnected()) {
      std::cout << pair.first << std::endl;
    }
  }
}

void Server::stop() {}
