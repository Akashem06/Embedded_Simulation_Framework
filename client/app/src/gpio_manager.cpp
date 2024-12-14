extern "C" {
#include "gpio.h"
}
#include <cstdint>
#include <iostream>

#include "app.h"
#include "command_code.h"
#include "gpio_manager.h"

std::string GpioManager::processGpioState(std::string &payload) {
  m_gpioDatagram.deserialize(payload);

  GpioState pinState =
      gpio_peek_state(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()),
                      m_gpioDatagram.getGpioPin());
  m_gpioDatagram.setData(static_cast<uint8_t>(pinState));

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_STATE);
}
