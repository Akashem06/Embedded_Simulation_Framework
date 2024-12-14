#include "app_callback.h"

#include "app.h"
#include "command_code.h"
#include "json_manager.h"

std::string applicationMessageCallback(TCPClient *client,
                                       std::string &message) {
  auto [commandCode, payload] = decodeCommand(message);
  switch (commandCode) {
    case CommandCode::METADATA: {
      // TBD. Debating if server will send meta data to client?
      break;
    }
    case CommandCode::GPIO_GET_STATE: {
      client->sendMessage(clientGpioManager.processGpioState(payload));
      break;
    }
    case CommandCode::GPIO_GET_MODE: {
      break;
    }
    case CommandCode::GPIO_GET_ALT_FUNCTION: {
      break;
    }
    default: {
      break;
    }
  }
}
