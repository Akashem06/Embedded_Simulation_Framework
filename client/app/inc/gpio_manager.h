#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

#include <stdint.h>
#include <string.h>

#include <unordered_map>

#include "gpio_datagram.h"

class GpioManager {
 private:
  Datagram::Gpio m_gpioDatagram;

 public:
  GpioManager() = default;

  std::string processGpioPinState(std::string &payload);
  std::string processGpioAllState(std::string &payload);

//   std::string createGpioCommand(CommandCode commandCode, std::string &gpioPortPin, uint8_t data);
};

#endif
