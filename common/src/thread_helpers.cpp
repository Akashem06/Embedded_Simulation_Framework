#include "thread_helpers.h"

#include <time.h>

void thread_sleep_s(unsigned int seconds) {
  struct timespec ts;
  ts.tv_sec = seconds;
  ts.tv_nsec = 0U;
  nanosleep(&ts, NULL);
}

void thread_sleep_ms(unsigned int milliseconds) {
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000U;
  ts.tv_nsec = (milliseconds % 1000U) * 1000000U;
  nanosleep(&ts, NULL);
}
