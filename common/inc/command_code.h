#ifndef COMMAND_CODE_H
#define COMMAND_CODE_H

#include <string>

enum class CommandCode : uint8_t {
    METADATA,
    NUM_COMMAND_CODES
};

std::string encodeCommand(const CommandCode commandCode, std::string &msg);
std::pair<CommandCode, std::string> decodeCommand(std::string &msg);

#endif
