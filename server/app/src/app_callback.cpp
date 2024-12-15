#include "app_callback.h"

#include <iostream>

#include "app.h"
#include "command_code.h"
#include "gpio_datagram.h"
#include "i2c_datagram.h"
#include "json_manager.h"
#include "metadata.h"
#include "spi_datagram.h"

void applicationCallback(TCPServer *srv, ClientConnection *src, std::string &message) {
  std::string clientName = src->getClientName();

  auto [commandCode, payload] = decodeCommand(message);
  switch (commandCode) {
    case CommandCode::METADATA: {
      Datagram::Metadata clientMetadata;
      clientMetadata.deserialize(payload);

      if (src->getClientName() != clientMetadata.getProjectName()) {
        srv->updateClientName(src, clientMetadata.getProjectName());
      }

      globalJSON.setProjectValue(src->getClientName(), "Project Name", src->getClientName()); /* Get the updated name if there are duplicates */
      globalJSON.setProjectValue(src->getClientName(), "Project Status", clientMetadata.getProjectStatus());
      globalJSON.setProjectValue(src->getClientName(), "Hardware Model", clientMetadata.getHardwareModel());
      globalJSON.setProjectValue(src->getClientName(), "Project Uptime", std::to_string(clientMetadata.getProjectRuntime()));

      break;
    }
    case CommandCode::GPIO_GET_PIN_STATE: {
      serverGpioManager.updateGpioPinState(clientName, payload);
      break;
    }
    case CommandCode::GPIO_GET_ALL_STATES: {
      serverGpioManager.updateGpioAllStates(clientName, payload);
      break;
    }
    case CommandCode::GPIO_GET_PIN_MODE: {
      serverGpioManager.updateGpioPinMode(clientName, payload);
      break;
    }
    case CommandCode::GPIO_GET_ALL_MODES: {
      serverGpioManager.updateGpioAllModes(clientName, payload);
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