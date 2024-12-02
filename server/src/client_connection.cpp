#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "client_connection.h"
#include "tcp_server.h"

ClientConnection::ClientConnection(TCPServer *server) {
    this->server = server;
    isConnected = false;
}

ClientConnection::~ClientConnection() {

}

void ClientConnection::monitorThreadProcedure() {
    const int bufferSize = 2048;
    char buffer[bufferSize + 1];
    int n;

    isConnected = true;
    while (true) {
        n = read(connSocket, &buffer, bufferSize);
        if (n <= 0) {
            break;
        }

        std::string msg(buffer, n);
        server->messageReceived(this, msg);
    }

    close(connSocket);
    isConnected = false;
}

void *clientConnection_MonitorThreadProcedure(void *param) {
    ClientConnection *conn = static_cast<ClientConnection *> (param);

    try {
        conn->monitorThreadProcedure();
    } catch (...) {
        std::cerr << "Error in MonitorThreadProcedure" << std::endl;
    }

    delete conn;
    return nullptr;
}

bool ClientConnection::acceptServer(int listeningSocket) {
    socklen_t clientLength = sizeof(clientAddress);
    connSocket = accept(listeningSocket, (struct sockaddr *) &clientAddress, &clientLength);
    
    if (connSocket < 0) 
        return false;

    if (pthread_create(&monitorThread, nullptr, clientConnection_MonitorThreadProcedure, this) < 0) {
        throw "Error creating monitor thread";
    }

    if (pthread_detach(monitorThread) != 0) {
        throw "Error detatching monitor-thread";
    }

    return true;
}

void ClientConnection::sendMessage(const std::string &msg) {
    if (!isConnected)
        throw "Sending on unconnected socket";
    
    size_t n = write(connSocket, &msg[0], msg.size());

    if (n < msg.size())
        throw "Error sending message";
}
