#pragma once

/************************************************************************************************
 * @file   system_can.h
 *
 * @brief  Header file for all CAN message IDs
 *
 * @date   2025-01-04
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include <stdbool.h>

/**
 * @defgroup CAN
 * @brief    CAN library
 * @{
 */

#define SYSTEM_CAN_MESSAGE_ID_OFFSET       4U
#define SYSTEM_CAN_MESSAGE_PRIORITY_BIT    0x400U

/** @brief CAN Device definitions */
typedef enum {
  SYSTEM_CAN_DEVICE_BMS_CARRIER = 0,
  SYSTEM_CAN_DEVICE_CAN_COMMUNICATION = 1,
  SYSTEM_CAN_DEVICE_CENTRE_CONSOLE = 2,
  NUM_SYSTEM_CAN_DEVICES = 3
} SystemCanDevice;


#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_STATUS \
  (1 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_VT \
  (2 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_INFO \
  (3 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE1_STATUS \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (61 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE2_STATUS \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (62 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE3_STATUS \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (63 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_BMS_CARRIER

#define SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (58 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CAN_COMMUNICATION

#define SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (59 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CAN_COMMUNICATION

#define SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG \
   SYSTEM_CAN_MESSAGE_PRIORITY_BIT + (60 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CAN_COMMUNICATION

#define SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_PEDAL \
  (4 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CENTRE_CONSOLE

#define SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_INFO \
  (5 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CENTRE_CONSOLE

#define SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_STEERING \
  (6 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CENTRE_CONSOLE

#define SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE \
  (7 << SYSTEM_CAN_MESSAGE_ID_OFFSET) + SYSTEM_CAN_DEVICE_CENTRE_CONSOLE

/** @} */