#include "command_code.h"

#include <iostream>

std::string encodeCommand(const CommandCode commandCode, std::string &msg) {
  return std::to_string(static_cast<uint8_t>(commandCode)) + '|' + msg;
}

std::pair<CommandCode, std::string> decodeCommand(std::string &msg) {
  size_t delimPosition = msg.find('|');

  if (delimPosition == std::string::npos) {
    throw std::runtime_error("Invalid command format");
  }

  uint8_t commandCodeValue = std::stoi(msg.substr(0, delimPosition));

  if (commandCodeValue > static_cast<uint8_t>(CommandCode::NUM_COMMAND_CODES)) {
    throw std::runtime_error("CommandCode out of valid range");
  }

  CommandCode commandCode = static_cast<CommandCode>(commandCodeValue);

  std::string payload = msg.substr(delimPosition + 1);

  return {commandCode, payload};
}
