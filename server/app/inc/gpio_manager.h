#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

#include <stdint.h>
#include <string.h>

#include <unordered_map>

#include "gpio_datagram.h"

class GpioManager {
 private:
  std::unordered_map<std::string, Datagram::Gpio::State> m_gpioStates;
  std::unordered_map<std::string, Datagram::Gpio::Mode> m_gpioModes;

  Datagram::Gpio m_gpioDatagram;

  void loadGpioStates(std::string &projectName);
  void loadGpioModes(std::string &projectName);

 public:
  GpioManager() = default;

  void updateGpioStates(std::string &projectName, std::string &payload);
  void updateGpioModes(std::string &projectName, std::string &payload);

  std::string createGpioCommand(CommandCode commandCode,
                                std::string &gpioPortPin, std::string data);
};

#endif
