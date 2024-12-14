#ifndef COMMAND_CODE_H
#define COMMAND_CODE_H

#include <string>

enum class CommandCode {
  /* MISC Commands */
  METADATA,

  /* GPIO Commands */
  GPIO_SET_STATE,
  GPIO_GET_STATE,
  GPIO_GET_MODE,
  GPIO_GET_ALT_FUNCTION,

  /* I2C Commands */

  /* SPI Commands */

  /* UART Commands */

  /* FLASH Commands */

  NUM_COMMAND_CODES
};

std::string encodeCommand(const CommandCode commandCode, std::string &message);
std::pair<CommandCode, std::string> decodeCommand(std::string &message);

#endif
