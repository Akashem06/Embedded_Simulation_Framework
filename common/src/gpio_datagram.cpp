#include <cstring>
#include <iostream>
#include <vector>

#include "gpio_datagram.h"
#include "serialization.h"

namespace Datagram {
std::string Gpio::serialize(const CommandCode &commandCode) const {
  std::string serializedData;

  serializeInteger<uint8_t>(serializedData, static_cast<uint8_t>(m_gpioDatagram.gpioPort));
  serializeInteger<uint16_t>(serializedData, m_gpioDatagram.gpioPin);

  return encodeCommand(commandCode, serializedData);
}

void Gpio::deserialize(std::string &gpioDatagramPayload) {
  if (gpioDatagramPayload.size() < 3U) {
    throw std::runtime_error("Invalid GPIO datagram payload");
  }
  size_t offset = 0;
  
  m_gpioDatagram.gpioPort = static_cast<Port>(deserializeInteger<uint8_t>(gpioDatagramPayload, offset));
  m_gpioDatagram.gpioPin = deserializeInteger<uint16_t>(gpioDatagramPayload, offset);
}

Gpio::Gpio(Payload &data) { m_gpioDatagram = data; }

void Gpio::setGpioPort(const Port &gpioPort) {
  m_gpioDatagram.gpioPort = gpioPort;
}

void Gpio::setGpioPin(const int &gpioPin) { m_gpioDatagram.gpioPin = gpioPin; }

Gpio::Port Gpio::getGpioPort() const { return m_gpioDatagram.gpioPort; }

int Gpio::getGpioPin() const { return m_gpioDatagram.gpioPin; }
}  // namespace Datagram
