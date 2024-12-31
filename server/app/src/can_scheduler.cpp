#include "can_scheduler.h"

#include <cstring>
#include <iostream>

#include "system_can.h"

/** @warning  This file is autogenerated */

CanScheduler::CanScheduler() {
  m_isConnected = false;
  m_bcmCanSocket = -1;
}

void CanScheduler::scheduleCanMessages() {
  canFastCycleBCM.msg_head.opcode = TX_SETUP;
  canFastCycleBCM.msg_head.can_id = FAST_CYCLE_BCM_ID;
  canFastCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canFastCycleBCM.msg_head.nframes = NUM_FAST_CYCLE_MESSAGES;
  canFastCycleBCM.msg_head.count = 0;

  canFastCycleBCM.msg_head.ival1.tv_sec = 0U;
  canFastCycleBCM.msg_head.ival1.tv_usec = 0U;
  canFastCycleBCM.msg_head.ival2.tv_sec = FAST_CYCLE_SPEED_MS / 1000U;
  canFastCycleBCM.msg_head.ival2.tv_usec = (FAST_CYCLE_SPEED_MS % 1000U) * 1000U;

  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_VT;
  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].can_dlc = 8U;
  memset(canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG;
  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].can_dlc = 4U;
  memset(canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_PEDAL;
  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].can_dlc = 5U;
  memset(canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Fast cycle messages");
  }

  canMediumCycleBCM.msg_head.opcode = TX_SETUP;
  canMediumCycleBCM.msg_head.can_id = MEDIUM_CYCLE_BCM_ID;
  canMediumCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canMediumCycleBCM.msg_head.nframes = NUM_MEDIUM_CYCLE_MESSAGES;
  canMediumCycleBCM.msg_head.count = 0;

  canMediumCycleBCM.msg_head.ival1.tv_sec = 0U;
  canMediumCycleBCM.msg_head.ival1.tv_usec = 0U;
  canMediumCycleBCM.msg_head.ival2.tv_sec = MEDIUM_CYCLE_SPEED_MS / 1000U;
  canMediumCycleBCM.msg_head.ival2.tv_usec = (MEDIUM_CYCLE_SPEED_MS % 1000U) * 1000U;

  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_STATUS;
  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].can_dlc = 7U;
  memset(canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG;
  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].can_dlc = 4U;
  memset(canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_INFO;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].can_dlc = 8U;
  memset(canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_STEERING;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX].can_dlc = 2U;
  memset(canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].can_dlc = 4U;
  memset(canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Medium cycle messages");
  }

  canSlowCycleBCM.msg_head.opcode = TX_SETUP;
  canSlowCycleBCM.msg_head.can_id = SLOW_CYCLE_BCM_ID;
  canSlowCycleBCM.msg_head.flags = SETTIMER | STARTTIMER;
  canSlowCycleBCM.msg_head.nframes = NUM_SLOW_CYCLE_MESSAGES;
  canSlowCycleBCM.msg_head.count = 0;

  canSlowCycleBCM.msg_head.ival1.tv_sec = 0U;
  canSlowCycleBCM.msg_head.ival1.tv_usec = 0U;
  canSlowCycleBCM.msg_head.ival2.tv_sec = SLOW_CYCLE_SPEED_MS / 1000U;
  canSlowCycleBCM.msg_head.ival2.tv_usec = (SLOW_CYCLE_SPEED_MS % 1000U) * 1000U;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_INFO;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].can_dlc = 6U;
  memset(canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE1_STATUS;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE2_STATUS;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE3_STATUS;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].can_dlc = 8U;
  memset(canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);
  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].can_id = SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG;
  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].can_dlc = 4U;
  memset(canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].data, 0U, MAX_MESSAGE_LENGTH);

  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to schedule CAN BCM Slow cycle messages");
  }
}

