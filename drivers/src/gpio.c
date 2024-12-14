#include "gpio.h"

static GpioMode s_gpio_pin_modes[GPIO_TOTAL_PINS];
static uint8_t s_gpio_pin_state[GPIO_TOTAL_PINS];
static GpioAlternateFunctions s_gpio_alt_functions[GPIO_TOTAL_PINS];

GpioMode gpio_peek_mode(GpioPort port, uint8_t pin) {
  if ((port * GPIO_PINS_PER_PORT) + pin < GPIO_TOTAL_PINS) {
    return s_gpio_pin_modes[(port * GPIO_PINS_PER_PORT) + pin];
  } else {
    return NUM_GPIO_MODES;
  }
}

GpioState gpio_peek_state(GpioPort port, uint8_t pin) {
  if ((port * GPIO_PINS_PER_PORT) + pin < GPIO_TOTAL_PINS) {
    return s_gpio_pin_state[(port * GPIO_PINS_PER_PORT) + pin];
  } else {
    return NUM_GPIO_STATES;
  }
}

GpioAlternateFunctions gpio_peek_alt_function(GpioPort port, uint8_t pin) {
  if ((port * GPIO_PINS_PER_PORT) + pin < GPIO_TOTAL_PINS) {
    return s_gpio_alt_functions[(port * GPIO_PINS_PER_PORT) + pin];
  } else {
    return GPIO_ALT_NONE;
  }
}
