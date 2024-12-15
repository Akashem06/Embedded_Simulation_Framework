#include "gpio_manager.h"

#include <cstdint>

#include "app.h"
#include "command_code.h"

#define PIN_STATE_KEY "State"
#define PIN_MODE_KEY "Mode"
#define PIN_ALT_FUNC_KEY "Alternate Function"

const char *gpioPortNames[] = {
    "A", /* GPIO_PORT_A */
    "B", /* GPIO_PORT_B */
};

std::string GpioManager::stringifyPinMode(Datagram::Gpio::Mode mode) {
  std::string result = "";

  switch (mode) {
    case Datagram::Gpio::Mode::GPIO_ANALOG: {
      result = "Analog";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_INPUT_FLOATING: {
      result = "Floating Input";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_INPUT_PULL_DOWN: {
      result = "Pull-down Input";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_INPUT_PULL_UP: {
      result = "Pull-up Input";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_OUTPUT_OPEN_DRAIN: {
      result = "Open-drain Output";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_OUTPUT_PUSH_PULL: {
      result = "Push-pull Output";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_ALFTN_OPEN_DRAIN: {
      result = "Open-drain Alternate Function";
      break;
    }
    case Datagram::Gpio::Mode::GPIO_ALTFN_PUSH_PULL: {
      result = "Push-pull Alternate Function";
      break;
    }
    default: {
      result = "Invalid Mode";
      break;
    }
  }

  return result;
}

void GpioManager::loadGpioInfo(std::string &projectName) {
  m_gpioInfo = globalJSON.getProjectValue<std::unordered_map<std::string, GpioManager::PinInfo>>(projectName, "Gpio Info");
}

void GpioManager::saveGpioInfo(std::string &projectName) {
  globalJSON.setProjectValue(projectName, "Gpio Info", m_gpioInfo);

  /* Upon save, clear the memory */
  m_gpioInfo.clear();
}

void GpioManager::updateGpioPinState(std::string &projectName, std::string &payload) {
  loadGpioInfo(projectName);

  m_gpioDatagram.deserialize(payload);

  std::string key = gpioPortNames[static_cast<uint8_t>(m_gpioDatagram.getGpioPort())];
  key += std::to_string(m_gpioDatagram.getGpioPin());
  const uint8_t *receivedData = m_gpioDatagram.getBuffer();

  if (static_cast<Datagram::Gpio::State>(receivedData[0U]) == Datagram::Gpio::State::GPIO_STATE_HIGH) {
    m_gpioInfo[key][PIN_STATE_KEY] = "HIGH";
  } else if (static_cast<Datagram::Gpio::State>(receivedData[0U]) == Datagram::Gpio::State::GPIO_STATE_LOW) {
    m_gpioInfo[key][PIN_STATE_KEY] = "LOW";
  } else {
    m_gpioInfo[key][PIN_STATE_KEY] = "INVALID";
  }

  saveGpioInfo(projectName);
}

void GpioManager::updateGpioAllStates(std::string &projectName, std::string &payload) {
  loadGpioInfo(projectName);

  m_gpioDatagram.deserialize(payload);

  const uint8_t *receivedData = m_gpioDatagram.getBuffer();

  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * static_cast<uint8_t>(Datagram::Gpio::PINS_PER_PORT); i++) {
    size_t blockIndex = i / 8U;
    size_t bitPosition = i % 8U;
    bool pinState = (receivedData[blockIndex] & (1U << bitPosition)) != 0;
    std::string key = gpioPortNames[i / Datagram::Gpio::PINS_PER_PORT];
    key += std::to_string(i % Datagram::Gpio::PINS_PER_PORT);

    if (pinState) {
      m_gpioInfo[key][PIN_STATE_KEY] = "HIGH";
    } else {
      m_gpioInfo[key][PIN_STATE_KEY] = "LOW";
    }
  }

  saveGpioInfo(projectName);
}

void GpioManager::updateGpioPinMode(std::string &projectName, std::string &payload) {
  loadGpioInfo(projectName);

  m_gpioDatagram.deserialize(payload);

  std::string key = gpioPortNames[static_cast<uint8_t>(m_gpioDatagram.getGpioPort())];
  key += std::to_string(m_gpioDatagram.getGpioPin());

  const uint8_t *receivedData = m_gpioDatagram.getBuffer();

  m_gpioInfo[key][PIN_MODE_KEY] = stringifyPinMode(static_cast<Datagram::Gpio::Mode>(receivedData[0U]));

  saveGpioInfo(projectName);
}

void GpioManager::updateGpioAllModes(std::string &projectName, std::string &payload) {
  loadGpioInfo(projectName);

  m_gpioDatagram.deserialize(payload);

  const uint32_t *receivedData = reinterpret_cast<const uint32_t *>(m_gpioDatagram.getBuffer());

  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * static_cast<uint8_t>(Datagram::Gpio::PINS_PER_PORT); i++) {
    size_t blockIndex = (i / 8U);     /* 4 bits per pin so there is only 8 pins per block */
    size_t bitOffset = (i % 8U) * 4U; /* Multiply by 4 because each each mode is 4 bit */

    uint8_t pinMode = (receivedData[blockIndex] >> bitOffset) & 0x0F;

    std::string key = gpioPortNames[i / Datagram::Gpio::PINS_PER_PORT];
    key += std::to_string(i % Datagram::Gpio::PINS_PER_PORT);

    m_gpioInfo[key][PIN_MODE_KEY] = stringifyPinMode(static_cast<Datagram::Gpio::Mode>(pinMode));
  }

  saveGpioInfo(projectName);
}

std::string GpioManager::createGpioCommand(CommandCode commandCode, std::string &gpioPortPin, std::string data) {
  try {
    switch (commandCode) {
      case CommandCode::GPIO_GET_PIN_MODE:
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
        m_gpioDatagram.setBuffer(nullptr, 0U);
        break;
      }

      case CommandCode::GPIO_GET_ALL_MODES:
      case CommandCode::GPIO_GET_ALL_STATES: {
        m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
        m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);
        m_gpioDatagram.setBuffer(nullptr, 0U);
        break;
      }

      case CommandCode::GPIO_SET_STATE: {
        uint8_t pinState = static_cast<uint8_t>(Datagram::Gpio::State::GPIO_STATE_LOW);
        if (data == "HIGH") {
          pinState = static_cast<uint8_t>(Datagram::Gpio::State::GPIO_STATE_HIGH);
        } else if (data == "LOW") {
          pinState = static_cast<uint8_t>(Datagram::Gpio::State::GPIO_STATE_LOW);
        } else {
          throw std::runtime_error("Invalid Gpio state: " + data);
        }

        m_gpioDatagram.setBuffer(&pinState, sizeof(pinState));

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
