#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

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

class CanManager {
 private:
  const std::string CAN_INTERFACE_NAME = "vcan0";
  const std::string CAN_JSON_NAME = "CANManager";

  static const constexpr int FAST_CYCLE_SPEED_MS = 1U;
  static const constexpr int MEDIUM_CYCLE_SPEED_MS = 100U;
  static const constexpr int SLOW_CYCLE_SPEED_MS = 1000U;

  static const constexpr int UPDATE_CAN_JSON_FREQUENCY_MS = 1000U;

  static const constexpr int SLOW_CYCLE_BCM_ID = 0U;
  static const constexpr int MEDIUM_CYCLE_BCM_ID = 1U;
  static const constexpr int FAST_CYCLE_BCM_ID = 2U;

  std::unordered_map<std::string, nlohmann::json> m_canInfo;

  pthread_mutex_t m_mutex;
  pthread_t m_listenCanBusId;
  pthread_t m_updateJSONId;

  int m_rawCanSocket;
  int m_bcmCanSocket;

  std::atomic<bool> m_isListening;

  void canMessageHandler(uint32_t id, const uint8_t *data);

 public:
  CanManager();
  ~CanManager();

  void listenCanBus();
  void listenCanBusProcedure();
  void updateJSONProcedure();

  void startCanScheduler();
  void scheduleCanMessages();
};

#endif
