#ifndef GPIO_DATAGRAM_H
#define GPIO_DATAGRAM_H

#include <cstdint>
#include <string>

#include "command_code.h"

namespace Datagram {
class Gpio {
 public:
  static const constexpr uint8_t PINS_PER_PORT = 16U;

  enum class Port { GPIO_PORT_A = 0, GPIO_PORT_B, NUM_GPIO_PORTS };

  enum class State {
    GPIO_STATE_LOW = 0,
    GPIO_STATE_HIGH,
  };

  enum class Mode {
    GPIO_ANALOG = 0,
    GPIO_INPUT_FLOATING,
    GPIO_INPUT_PULL_DOWN,
    GPIO_INPUT_PULL_UP,
    GPIO_OUTPUT_OPEN_DRAIN,
    GPIO_OUTPUT_PUSH_PULL,
    GPIO_ALFTN_OPEN_DRAIN,
    GPIO_ALTFN_PUSH_PULL,
    NUM_GPIO_MODES,
  };

  static constexpr size_t GPIO_MAX_BUFFER_SIZE = PINS_PER_PORT * static_cast<uint8_t>(Port::NUM_GPIO_PORTS);

  struct Payload {
    Port gpioPort;
    uint8_t gpioPin;
    uint8_t bufferLength;
    uint8_t buffer[GPIO_MAX_BUFFER_SIZE];
  };

  explicit Gpio(Payload &data);
  Gpio() = default;

  std::string serialize(const CommandCode &commandCode) const;
  void deserialize(std::string &gpioDatagramPayload);

  void setGpioPort(const Port &gpioPort);
  void setGpioPin(const uint8_t &gpioPin);
  void setBuffer(const uint8_t *data, uint8_t length);
  void clearBuffer();

  Port getGpioPort() const;
  uint8_t getGpioPin() const;
  uint8_t getBufferLength() const;
  const uint8_t *getBuffer() const;

 private:
  Payload m_gpioDatagram;
};

}  // namespace Datagram
#endif
