#include "gpio_manager.h"

#include <cstdint>

#include "app.h"
#include "command_code.h"

const char *gpioPortNames[] = {
    "A", /* GPIO_PORT_A */
    "B", /* GPIO_PORT_B */
    "C", /* GPIO_PORT_C */
    "D", /* GPIO_PORT_D */
    "E", /* GPIO_PORT_E */
    "H", /* GPIO_PORT_H */
};

void GpioManager::loadGpioStates(std::string &projectName) {
  m_gpioStates = globalJSON.getProjectValue<
      std::unordered_map<std::string, Datagram::Gpio::State>>(projectName,
                                                              "Gpio States");
}

void GpioManager::loadGpioModes(std::string &projectName) {
  m_gpioModes = globalJSON.getProjectValue<
      std::unordered_map<std::string, Datagram::Gpio::Mode>>(projectName,
                                                             "Gpio Modes");
}

void GpioManager::updateGpioStates(std::string &projectName,
                                   std::string &payload) {
  loadGpioStates(projectName);

  m_gpioDatagram.deserialize(payload);

  std::string key =
      gpioPortNames[static_cast<uint8_t>(m_gpioDatagram.getGpioPort())];
  key = key + std::to_string(m_gpioDatagram.getGpioPin());
  m_gpioStates[key] =
      static_cast<Datagram::Gpio::State>(m_gpioDatagram.getData());

  globalJSON.setProjectValue(projectName, "Gpio States", m_gpioStates);
}

void GpioManager::updateGpioModes(std::string &projectName,
                                  std::string &payload) {}

std::string GpioManager::createGpioCommand(CommandCode commandCode,
                                           std::string &gpioPortPin,
                                           std::string data) {
  if (gpioPortPin.empty() || gpioPortPin.size() < 2) {
    return "";
  }

  Datagram::Gpio::Port port =
      static_cast<Datagram::Gpio::Port>(gpioPortPin[0] - 'A');
  int pin = std::stoi(gpioPortPin.substr(1));

  m_gpioDatagram.setGpioPort(port);
  m_gpioDatagram.setGpioPin(pin);

  if (commandCode == CommandCode::GPIO_SET_STATE) {
    if (data == "HIGH") {
      m_gpioDatagram.setData(
          static_cast<int>(Datagram::Gpio::State::GPIO_STATE_HIGH));
    } else if (data == "LOW") {
      m_gpioDatagram.setData(
          static_cast<int>(Datagram::Gpio::State::GPIO_STATE_LOW));
    } else {
      return "";
    }
  } else {
    m_gpioDatagram.setData(GPIO_DATAGRAM_NO_DATA_FLAG);
  }

  return m_gpioDatagram.serialize(commandCode);
}
