#include "gpio_datagram.h"

#include <cstring>
#include <iostream>
#include <vector>

namespace Datagram {
std::string Gpio::serialize(const CommandCode &commandCode) const {
  std::string serializedData;

  uint8_t portValue = static_cast<uint8_t>(m_gpioDatagram.gpioPort);
  serializedData.push_back(portValue);

  uint16_t pinValue = static_cast<uint16_t>(m_gpioDatagram.gpioPin);
  serializedData.append(reinterpret_cast<const char *>(&pinValue),
                        sizeof(pinValue));

  return encodeCommand(commandCode, serializedData);
}

void Gpio::deserialize(std::string &gpioDatagramPayload) {
  if (gpioDatagramPayload.size() < 3) {
    throw std::runtime_error("Invalid GPIO datagram payload");
  }

  uint8_t portValue = static_cast<uint8_t>(gpioDatagramPayload[0]);
  m_gpioDatagram.gpioPort = static_cast<Port>(portValue);

  uint16_t pinValue;
  std::memcpy(&pinValue, gpioDatagramPayload.data() + 1, sizeof(pinValue));
  m_gpioDatagram.gpioPin = static_cast<int>(pinValue);
}

Gpio::Gpio(Payload &data) { m_gpioDatagram = data; }

void Gpio::setGpioPort(const Port &gpioPort) {
  m_gpioDatagram.gpioPort = gpioPort;
}

void Gpio::setGpioPin(const int &gpioPin) { m_gpioDatagram.gpioPin = gpioPin; }

Gpio::Port Gpio::getGpioPort() const { return m_gpioDatagram.gpioPort; }

int Gpio::getGpioPin() const { return m_gpioDatagram.gpioPin; }
}  // namespace Datagram
