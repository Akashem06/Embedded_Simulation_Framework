#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <string>
#include <arpa/inet.h>
#include <pthread.h>

/* Forward declaration */
class TCPServer;

class ClientConnection {
    private:
        bool isConnected;
        int connSocket;
        struct sockaddr_in clientAddress;
        pthread_t monitorThread;

        TCPServer *server;
    public:
        ClientConnection(TCPServer *server);
        ~ClientConnection();

        bool acceptServer(int listeningSocket);
        void send(const std::string &msg);

        void monitorThreadProcedure();
        void sendMessage(const std::string &msg);
};

#endif
