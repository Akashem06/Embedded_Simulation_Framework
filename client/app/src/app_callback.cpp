#include "app_callback.h"

#include "app.h"
#include "command_code.h"
#include "json_manager.h"

std::string applicationMessageCallback(TCPClient *client, std::string &message) {
  auto [commandCode, payload] = decodeCommand(message);
  switch (commandCode) {
    case CommandCode::METADATA: {
      // TBD. Debating if server will send meta data to client?
      break;
    }
    case CommandCode::GPIO_GET_PIN_STATE: {
      client->sendMessage(clientGpioManager.processGpioPinState(payload));
      break;
    }
    case CommandCode::GPIO_GET_ALL_STATES: {
      client->sendMessage(clientGpioManager.processGpioAllStates(payload));
      break;
    }
    case CommandCode::GPIO_GET_PIN_MODE: {
      client->sendMessage(clientGpioManager.processGpioPinMode(payload));
      break;
    }
    case CommandCode::GPIO_GET_ALL_MODES: {
      client->sendMessage(clientGpioManager.processGpioAllModes(payload));
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
