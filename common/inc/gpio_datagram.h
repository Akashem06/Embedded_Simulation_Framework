#ifndef GPIO_DATAGRAM_H
#define GPIO_DATAGRAM_H

#include <string>

#include "command_code.h"

namespace Datagram {
class Gpio {
 public:
  enum class Port {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_H,
    NUM_GPIO_PORTS
  };

  struct Payload {
    Port gpioPort;
    int gpioPin;
  };

  explicit Gpio(Payload &data);
  Gpio() = default;

  std::string serialize(const CommandCode &commandCode) const;
  void deserialize(std::string &gpioDatagramPayload);

  void setGpioPort(const Port &gpioPort);
  void setGpioPin(const int &gpioPin);

  Port getGpioPort() const;
  int getGpioPin() const;

 private:
  Payload m_gpioDatagram;
};

}  // namespace Datagram
#endif