void CanScheduler::startCanScheduler() {
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
void CanScheduler::update_battery_status_fault(uint16_t fault_value) {
  unsigned int start_byte = 0;

  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 0U] = (fault_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 1U] = (fault_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update fault");
  }
}
void CanScheduler::update_battery_status_fault_val(uint16_t fault_val_value) {
  unsigned int start_byte = 2;

  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 0U] = (fault_val_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 1U] = (fault_val_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update fault_val");
  }
}
void CanScheduler::update_battery_status_aux_batt_v(uint16_t aux_batt_v_value) {
  unsigned int start_byte = 4;

  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 0U] = (aux_batt_v_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 1U] = (aux_batt_v_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update aux_batt_v");
  }
}
void CanScheduler::update_battery_status_afe_status(uint8_t afe_status_value) {
  unsigned int start_byte = 6;

  canMediumCycleBCM.frame[MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX].data[start_byte + 0U] = (afe_status_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update afe_status");
  }
}
void CanScheduler::update_battery_vt_voltage(uint16_t voltage_value) {
  unsigned int start_byte = 0;

  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 0U] = (voltage_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 1U] = (voltage_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update voltage");
  }
}
void CanScheduler::update_battery_vt_current(uint16_t current_value) {
  unsigned int start_byte = 2;

  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 0U] = (current_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 1U] = (current_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update current");
  }
}
void CanScheduler::update_battery_vt_temperature(uint16_t temperature_value) {
  unsigned int start_byte = 4;

  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 0U] = (temperature_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 1U] = (temperature_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update temperature");
  }
}
void CanScheduler::update_battery_vt_batt_perc(uint16_t batt_perc_value) {
  unsigned int start_byte = 6;

  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 0U] = (batt_perc_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX].data[start_byte + 1U] = (batt_perc_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update batt_perc");
  }
}
void CanScheduler::update_battery_info_fan1(uint8_t fan1_value) {
  unsigned int start_byte = 0;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 0U] = (fan1_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update fan1");
  }
}
void CanScheduler::update_battery_info_fan2(uint8_t fan2_value) {
  unsigned int start_byte = 1;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 0U] = (fan2_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update fan2");
  }
}
void CanScheduler::update_battery_info_max_cell_v(uint16_t max_cell_v_value) {
  unsigned int start_byte = 2;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 0U] = (max_cell_v_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 1U] = (max_cell_v_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update max_cell_v");
  }
}
void CanScheduler::update_battery_info_min_cell_v(uint16_t min_cell_v_value) {
  unsigned int start_byte = 4;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 0U] = (min_cell_v_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX].data[start_byte + 1U] = (min_cell_v_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update min_cell_v");
  }
}
void CanScheduler::update_afe1_status_id(uint8_t id_value) {
  unsigned int start_byte = 0;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 0U] = (id_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update id");
  }
}
void CanScheduler::update_afe1_status_temp(uint8_t temp_value) {
  unsigned int start_byte = 1;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 0U] = (temp_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update temp");
  }
}
void CanScheduler::update_afe1_status_v1(uint16_t v1_value) {
  unsigned int start_byte = 2;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v1_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v1");
  }
}
void CanScheduler::update_afe1_status_v2(uint16_t v2_value) {
  unsigned int start_byte = 4;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v2_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v2");
  }
}
void CanScheduler::update_afe1_status_v3(uint16_t v3_value) {
  unsigned int start_byte = 6;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v3_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v3_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v3");
  }
}
void CanScheduler::update_afe2_status_id(uint8_t id_value) {
  unsigned int start_byte = 0;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 0U] = (id_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update id");
  }
}
void CanScheduler::update_afe2_status_temp(uint8_t temp_value) {
  unsigned int start_byte = 1;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 0U] = (temp_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update temp");
  }
}
void CanScheduler::update_afe2_status_v1(uint16_t v1_value) {
  unsigned int start_byte = 2;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v1_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v1");
  }
}
void CanScheduler::update_afe2_status_v2(uint16_t v2_value) {
  unsigned int start_byte = 4;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v2_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v2");
  }
}
void CanScheduler::update_afe2_status_v3(uint16_t v3_value) {
  unsigned int start_byte = 6;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v3_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v3_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v3");
  }
}
void CanScheduler::update_afe3_status_id(uint8_t id_value) {
  unsigned int start_byte = 0;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 0U] = (id_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update id");
  }
}
void CanScheduler::update_afe3_status_temp(uint8_t temp_value) {
  unsigned int start_byte = 1;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 0U] = (temp_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update temp");
  }
}
void CanScheduler::update_afe3_status_v1(uint16_t v1_value) {
  unsigned int start_byte = 2;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v1_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v1");
  }
}
void CanScheduler::update_afe3_status_v2(uint16_t v2_value) {
  unsigned int start_byte = 4;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v2_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v2");
  }
}
void CanScheduler::update_afe3_status_v3(uint16_t v3_value) {
  unsigned int start_byte = 6;

  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 0U] = (v3_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX].data[start_byte + 1U] = (v3_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update v3");
  }
}
void CanScheduler::update_fast_one_shot_msg_sig1(uint16_t sig1_value) {
  unsigned int start_byte = 0;

  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig1_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig1");
  }
}
void CanScheduler::update_fast_one_shot_msg_sig2(uint16_t sig2_value) {
  unsigned int start_byte = 2;

  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig2_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig2");
  }
}
void CanScheduler::update_medium_one_shot_msg_sig1(uint16_t sig1_value) {
  unsigned int start_byte = 0;

  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig1_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig1");
  }
}
void CanScheduler::update_medium_one_shot_msg_sig2(uint16_t sig2_value) {
  unsigned int start_byte = 2;

  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig2_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig2");
  }
}
void CanScheduler::update_slow_one_shot_msg_sig1(uint16_t sig1_value) {
  unsigned int start_byte = 0;

  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig1_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig1_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig1");
  }
}
void CanScheduler::update_slow_one_shot_msg_sig2(uint16_t sig2_value) {
  unsigned int start_byte = 2;

  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 0U] = (sig2_value >> 0U) & 0xFFU;
  canSlowCycleBCM.frame[SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX].data[start_byte + 1U] = (sig2_value >> 8U) & 0xFFU;
  if (write(m_bcmCanSocket, &canSlowCycleBCM, sizeof(canSlowCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update sig2");
  }
}
void CanScheduler::update_cc_pedal_throttle_output(uint32_t throttle_output_value) {
  unsigned int start_byte = 0;

  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data[start_byte + 0U] = (throttle_output_value >> 0U) & 0xFFU;
  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data[start_byte + 1U] = (throttle_output_value >> 8U) & 0xFFU;
  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data[start_byte + 2U] = (throttle_output_value >> 16U) & 0xFFU;
  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data[start_byte + 3U] = (throttle_output_value >> 24U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update throttle_output");
  }
}
void CanScheduler::update_cc_pedal_brake_output(uint8_t brake_output_value) {
  unsigned int start_byte = 4;

  canFastCycleBCM.frame[FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX].data[start_byte + 0U] = (brake_output_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canFastCycleBCM, sizeof(canFastCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update brake_output");
  }
}
void CanScheduler::update_cc_info_target_velocity(uint32_t target_velocity_value) {
  unsigned int start_byte = 0;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 0U] = (target_velocity_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 1U] = (target_velocity_value >> 8U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 2U] = (target_velocity_value >> 16U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 3U] = (target_velocity_value >> 24U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update target_velocity");
  }
}
void CanScheduler::update_cc_info_drive_state(uint8_t drive_state_value) {
  unsigned int start_byte = 4;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 0U] = (drive_state_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update drive_state");
  }
}
void CanScheduler::update_cc_info_cruise_control(uint8_t cruise_control_value) {
  unsigned int start_byte = 5;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 0U] = (cruise_control_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update cruise_control");
  }
}
void CanScheduler::update_cc_info_regen_braking(uint8_t regen_braking_value) {
  unsigned int start_byte = 6;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 0U] = (regen_braking_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update regen_braking");
  }
}
void CanScheduler::update_cc_info_hazard_enabled(uint8_t hazard_enabled_value) {
  unsigned int start_byte = 7;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX].data[start_byte + 0U] = (hazard_enabled_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update hazard_enabled");
  }
}
void CanScheduler::update_cc_steering_input_cc(uint8_t input_cc_value) {
  unsigned int start_byte = 0;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX].data[start_byte + 0U] = (input_cc_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update input_cc");
  }
}
void CanScheduler::update_cc_steering_input_lights(uint8_t input_lights_value) {
  unsigned int start_byte = 1;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX].data[start_byte + 0U] = (input_lights_value >> 0U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update input_lights");
  }
}
void CanScheduler::update_cc_regen_percentage_percent(uint32_t percent_value) {
  unsigned int start_byte = 0;

  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].data[start_byte + 0U] = (percent_value >> 0U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].data[start_byte + 1U] = (percent_value >> 8U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].data[start_byte + 2U] = (percent_value >> 16U) & 0xFFU;
  canMediumCycleBCM.frame[MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX].data[start_byte + 3U] = (percent_value >> 24U) & 0xFFU;
  if (write(m_bcmCanSocket, &canMediumCycleBCM, sizeof(canMediumCycleBCM)) < 0) {
    throw std::runtime_error("Failed to update percent");
  }
}