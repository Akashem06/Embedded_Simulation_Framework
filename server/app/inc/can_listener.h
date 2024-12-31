#ifndef CAN_LISTENER_H
#define CAN_LISTENER_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/bcm.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <cstring>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class CanListener {
 private:
  const std::string CAN_INTERFACE_NAME = "vcan0";
  const std::string CAN_JSON_NAME = "CANListener";

  static const constexpr unsigned int UPDATE_CAN_JSON_FREQUENCY_MS = 1000U;

  std::unordered_map<std::string, nlohmann::json> m_canInfo;

  pthread_mutex_t m_mutex;
  pthread_t m_listenCanBusId;
  pthread_t m_updateJSONId;

  int m_rawCanSocket;

  std::atomic<bool> m_isListening;

  void canMessageHandler(uint32_t id, const uint8_t *data);

 public:
  CanListener();
  ~CanListener();

  void listenCanBus();
  void listenCanBusProcedure();
  void updateJSONProcedure();
};

#endif
