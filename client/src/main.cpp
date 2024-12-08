#include <iostream>
#include "tcp_client.h"
#include "metadata.h"

std::string messageCallback(TCPClient *client, const std::string &message) {
    std::cout << "Received message: " << message << std::endl;
}

void connectCallback(TCPClient *client) {
    Metadata::Payload initialData = {
        .projectName    = "SAMPLE PROJECT",
        .projectStatus  = "RUNNING",
        .hardwareModel  = "MS16.0.0",
        .projectRuntime = 0,
    };

    Metadata projectMetadata(initialData);

    client->sendMessage(projectMetadata.serialize());
}

int main(int argc, char **argv)
{
    std::cout << "Running Client" << std::endl;

    TCPClient client("127.0.0.1", 1024, messageCallback, connectCallback);
    client.connectServer();
    
    int n;
    std::cin >> n;

    return 0;
}
