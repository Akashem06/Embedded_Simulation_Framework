#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <vector>
#include <functional>
#include <arpa/inet.h>
#include <pthread.h>
#include "client_connection.h"

class TCPServer {
    private:
        std::vector <ClientConnection *> connections;
        volatile bool isListening;
        int listenPort;
        pthread_t listenThread;
        std::function<void(TCPServer *srv, ClientConnection *src, const std::string&)> callback;

        /* Sockets */
        struct sockaddr_in serverAddress;
        int socketHandle;

        pthread_mutex_t mutex;
    public:
        TCPServer();
        ~TCPServer();

        void listenClients(int port, std::function<void(TCPServer *srv, ClientConnection *src, const std::string&)> callback);
        void listenThreadProcedure();
        void stop();
        void sendMessage(ClientConnection *dst, const std::string &msg);

        void messageReceived(ClientConnection *src, std::string &msg);
};

#endif
