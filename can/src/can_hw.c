/************************************************************************************************
 * @file   can_hw.c
 *
 * @brief  Source file for CAN HW Interface
 *
 * @date   2024-11-03
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Inter-component Headers */
#include "log.h"

/* Intra-component Headers */
#include "can_hw.h"

/** @brief Maximum amount of CAN filters */
#define CAN_HW_MAX_FILTERS CAN_QUEUE_SIZE

/**
 * @brief   Storage for all CAN Socket data
 */
typedef struct CanHwSocketData {
  int can_fd;
  struct can_frame rx_frame;
  struct can_filter filters[CAN_HW_MAX_FILTERS];
  size_t num_filters;
  uint32_t delay_us;
  int loopback;
} CanHwSocketData;

static pthread_t s_rx_pthread_id;
static bool s_bus_alive = true;
static CanHwSocketData s_socket_data = {.can_fd = -1};

static uint32_t s_get_delay(CanHwBitrate bitrate) {
  const uint32_t delay_us[NUM_CAN_HW_BITRATES] = {
      1000U, /* 125 kbps */
      500U,  /* 250 kbps */
      250U,  /* 500 kbps */
      125U,  /* 1 mbps */
  };

  return delay_us[bitrate];
}

static void *s_listener_thread(void *param) {
  CanQueue *rx_queue = (CanQueue *)param;
  CanMessage rx_msg = {0U};

  while (s_bus_alive) {
    ssize_t num_bytes_read = read(s_socket_data.can_fd, &s_socket_data.rx_frame, sizeof(s_socket_data.rx_frame));

    if (num_bytes_read == -1) {
      /* Handle read failure */
      continue;
    }

    can_hw_receive(&rx_msg.id.raw, (bool *)&rx_msg.extended, &rx_msg.data, &rx_msg.dlc);
    can_queue_push(rx_queue, &rx_msg);
  }
}

void can_hw_init(const CanQueue *rx_queue, const CanSettings *settings) {
  /* If the socket already exists */
  if (s_socket_data.can_fd != -1) {
    /* Close the existing CAN socket */
    close(s_socket_data.can_fd);

    /* Close the RX Listening thread */
    s_bus_alive = false;
    pthread_join(s_rx_pthread_id, NULL);

    LOG_CRITICAL("CAN HW: socket exists. Aborting\n");
    return;
  }

  /* Initialize */
  s_socket_data.delay_us = s_get_delay(settings->bitrate);
  s_socket_data.loopback = settings->loopback;

  s_socket_data.can_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (s_socket_data.can_fd < 0) {
    /* Handle socket creation failure */
    LOG_CRITICAL("CAN HW: Failed to open SocketCAN socket\n");
    return;
  }

  /* Set loopback options. Technically loopback is enabled by default, but lets just do it explicitly here */
  if (setsockopt(s_socket_data.can_fd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &s_socket_data.loopback, sizeof(s_socket_data.loopback)) < 0) {
    /* Handle failure to set loopback mode */
    LOG_CRITICAL("CAN HW: Failed to set loopback mode on socket\n");
    return;
  }
  if (setsockopt(s_socket_data.can_fd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &s_socket_data.loopback, sizeof(s_socket_data.loopback)) < 0) {
    /* Handle failure to set receive own messages */
    LOG_CRITICAL("CAN HW: Failed to set recv own msg on socket\n");
    return;
  }

  /* Set bus name */
  struct ifreq ifr = {0};
  snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", CAN_HW_DEV_INTERFACE);
  if (ioctl(s_socket_data.can_fd, SIOCGIFINDEX, &ifr) < 0) {
    LOG_CRITICAL("CAN HW: Device %s not found\n", CAN_HW_DEV_INTERFACE);
    /* Handle failure to connect to Linux CAN Bus */
    return;
  }

  struct sockaddr_can addr = {
      .can_family = AF_CAN,
      .can_ifindex = ifr.ifr_ifindex,
  };

  if (bind(s_socket_data.can_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    /* Handle failure to bind the CAN Socket */
    LOG_CRITICAL("CAN HW: Failed to bind socket\n");
    return;
  }

  /* Start the RX Listener Thread */
  s_bus_alive = true;
  if (pthread_create(&s_rx_pthread_id, NULL, s_listener_thread, rx_queue)) {
    LOG_CRITICAL("Failed to create CAN HW Listener thread\n");
    close(s_socket_data.can_fd);
    return;
  }

  LOG_DEBUG("CAN HW initialized on %s\n", CAN_HW_DEV_INTERFACE);
}

void can_hw_add_filter_in(uint32_t mask, uint32_t filter, bool extended) {}

CanHwBusStatus can_hw_bus_status(void) {
  return CAN_HW_BUS_STATUS_OK;
}

void can_hw_transmit(uint32_t id, bool extended, const uint8_t *data, size_t len) {}

bool can_hw_receive(uint32_t *id, bool *extended, uint64_t *data, size_t *len) {
  *extended = !!(s_socket_data.rx_frame.can_id & CAN_EFF_FLAG);
  uint32_t mask = *extended ? CAN_EFF_MASK : CAN_SFF_MASK;
  *id = s_socket_data.rx_frame.can_id & mask;
  memcpy(data, s_socket_data.rx_frame.data, sizeof(*data));
  *len = s_socket_data.rx_frame.can_dlc;

  memset(&s_socket_data.rx_frame, 0, sizeof(s_socket_data.rx_frame));

  return true;
}
