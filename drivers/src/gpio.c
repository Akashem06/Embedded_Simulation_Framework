#include "gpio.h"

/* Random data */
static GpioMode s_gpio_pin_modes[GPIO_TOTAL_PINS] = {GPIO_OUTPUT_PUSH_PULL,  GPIO_INPUT_FLOATING,  GPIO_ANALOG,          GPIO_INPUT_PULL_UP,
                                                     GPIO_OUTPUT_OPEN_DRAIN, GPIO_ALTFN_PUSH_PULL, GPIO_INPUT_PULL_DOWN, GPIO_ALT_NONE,
                                                     GPIO_OUTPUT_PUSH_PULL,  GPIO_INPUT_FLOATING,  GPIO_ANALOG,          GPIO_INPUT_PULL_UP,
                                                     GPIO_OUTPUT_OPEN_DRAIN, GPIO_ALTFN_PUSH_PULL, GPIO_INPUT_PULL_DOWN, GPIO_ALT_NONE,
                                                     GPIO_OUTPUT_PUSH_PULL,  GPIO_INPUT_FLOATING,  GPIO_ANALOG,          GPIO_INPUT_PULL_UP,
                                                     GPIO_OUTPUT_OPEN_DRAIN, GPIO_ALTFN_PUSH_PULL, GPIO_INPUT_PULL_DOWN, GPIO_ALT_NONE,
                                                     GPIO_OUTPUT_PUSH_PULL,  GPIO_INPUT_FLOATING,  GPIO_ANALOG,          GPIO_INPUT_PULL_UP,
                                                     GPIO_OUTPUT_OPEN_DRAIN, GPIO_ALTFN_PUSH_PULL, GPIO_INPUT_PULL_DOWN, GPIO_ALT_NONE};

/* Random data */
static uint8_t s_gpio_pin_state[GPIO_TOTAL_PINS] = {
    GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH,
    GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH,
    GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH,
    GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH, GPIO_STATE_LOW, GPIO_STATE_HIGH};

/* Random data */
static GpioAlternateFunctions s_gpio_alt_functions[GPIO_TOTAL_PINS] = {
    GPIO_ALT_NONE,    GPIO_ALT1_TIM1,   GPIO_ALT4_I2C1,   GPIO_ALT5_SPI1,   GPIO_ALT7_USART1, GPIO_ALT9_CAN1, GPIO_ALT14_TIM15, GPIO_ALT0_SWDIO,
    GPIO_ALT1_TIM2,   GPIO_ALT4_I2C2,   GPIO_ALT5_SPI2,   GPIO_ALT7_USART2, GPIO_ALT_NONE,    GPIO_ALT1_TIM1, GPIO_ALT4_I2C3,   GPIO_ALT0_SWCLK,
    GPIO_ALT7_USART3, GPIO_ALT9_CAN1,   GPIO_ALT14_TIM16, GPIO_ALT_NONE,    GPIO_ALT1_TIM1,   GPIO_ALT4_I2C1, GPIO_ALT5_SPI1,   GPIO_ALT7_USART1,
    GPIO_ALT9_CAN1,   GPIO_ALT14_TIM15, GPIO_ALT_NONE,    GPIO_ALT1_TIM2,   GPIO_ALT4_I2C2,   GPIO_ALT5_SPI2, GPIO_ALT7_USART2, GPIO_ALT_NONE};

GpioMode gpio_peek_mode(GpioAddress *address) {
  if (address->port >= NUM_GPIO_PORTS || address->pin >= GPIO_PINS_PER_PORT) {
    return NUM_GPIO_MODES;
  } else {
    return s_gpio_pin_modes[(address->port * GPIO_PINS_PER_PORT) + address->pin];
  }
}

GpioState gpio_peek_state(GpioAddress *address) {
  if (address->port >= NUM_GPIO_PORTS || address->pin >= GPIO_PINS_PER_PORT) {
    return NUM_GPIO_STATES;
  } else {
    return s_gpio_pin_state[(address->port * GPIO_PINS_PER_PORT) + address->pin];
  }
}

GpioAlternateFunctions gpio_peek_alt_function(GpioAddress *address) {
  if (address->port >= NUM_GPIO_PORTS || address->pin >= GPIO_PINS_PER_PORT) {
    return GPIO_ALT_NONE;
  } else {
    return s_gpio_alt_functions[(address->port * GPIO_PINS_PER_PORT) + address->pin];
  }
}

void gpio_set_state(GpioAddress *address, GpioState state) {
  if (address->port >= NUM_GPIO_PORTS || address->pin >= GPIO_PINS_PER_PORT) {
    return;
  }

  uint32_t index = address->port * (uint32_t)GPIO_PINS_PER_PORT + address->pin;
  GpioMode mode = s_gpio_pin_modes[index];
  if (mode != GPIO_OUTPUT_OPEN_DRAIN && mode != GPIO_OUTPUT_PUSH_PULL) {
    /* Log trying to set input pin */
    return;
  }
  s_gpio_pin_state[index] = state;
}
