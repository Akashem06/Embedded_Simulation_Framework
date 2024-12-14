#include "gpio_manager.h"

#include <cstdint>

#include "app.h"
#include "command_code.h"

const char *gpioPortNames[] = {
    "A", /* GPIO_PORT_A */
    "B", /* GPIO_PORT_B */
};

void GpioManager::loadGpioStates(std::string &projectName) {
  m_gpioStates = globalJSON.getProjectValue<std::unordered_map<std::string, std::string>>(projectName, "Gpio States");
}

void GpioManager::loadGpioModes(std::string &projectName) {
  m_gpioModes = globalJSON.getProjectValue<std::unordered_map<std::string, Datagram::Gpio::Mode>>(projectName, "Gpio Modes");
}

void GpioManager::updateGpioPinState(std::string &projectName, std::string &payload) {
  loadGpioStates(projectName);

  m_gpioDatagram.deserialize(payload);

  std::string key = gpioPortNames[static_cast<uint8_t>(m_gpioDatagram.getGpioPort())];
  key += std::to_string(m_gpioDatagram.getGpioPin());
  Datagram::Gpio::State receivedPinState = static_cast<Datagram::Gpio::State>(m_gpioDatagram.getData());

  if (receivedPinState == Datagram::Gpio::State::GPIO_STATE_HIGH) {
    m_gpioStates[key] = "HIGH";
  } else if (receivedPinState == Datagram::Gpio::State::GPIO_STATE_LOW) {
    m_gpioStates[key] = "LOW";
  } else {
    m_gpioStates[key] = "INVALID";
  }

  globalJSON.setProjectValue(projectName, "Gpio States", m_gpioStates);
}

void GpioManager::updateGpioAllStates(std::string &projectName, std::string &payload) {
  loadGpioStates(projectName);

  m_gpioDatagram.deserialize(payload);

  uint32_t receivedData = static_cast<uint32_t>(m_gpioDatagram.getData());

  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * static_cast<uint8_t>(Datagram::Gpio::PINS_PER_PORT); i++) {
    bool pinState = (receivedData & (1U << i)) != 0;
    std::string key = gpioPortNames[i / Datagram::Gpio::PINS_PER_PORT];
    key += std::to_string(i % Datagram::Gpio::PINS_PER_PORT);

    if (pinState) {
      m_gpioStates[key] = "HIGH";
    } else {
      m_gpioStates[key] = "LOW";
    }
  }

  globalJSON.setProjectValue(projectName, "Gpio States", m_gpioStates);
}

void GpioManager::updateGpioModes(std::string &projectName, std::string &payload) {}

std::string GpioManager::createGpioCommand(CommandCode commandCode, std::string &gpioPortPin, std::string data) {
  try {
    switch (commandCode) {
      case CommandCode::GPIO_GET_PIN_STATE: {
        if (gpioPortPin.empty() || gpioPortPin.size() < 2) {
          throw std::runtime_error(
              "Invalid format for port/pin specification. Good examples: 'A9' "
              "'A12' 'B13'");
        }

        Datagram::Gpio::Port port = static_cast<Datagram::Gpio::Port>(gpioPortPin[0] - 'A');
        uint8_t pin = static_cast<uint8_t>(std::stoi(gpioPortPin.substr(1)));

        if (port >= Datagram::Gpio::Port::NUM_GPIO_PORTS) {
          throw std::runtime_error("Invalid selection for Gpio ports. Expected: A or B");
        }

        if (pin >= Datagram::Gpio::PINS_PER_PORT) {
          throw std::runtime_error("Exceeded maximum number of Gpio pins: " + std::to_string(static_cast<int>(Datagram::Gpio::PINS_PER_PORT)));
        }

        m_gpioDatagram.setGpioPort(port);
        m_gpioDatagram.setGpioPin(pin);
        m_gpioDatagram.setData(UINT32_MAX);
        break;
      }

      case CommandCode::GPIO_GET_ALL_STATES: {
        m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
        m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);
        m_gpioDatagram.setData(UINT32_MAX);
        break;
      }

      case CommandCode::GPIO_SET_STATE: {
        if (data == "HIGH") {
          m_gpioDatagram.setData(static_cast<uint8_t>(Datagram::Gpio::State::GPIO_STATE_HIGH));
        } else if (data == "LOW") {
          m_gpioDatagram.setData(static_cast<uint8_t>(Datagram::Gpio::State::GPIO_STATE_LOW));
        } else {
          throw std::runtime_error("Invalid Gpio state: " + data);
        }

        break;
      }

      default: {
        throw std::runtime_error("Invalid command code");
        break;
      }
    }

    return m_gpioDatagram.serialize(commandCode);

  } catch (std::exception &e) {
    std::cerr << "Gpio Manager error: " << e.what() << std::endl;
  }
  return "";
}
