#ifndef APP_H
#define APP_H

#include <string>

#include "can_listener.h"
#include "can_scheduler.h"
#include "gpio_manager.h"
#include "json_manager.h"

#ifndef USE_NETWORK_TIME_PROTOCOL
#define USE_NETWORK_TIME_PROTOCOL 0U
#endif

extern JSONManager serverJSONManager;
extern GpioManager serverGpioManager;
extern CanListener serverCanListener;
extern CanScheduler serverCanScheduler;

#endif
