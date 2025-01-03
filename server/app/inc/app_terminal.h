#ifndef APP_TERMINAL_H
#define APP_TERMINAL_H

#include "client_connection.h"
#include "server.h"
class Terminal {
 private:
  Server *m_Server;
  ClientConnection *m_targetClient;

  std::string toLower(const std::string &input);

  void handleGpioCommands(const std::string &action, std::vector<std::string> &tokens);
  void parseCommand(std::vector<std::string> &tokens);

 public:
  Terminal(Server *server);

  void run();
};

#endif
