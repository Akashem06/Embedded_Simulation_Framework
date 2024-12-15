extern "C" {
#include "gpio.h"
}
#include <cstdint>
#include <iostream>
#include <vector>

#include "app.h"
#include "command_code.h"
#include "gpio_manager.h"

std::string GpioManager::processGpioPinState(std::string &payload) {
  m_gpioDatagram.deserialize(payload);

  uint8_t pinState = static_cast<uint8_t>(gpio_peek_state(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()), m_gpioDatagram.getGpioPin()));

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(&pinState, sizeof(pinState));

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_PIN_STATE);
}

std::string GpioManager::processGpioAllStates(std::string &payload) {
  std::vector<uint32_t> gpioStateBitsetArray;

  /* Round up the number of blocks by adding the divisor - 1 */
  constexpr uint8_t numBlocks = ((Datagram::Gpio::PINS_PER_PORT * static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS)) + 32U - 1U) / 32U;
  gpioStateBitsetArray.resize(numBlocks, 0U);

  /* Simulation only supports reading port A and B */
  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * Datagram::Gpio::PINS_PER_PORT; i++) {
    size_t blockIndex = i / 32U;
    size_t bitPosition = i % 32U;
    GpioState pinState = gpio_peek_state(static_cast<GpioPort>(i / 16U), i % 16U);
    gpioStateBitsetArray[blockIndex] |= (static_cast<uint32_t>(pinState << bitPosition));
  }
  m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
  m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);

  std::vector<uint8_t> byteArray;
  for (uint32_t value : gpioStateBitsetArray) {
    byteArray.push_back(static_cast<uint8_t>(value & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
  }

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(byteArray.data(), byteArray.size());

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_ALL_STATES);
}

std::string GpioManager::processGpioPinMode(std::string &payload) {
  m_gpioDatagram.deserialize(payload);

  uint8_t pinMode = static_cast<uint8_t>(gpio_peek_mode(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()), m_gpioDatagram.getGpioPin()));

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(&pinMode, sizeof(pinMode));

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_PIN_MODE);
}

std::string GpioManager::processGpioAllModes(std::string &payload) {
  std::vector<uint32_t> gpioStateBitsetArray;

  /* Calculate number of 32-bit blocks needed (8 pins per 32-bit block with 4 bits per pin) */
  constexpr uint8_t numBlocks = (Datagram::Gpio::PINS_PER_PORT * static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) + 8U - 1U) / 8U;
  gpioStateBitsetArray.resize(numBlocks, 0U);

  /* Simulation only supports reading port A and B */
  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * Datagram::Gpio::PINS_PER_PORT; i++) {
    size_t blockIndex = (i / 8U);       /* 4 bits per pin so there is only 8 pins per block */
    size_t bitPosition = (i % 8U) * 4U; /* Multiply by 4 to account for 4 bits per pin */

    GpioMode pinMode = gpio_peek_mode(static_cast<GpioPort>(i / 16U), i % 16U);

    gpioStateBitsetArray[blockIndex] &= ~(0xFU << bitPosition);
    gpioStateBitsetArray[blockIndex] |= (static_cast<uint32_t>(pinMode) << bitPosition);
  }

  m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
  m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);

  std::vector<uint8_t> byteArray;
  for (uint32_t value : gpioStateBitsetArray) {
    byteArray.push_back(static_cast<uint8_t>(value & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
  }

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(byteArray.data(), byteArray.size());

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_ALL_MODES);
}

std::string GpioManager::processGpioPinAltFunction(std::string &payload) {
  m_gpioDatagram.deserialize(payload);

  uint8_t pinAltFunction =
      static_cast<uint8_t>(gpio_peek_alt_function(static_cast<GpioPort>(m_gpioDatagram.getGpioPort()), m_gpioDatagram.getGpioPin()));

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(&pinAltFunction, sizeof(pinAltFunction));

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_PIN_ALT_FUNCTION);
}

std::string GpioManager::processGpioAllAltFunctions(std::string &payload) {
  std::vector<uint32_t> gpioAltFunctionBitsetArray;

  /* Calculate number of 32-bit blocks needed (8 pins per 32-bit block with 4 bits per pin) */
  constexpr uint8_t numBlocks = (Datagram::Gpio::PINS_PER_PORT * static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) + 8U - 1U) / 8U;
  gpioAltFunctionBitsetArray.resize(numBlocks, 0U);

  /* Simulation only supports reading port A and B */
  for (uint8_t i = 0U; i < static_cast<uint8_t>(Datagram::Gpio::Port::NUM_GPIO_PORTS) * Datagram::Gpio::PINS_PER_PORT; i++) {
    size_t blockIndex = (i / 8U);       /* 4 bits per pin so there is only 8 pins per block */
    size_t bitPosition = (i % 8U) * 4U; /* Multiply by 4 to account for 4 bits per pin */

    GpioAlternateFunctions pinFunction = gpio_peek_alt_function(static_cast<GpioPort>(i / 16U), i % 16U);

    gpioAltFunctionBitsetArray[blockIndex] &= ~(0xFU << bitPosition);
    gpioAltFunctionBitsetArray[blockIndex] |= (static_cast<uint32_t>(pinFunction) << bitPosition);
  }

  m_gpioDatagram.setGpioPort(Datagram::Gpio::Port::NUM_GPIO_PORTS);
  m_gpioDatagram.setGpioPin(Datagram::Gpio::PINS_PER_PORT);

  std::vector<uint8_t> byteArray;
  for (uint32_t value : gpioAltFunctionBitsetArray) {
    byteArray.push_back(static_cast<uint8_t>(value & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    byteArray.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
  }

  m_gpioDatagram.clearBuffer();
  m_gpioDatagram.setBuffer(byteArray.data(), byteArray.size());

  return m_gpioDatagram.serialize(CommandCode::GPIO_GET_ALL_ALT_FUNCTIONS);
}
