
#include <string>
#include <iostream>

#include "tcp_server.h"
#include "client_connection.h"

#include "command_code.h"
#include "metadata.h"
#include "json_manager.h"

JSONManager<std::string> globalJSON;

void serverCallback(TCPServer *srv, ClientConnection *src, std::string &msg) {
    auto [commandCode, payload] = decodeCommand(msg);
    switch (commandCode) {
        case CommandCode::METADATA:
            Metadata clientMetadata;
            clientMetadata.deserialize(payload);

            if (src->getClientName() != clientMetadata.getProjectName()) {
                srv->updateClientName(src, clientMetadata.getProjectName());
            }
            globalJSON.setProjectValue(src->getClientName(), "Project Status", clientMetadata.getProjectStatus());
            
            break;
    }

    std::cout << src->getClientName() << " received: " << msg << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "Running Server" << std::endl;
    TCPServer server;
    server.listenClients(1024, serverCallback);

    int foo;
    std::cin >> foo;

    return 0;
}
