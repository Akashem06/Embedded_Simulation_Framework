#include "app_terminal.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app.h"
#include "command_code.h"

Terminal::Terminal(TCPServer *server) { m_Server = server; }

std::string Terminal::toLower(const std::string &input) {
  std::string lowered = input;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return lowered;
}

void Terminal::handleGpioCommands(const std::string &action,
                                  std::vector<std::string> &tokens) {
  std::string message;
  if (action == "get_state" && tokens.size() >= 3) {
    message = globalGpioManager.createGpioCommand(CommandCode::GPIO_GET_STATE,
                                                  tokens[2], "");
    std::cout << message << std::endl;
    if (!message.empty()) {
      m_Server->sendMessage(m_targetClient, message);
    } else {
      std::cout << "Invalid command. Example: 'GPIO GET_STATE A12'"
                << std::endl;
    }
    m_targetClient = nullptr;
  } else if (action == "set_state" && tokens.size() >= 4) {
  } else if (action == "gpio_get_alt_function" && tokens.size() >= 3) {
  } else {
    std::cerr << "Unsupported action: " << action << std::endl;
  }
}

void Terminal::parseCommand(std::vector<std::string> &tokens) {
  if (tokens.size() < 3) {
    std::cout << "Invalid command. Format: <interface> <action> <args...>\n";
    return;
  }

  std::string interface = toLower(tokens[0]);
  std::string action = toLower(tokens[1]);

  try {
    if (interface == "gpio") {
      handleGpioCommands(action, tokens);
    } else if (interface == "i2c") {
    } else if (interface == "spi") {
    } else {
      std::cerr << "Unsupported interface: " << interface << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Terminal command error: " << e.what() << std::endl;
  }
}

void Terminal::run() {
  std::string input;

  while (true) {
    std::cout << "Client List:" << std::endl;
    std::cout << "------------" << std::endl;
    m_Server->dumpClientList();
    std::cout << "------------" << std::endl;

    std::cout << "Select Client by Name (Enter to refresh) > ";
    std::getline(std::cin, input);

    input.erase(0, input.find_first_not_of(" \t"));
    input.erase(input.find_last_not_of(" \t") + 1);

    if (toLower(input) == "exit") {
      break;
    }

    m_targetClient = m_Server->getClientByName(input);

    if (m_targetClient == nullptr) {
      std::cout << "Invalid client selection." << std::endl << std::endl;
      continue;
    }
    std::cout << "Selected " << m_targetClient->getClientName() << std::endl
              << std::endl;

    std::cout << "Enter commmand > ";
    std::getline(std::cin, input);

    input.erase(0, input.find_first_not_of(" \t"));
    input.erase(input.find_last_not_of(" \t") + 1);

    if (toLower(input) == "exit") {
      break;
    }

    /**
     * Create tokens out of input string
     * Input = "GPIO GET_STATE A9"
     * tokens = ["GPIO", "GET_STATE", "A9"]
     */
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
      tokens.push_back(token);
    }

    if (!tokens.empty()) {
      parseCommand(tokens);
    }
  }
}
