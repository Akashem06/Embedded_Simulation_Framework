#include "app_callback.h"

#include "app.h"
#include "command_code.h"
#include "json_manager.h"
#include "metadata.h"

std::string projectName = DEFAULT_PROJECT_NAME;
std::string hardwareModel = DEFAULT_HARDWARE_MODEL;

void applicationMessageCallback(Client *client, std::string &message) {
  auto [commandCode, payload] = decodeCommand(message);

  switch (commandCode) {
    case CommandCode::METADATA: {
      /* Future expansion if the server needs to send the client some metadata? */
      break;
    }
    case CommandCode::GPIO_SET_PIN_STATE: {
      clientGpioManager.setGpioPinState(payload);
      break;
    }
    case CommandCode::GPIO_SET_ALL_STATES: {
      clientGpioManager.setGpioAllStates(payload);
      break;
    }
    case CommandCode::GPIO_GET_PIN_STATE: {
      client->sendMessage(clientGpioManager.processGpioPinState(payload));
      break;
    }
    case CommandCode::GPIO_GET_ALL_STATES: {
      client->sendMessage(clientGpioManager.processGpioAllStates());
      break;
    }
    case CommandCode::GPIO_GET_PIN_MODE: {
      client->sendMessage(clientGpioManager.processGpioPinMode(payload));
      break;
    }
    case CommandCode::GPIO_GET_ALL_MODES: {
      client->sendMessage(clientGpioManager.processGpioAllModes());
      break;
    }
    case CommandCode::GPIO_GET_PIN_ALT_FUNCTION: {
      client->sendMessage(clientGpioManager.processGpioPinAltFunction(payload));
      break;
    }
    case CommandCode::GPIO_GET_ALL_ALT_FUNCTIONS: {
      client->sendMessage(clientGpioManager.processGpioAllAltFunctions());
      break;
    }
    default: {
      break;
    }
  }
}

void applicationConnectCallback(Client *client) {
  std::cout << "Connected :-)" << std::endl;

  Datagram::Metadata::Payload initialData = {.projectName = projectName, .projectStatus = "RUNNING", .hardwareModel = hardwareModel};
  Datagram::Metadata projectMetadata(initialData);

  client->sendMessage(projectMetadata.serialize());
}
