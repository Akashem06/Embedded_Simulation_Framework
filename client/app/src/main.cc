#include <iostream>

#include "app.h"
#include "app_callback.h"
#include "client.h"
#include "gpio_manager.h"
#include "ntp_client.h"

GpioManager clientGpioManager;

int main(int argc, char **argv) {
  std::cout << "Running Client" << std::endl;

  Client serverClient("127.0.0.1", 1024, applicationMessageCallback, applicationConnectCallback);
  serverClient.connectServer();

#if USE_NETWORK_TIME_PROTOCOL == 1U
  NTPClient ntpClient;
  ntpClient.startSynchronization("127.0.0.1");
#endif

  int n;
  std::cin >> n;

  return 0;
}
