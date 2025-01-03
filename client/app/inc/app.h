#ifndef APP_H
#define APP_H

#include "gpio_manager.h"

#ifndef USE_NETWORK_TIME_PROTOCOL
#define USE_NETWORK_TIME_PROTOCOL 0U
#endif

#define DEFAULT_PROJECT_NAME "Default Project"
#define DEFAULT_HARDWARE_MODEL "MS16.0.0"

extern GpioManager clientGpioManager;

#endif
