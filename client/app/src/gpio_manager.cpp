extern "C" {
#include "gpio.h"
}
#include <cstdint>
#include <iostream>

#include "app.h"
#include "command_code.h"
#include "gpio_manager.h"

std::string GpioManager::processGpioPinState(std::string &payload) {
  m_gpioDatagram.deserialize(payload);

  GpioState pinState = gpio_peek_state(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()), m_gpioDatagram.getGpioPin());
  m_gpioDatagram.setData(static_cast<uint8_t>(pinState));

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_PIN_STATE);
}

std::string GpioManager::processGpioAllState(std::string &payload) {
  uint32_t gpioStateBitset = 0U;

  /* Simulation only supports reading port A and B */
  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * static_cast<uint8_t>(Datagram::Gpio::PINS_PER_PORT); i++) {
    gpioStateBitset |= (gpio_peek_state(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()), m_gpioDatagram.getGpioPin())) << i;
  }
  m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
  m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);
  m_gpioDatagram.setData(gpioStateBitset);
  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_ALL_STATES);
}