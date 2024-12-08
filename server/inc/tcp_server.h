#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <atomic>
#include <memory>
#include <arpa/inet.h>
#include <pthread.h>
#include "client_connection.h"

class TCPServer {
    private:
        using serverCallback = std::function<void(TCPServer *srv, ClientConnection *src, std::string&)>;
        pthread_mutex_t m_mutex;
        serverCallback m_serverCallback;
        std::unordered_map<std::string, ClientConnection *> m_connections;

        std::atomic<bool> m_isListening;
        int m_listenPort;
        int m_listeningSocket;

        pthread_t m_listenThreadId;
        struct sockaddr_in m_serverAddress;
    public:
        TCPServer();
        ~TCPServer();

        void listenThreadProcedure();

        void stop();
        void listenClients(int port, serverCallback callback);
        void messageReceived(ClientConnection *src, std::string &msg);
        void sendMessage(ClientConnection *dst, const std::string &msg);
        void broadcastMessage(const std::string &msg);
        void updateClientName(ClientConnection *conn, std::string newName);
        void removeClient(ClientConnection *conn);
};

#endif
