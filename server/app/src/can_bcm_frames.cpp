#include <iostream>

#include "can_manager.h"
#include "system_can.h"

#define NUM_FAST_CYCLE_MESSAGES 3U
#define NUM_MEDIUM_CYCLE_MESSAGES 5U
#define NUM_SLOW_CYCLE_MESSAGES 5U
#define NUM_TOTAL_MESSAGES 13U

void CanManager::scheduleCanMessages() {
  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_FAST_CYCLE_MESSAGES];
  } canFastCycleBCM;

  canFastCycleBCM.msg_head.opcode = TX_SETUP;
  canFastCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canFastCycleBCM.msg_head.nframes = NUM_FAST_CYCLE_MESSAGES;
  canFastCycleBCM.msg_head.count = 0;

  canFastCycleBCM.msg_head.ival2.tv_sec = FAST_CYCLE_SPEED_MS / 1000U;
  canFastCycleBCM.msg_head.ival2.tv_usec = (FAST_CYCLE_SPEED_MS % 1000U) * 1000000U;

  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Fast cycle messages");
  }

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_MEDIUM_CYCLE_MESSAGES];
  } canMediumCycleBCM;

  canMediumCycleBCM.msg_head.opcode = TX_SETUP;
  canMediumCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canMediumCycleBCM.msg_head.nframes = NUM_MEDIUM_CYCLE_MESSAGES;
  canMediumCycleBCM.msg_head.count = 0;

  canMediumCycleBCM.msg_head.ival2.tv_sec = MEDIUM_CYCLE_SPEED_MS / 1000U;
  canMediumCycleBCM.msg_head.ival2.tv_usec = (MEDIUM_CYCLE_SPEED_MS % 1000U) * 1000000U;

  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Medium cycle messages");
  }

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_SLOW_CYCLE_MESSAGES];
  } canSlowCycleBCM;

  canSlowCycleBCM.msg_head.opcode = TX_SETUP;
  canSlowCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canSlowCycleBCM.msg_head.nframes = NUM_SLOW_CYCLE_MESSAGES;
  canSlowCycleBCM.msg_head.count = 0;

  canSlowCycleBCM.msg_head.ival2.tv_sec = SLOW_CYCLE_SPEED_MS / 1000U;
  canSlowCycleBCM.msg_head.ival2.tv_usec = (SLOW_CYCLE_SPEED_MS % 1000U) * 1000000U;

  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Slow cycle messages");
  }
}