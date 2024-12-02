#include <iostream>
#include <unistd.h>
#include <string.h>
#include "tcp_server.h"

TCPServer::TCPServer()
{
    isListening = false;
    listenPort = -1;
    pthread_mutex_init(&mutex, nullptr);
}

TCPServer::~TCPServer()
{
    pthread_mutex_destroy(&mutex);
}

void TCPServer::listenThreadProcedure()
{
    socketHandle = socket(AF_INET, SOCK_STREAM, 0);

    if (socketHandle < 0)
    {
        throw "Error creating socket";
    }

    int enable = 1;
    if (setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        throw "Error setting socket option SO_REUSEADDR";
    }
    std::cout << "Creating socket";
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(listenPort);
    serverAddress.sin_addr.s_addr = INADDR_ANY; /* Listen to all addresses */

    if (bind(socketHandle, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        throw "Error binding socket";
    }

    listen(socketHandle, 5);
    isListening = true;

    while (isListening) {
        ClientConnection *conn = new ClientConnection(this);

        if (!conn->acceptServer(socketHandle)) {
            delete conn;
            break;
        }

        std::cerr << "Connection established" << std::endl;

        pthread_mutex_lock(&mutex);
        /* Add to list of connections */
        connections.push_back(conn);
        pthread_mutex_unlock(&mutex);
    }

    isListening = false;
}

void *tcpServer_ListenThreadProcedure(void *param)
{
    TCPServer *server = static_cast<TCPServer *>(param);

    try
    {
        server->listenThreadProcedure();
    }
    catch (...)
    {
        std::cerr << "Listen Thread Error" << std::endl;
    }

    return nullptr;
}

void TCPServer::listenClients(int port, std::function<void(TCPServer *srv, ClientConnection *src, const std::string&)> callback)
{
    if (isListening)
        return;

    this->listenPort = port;
    this->callback = callback;

    if (pthread_create(&listenThread, nullptr, tcpServer_ListenThreadProcedure, this))
    {
        throw "Listen Error";
    }
}

void TCPServer::messageReceived(ClientConnection *src, std::string &msg) {
    callback(this, src, msg);
}

void TCPServer::sendMessage(ClientConnection *dst, const std::string &msg) {
    dst->sendMessage(msg);
}

void TCPServer::stop()
{
}
