#include <iostream>

#include "can_manager.h"
#include "system_can.h"

#define NUM_FAST_CYCLE_MESSAGES 3U
#define NUM_MEDIUM_CYCLE_MESSAGES 5U
#define NUM_SLOW_CYCLE_MESSAGES 5U
#define NUM_TOTAL_MESSAGES 13U
#define MAX_MESSAGE_LENGTH 8U

void CanManager::scheduleCanMessages() {
  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_FAST_CYCLE_MESSAGES];
  } canFastCycleBCM;

  canFastCycleBCM.msg_head.opcode = TX_SETUP;
  canFastCycleBCM.msg_head.can_id = FAST_CYCLE_BCM_ID;
  canFastCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canFastCycleBCM.msg_head.nframes = NUM_FAST_CYCLE_MESSAGES;
  canFastCycleBCM.msg_head.count = 0;

  canFastCycleBCM.msg_head.ival1.tv_sec = 0U;
  canFastCycleBCM.msg_head.ival1.tv_usec = 0U;
  canFastCycleBCM.msg_head.ival2.tv_sec = FAST_CYCLE_SPEED_MS / 1000U;
  canFastCycleBCM.msg_head.ival2.tv_usec = (FAST_CYCLE_SPEED_MS % 1000U) * 1000U;

  canFastCycleBCM.frame[0U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_VT;
  canFastCycleBCM.frame[0U].can_dlc = 8U;
  memset(canFastCycleBCM.frame[0U].data, 0U, MAX_MESSAGE_LENGTH);
  canFastCycleBCM.frame[1U].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG;
  canFastCycleBCM.frame[1U].can_dlc = 4U;
  memset(canFastCycleBCM.frame[1U].data, 0U, MAX_MESSAGE_LENGTH);
  canFastCycleBCM.frame[2U].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_PEDAL;
  canFastCycleBCM.frame[2U].can_dlc = 5U;
  memset(canFastCycleBCM.frame[2U].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Fast cycle messages");
  }

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_MEDIUM_CYCLE_MESSAGES];
  } canMediumCycleBCM;

  canMediumCycleBCM.msg_head.opcode = TX_SETUP;
  canMediumCycleBCM.msg_head.can_id = MEDIUM_CYCLE_BCM_ID;
  canMediumCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canMediumCycleBCM.msg_head.nframes = NUM_MEDIUM_CYCLE_MESSAGES;
  canMediumCycleBCM.msg_head.count = 0;

  canMediumCycleBCM.msg_head.ival1.tv_sec = 0U;
  canMediumCycleBCM.msg_head.ival1.tv_usec = 0U;
  canMediumCycleBCM.msg_head.ival2.tv_sec = MEDIUM_CYCLE_SPEED_MS / 1000U;
  canMediumCycleBCM.msg_head.ival2.tv_usec = (MEDIUM_CYCLE_SPEED_MS % 1000U) * 1000U;

  canMediumCycleBCM.frame[0U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_STATUS;
  canMediumCycleBCM.frame[0U].can_dlc = 7U;
  memset(canMediumCycleBCM.frame[0U].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[1U].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG;
  canMediumCycleBCM.frame[1U].can_dlc = 4U;
  memset(canMediumCycleBCM.frame[1U].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[2U].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_INFO;
  canMediumCycleBCM.frame[2U].can_dlc = 8U;
  memset(canMediumCycleBCM.frame[2U].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[3U].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_STEERING;
  canMediumCycleBCM.frame[3U].can_dlc = 2U;
  memset(canMediumCycleBCM.frame[3U].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[4U].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE;
  canMediumCycleBCM.frame[4U].can_dlc = 4U;
  memset(canMediumCycleBCM.frame[4U].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Medium cycle messages");
  }

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_SLOW_CYCLE_MESSAGES];
  } canSlowCycleBCM;

  canSlowCycleBCM.msg_head.opcode = TX_SETUP;
  canSlowCycleBCM.msg_head.can_id = SLOW_CYCLE_BCM_ID;
  canSlowCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canSlowCycleBCM.msg_head.nframes = NUM_SLOW_CYCLE_MESSAGES;
  canSlowCycleBCM.msg_head.count = 0;

  canSlowCycleBCM.msg_head.ival1.tv_sec = 0U;
  canSlowCycleBCM.msg_head.ival1.tv_usec = 0U;
  canSlowCycleBCM.msg_head.ival2.tv_sec = SLOW_CYCLE_SPEED_MS / 1000U;
  canSlowCycleBCM.msg_head.ival2.tv_usec = (SLOW_CYCLE_SPEED_MS % 1000U) * 1000U;

  canSlowCycleBCM.frame[0U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_INFO;
  canSlowCycleBCM.frame[0U].can_dlc = 6U;
  memset(canSlowCycleBCM.frame[0U].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[1U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE1_STATUS;
  canSlowCycleBCM.frame[1U].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[1U].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[2U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE2_STATUS;
  canSlowCycleBCM.frame[2U].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[2U].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[3U].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE3_STATUS;
  canSlowCycleBCM.frame[3U].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[3U].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[4U].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG;
  canSlowCycleBCM.frame[4U].can_dlc = 4U;
  memset(canSlowCycleBCM.frame[4U].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Slow cycle messages");
  }
}