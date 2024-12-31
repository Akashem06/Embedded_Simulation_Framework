#include "can_manager.h"

#include <unistd.h>

#include <cstring>
#include <iostream>

#include "app.h"
#include "thread_helpers.h"

#define CAN_MESSAGE_JSON_KEY "messages"

CanManager::CanManager() {
  m_isListening = false;
  m_rawCanSocket = -1;
  m_bcmCanSocket = -1;
  pthread_mutex_init(&m_mutex, nullptr);
}

CanManager::~CanManager() {
  pthread_mutex_destroy(&m_mutex);
}

void CanManager::listenCanBusProcedure() {
  m_rawCanSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

  if (m_rawCanSocket < 0) {
    throw std::runtime_error("Error creating raw CAN socket");
  }

  struct ifreq ifr;
  strcpy(ifr.ifr_name, CAN_INTERFACE_NAME.c_str());
  if (ioctl(m_rawCanSocket, SIOCGIFINDEX, &ifr) < 0) {
    throw std::runtime_error("Error binding raw CAN socket to interface");
  }

  struct sockaddr_can addr = {};
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(m_rawCanSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    throw std::runtime_error("Error binding raw CAN socket");
  }

  m_isListening = true;

  struct can_frame canFrame;
  int numBytes;

  while (m_isListening) {
    numBytes = read(m_rawCanSocket, &canFrame, sizeof(struct can_frame));

    if (numBytes < 0) {
      throw std::runtime_error("Error reading CAN data");
      break;
    }

    pthread_mutex_lock(&m_mutex);
    canMessageHandler(canFrame.can_id, canFrame.data);
    pthread_mutex_unlock(&m_mutex);
  }

  close(m_rawCanSocket);
  m_isListening = false;
}

void CanManager::updateJSONProcedure() {
  while (m_isListening) {
    pthread_mutex_lock(&m_mutex);
    globalJSON.setProjectValue(CAN_JSON_NAME, CAN_MESSAGE_JSON_KEY, m_canInfo);
    pthread_mutex_unlock(&m_mutex);

    thread_sleep_ms(UPDATE_CAN_JSON_FREQUENCY_MS);
  }
}

void *listenCanBusWrapper(void *param) {
  CanManager *canManager = static_cast<CanManager *>(param);

  try {
    canManager->listenCanBusProcedure();
  } catch (std::exception &e) {
    std::cerr << "Can Manager Listener Thread Error: " << e.what() << std::endl;
  }

  return nullptr;
}

void *updateJSONWrapper(void *param) {
  CanManager *canManager = static_cast<CanManager *>(param);

  try {
    canManager->updateJSONProcedure();
  } catch (std::exception &e) {
    std::cerr << "Can Manager Update JSON Thread Error: " << e.what() << std::endl;
  }

  return nullptr;
}

void CanManager::listenCanBus() {
  if (m_isListening)
    return;

  if (pthread_create(&m_listenCanBusId, nullptr, listenCanBusWrapper, this)) {
    throw std::runtime_error("CAN listener thread creation error");
  }

  if (pthread_create(&m_updateJSONId, nullptr, updateJSONWrapper, this)) {
    throw std::runtime_error("CAN update JSON thread creation error");
  }
}

void CanManager::startCanScheduler() {
  try {
    m_bcmCanSocket = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);

    if (m_bcmCanSocket < 0) {
      throw std::runtime_error("Error creating socket for CAN Broadcast Manager");
    }

    struct ifreq ifr;
    strcpy(ifr.ifr_name, CAN_INTERFACE_NAME.c_str());
    if (ioctl(m_bcmCanSocket, SIOCGIFINDEX, &ifr) < 0) {
      throw std::runtime_error("Error writing interface name to socketCAN file descriptor. Check if vcan0 is enabled?");
    }

    struct sockaddr_can addr = {};
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (connect(m_bcmCanSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      throw std::runtime_error("Error connecting to SocketCAN broadcast manager");
    }

    scheduleCanMessages();

  } catch (std::exception &e) {
    std::cerr << "Error running CAN Scheduler: " << e.what() << std::endl;
  }
}
