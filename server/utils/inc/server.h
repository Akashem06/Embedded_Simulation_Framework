#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <pthread.h>
#include <sys/epoll.h>

#include <atomic>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "client_connection.h"

class Server {
 private:
  static const constexpr unsigned int MAX_SERVER_EPOLL_EVENTS = 64U;
  static const constexpr size_t MAX_CLIENT_READ_SIZE = 256U;

  using messageCallback = std::function<void(Server *srv, ClientConnection *src, std::string &)>;
  using connectCallback = std::function<void(Server *srv, ClientConnection *src)>;

  pthread_mutex_t m_mutex;
  messageCallback m_messageCallback;
  connectCallback m_connectCallback;

  std::unordered_map<std::string, ClientConnection *> m_connections;

  std::atomic<bool> m_serverListening;
  int m_listenPort;
  int m_listeningSocket;

  /* EPOLL */
  int m_epollFd;
  struct epoll_event m_epollEvents[MAX_SERVER_EPOLL_EVENTS];

  pthread_t m_listenNewClientsId;
  pthread_t m_epollClientsId;
  struct sockaddr_in m_serverAddress;

 public:
  Server();
  ~Server();

  void listenNewClientsProcedure();
  void epollClientsProcedure();

  void stop();
  void listenClients(int port, messageCallback messageCallback, connectCallback connectCallback);
  void messageReceived(ClientConnection *src, std::string &message);

  void sendMessage(ClientConnection *dst, const std::string &message);
  void broadcastMessage(const std::string &message);
  void updateClientName(ClientConnection *conn, std::string newName);
  void removeClient(ClientConnection *conn);
  ClientConnection *getClientByName(std::string &clientName);

  void dumpClientList();
};

#endif
