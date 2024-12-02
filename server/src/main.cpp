
#include "tcp_server.h"
#include "client_connection.h"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Running Server" << std::endl;
    TCPServer server;
    server.listenClients(12345, [](TCPServer *srv, ClientConnection *src, const std::string &msg) {
        src->sendMessage(msg);
        std::cout << msg << std::endl;
    });

    int foo;
    std::cin >> foo;

    return 0;
}
