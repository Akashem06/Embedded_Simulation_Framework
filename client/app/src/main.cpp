#include <iostream>

#include "metadata.h"
#include "ntp_client.h"
#include "tcp_client.h"

std::string messageCallback(TCPClient *client, const std::string &message) {
  std::cout << "Received message: " << message << std::endl;
}

void connectCallback(TCPClient *client) {
  Datagram::Metadata::Payload initialData = {
      .projectName = "SAMPLE PROJECT",
      .projectStatus = "RUNNING",
      .hardwareModel = "MS16.0.0",
      .projectRuntime = 0,
  };

  Datagram::Metadata projectMetadata(initialData);

  client->sendMessage(projectMetadata.serialize());
}

int main(int argc, char **argv) {
  std::cout << "Running Client" << std::endl;

  NTPClient ntpClient;
  TCPClient serverClient("127.0.0.1", 1024, messageCallback, connectCallback);

  ntpClient.startSynchronization("127.0.0.1");
  serverClient.connectServer();

  int n;
  std::cin >> n;

  return 0;
}
