
#include <iostream>
#include <string>

#include "client_connection.h"
#include "command_code.h"
#include "json_manager.h"
#include "metadata.h"
#include "ntp_server.h"
#include "tcp_server.h"

JSONManager<std::string> globalJSON;

void serverCallback(TCPServer *srv, ClientConnection *src, std::string &msg) {
  auto [commandCode, payload] = decodeCommand(msg);
  switch (commandCode) {
    case CommandCode::METADATA:
      Datagram::Metadata clientMetadata;
      clientMetadata.deserialize(payload);

      if (src->getClientName() != clientMetadata.getProjectName()) {
        srv->updateClientName(src, clientMetadata.getProjectName());
      }

      globalJSON.setProjectValue(src->getClientName(), "Project Name",
                                 clientMetadata.getProjectName());
      globalJSON.setProjectValue(src->getClientName(), "Project Status",
                                 clientMetadata.getProjectStatus());
      globalJSON.setProjectValue(src->getClientName(), "Hardware Model",
                                 clientMetadata.getHardwareModel());
      globalJSON.setProjectValue(
          src->getClientName(), "Project Uptime",
          std::to_string(clientMetadata.getProjectRuntime()));

      break;
  }

  std::cout << src->getClientName() << " received: " << msg << std::endl;
}

int main(int argc, char **argv) {
  std::cout << "Running Server" << std::endl;
  TCPServer tcp_server;
  NTPServer ntp_server;

  tcp_server.listenClients(1024, serverCallback);
  ntp_server.startListening("127.0.0.1", "time.google.com");

  int foo;
  std::cin >> foo;

  return 0;
}
