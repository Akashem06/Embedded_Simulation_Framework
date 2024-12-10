#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <string>
#include <atomic>
#include <arpa/inet.h>
#include <pthread.h>

/* Forward declaration */
class TCPServer;

class ClientConnection {
    private:
        std::atomic<bool> m_isConnected;
        int m_clientPort;
        int m_clientSocket;
        struct sockaddr_in m_clientAddress;
        pthread_t m_monitorThreadId;
        std::string m_clientName;

        TCPServer *server;

        std::string getClientAddress() const;
    public:
        ClientConnection(TCPServer *server);
        ~ClientConnection();

        bool acceptClient(int listeningSocket);

        void monitorThreadProcedure();
        void sendMessage(const std::string &msg);
        
        std::string getClientName() const;
        void setClientName(const std::string& name);

        int getClientPort() const;
        void setClientPort(int port);

        bool isConnected();
};

#endif
