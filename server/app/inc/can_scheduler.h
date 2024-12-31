#ifndef CAN_SCHEDULER_H
#define CAN_SCHEDULER_H

/** @warning  This file is autogenerated */

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

class CanScheduler {
 private:
  const std::string CAN_INTERFACE_NAME = "vcan0";

  static const constexpr unsigned int FAST_CYCLE_SPEED_MS = 1U;
  static const constexpr unsigned int MEDIUM_CYCLE_SPEED_MS = 100U;
  static const constexpr unsigned int SLOW_CYCLE_SPEED_MS = 1000U;

  static const constexpr unsigned int SLOW_CYCLE_BCM_ID = 0U;
  static const constexpr unsigned int MEDIUM_CYCLE_BCM_ID = 1U;
  static const constexpr unsigned int FAST_CYCLE_BCM_ID = 2U;

  static const constexpr unsigned int NUM_FAST_CYCLE_MESSAGES = 3U;
  static const constexpr unsigned int NUM_MEDIUM_CYCLE_MESSAGES = 5U;
  static const constexpr unsigned int NUM_SLOW_CYCLE_MESSAGES = 5U;
  static const constexpr unsigned int NUM_TOTAL_MESSAGES = 13U;
  static const constexpr unsigned int MAX_MESSAGE_LENGTH = 8U;

  static const constexpr unsigned int FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX = 0U;
  static const constexpr unsigned int FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX = 1U;
  static const constexpr unsigned int FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX = 2U;

  static const constexpr unsigned int MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX = 0U;
  static const constexpr unsigned int MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX = 1U;
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX = 2U;
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX = 3U;
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX = 4U;

  static const constexpr unsigned int SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX = 0U;
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX = 1U;
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX = 2U;
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX = 3U;
  static const constexpr unsigned int SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX = 4U;

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_FAST_CYCLE_MESSAGES];
  } canFastCycleBCM;

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_MEDIUM_CYCLE_MESSAGES];
  } canMediumCycleBCM;

  struct {
    struct bcm_msg_head msg_head;
    struct can_frame frame[NUM_SLOW_CYCLE_MESSAGES];
  } canSlowCycleBCM;

  int m_bcmCanSocket;

  std::atomic<bool> m_isConnected;

 public:
  CanScheduler();

  void startCanScheduler();
  void scheduleCanMessages();
  void update_battery_status_fault(uint16_t fault_value);
  void update_battery_status_fault_val(uint16_t fault_val_value);
  void update_battery_status_aux_batt_v(uint16_t aux_batt_v_value);
  void update_battery_status_afe_status(uint8_t afe_status_value);
  void update_battery_vt_voltage(uint16_t voltage_value);
  void update_battery_vt_current(uint16_t current_value);
  void update_battery_vt_temperature(uint16_t temperature_value);
  void update_battery_vt_batt_perc(uint16_t batt_perc_value);
  void update_battery_info_fan1(uint8_t fan1_value);
  void update_battery_info_fan2(uint8_t fan2_value);
  void update_battery_info_max_cell_v(uint16_t max_cell_v_value);
  void update_battery_info_min_cell_v(uint16_t min_cell_v_value);
  void update_afe1_status_id(uint8_t id_value);
  void update_afe1_status_temp(uint8_t temp_value);
  void update_afe1_status_v1(uint16_t v1_value);
  void update_afe1_status_v2(uint16_t v2_value);
  void update_afe1_status_v3(uint16_t v3_value);
  void update_afe2_status_id(uint8_t id_value);
  void update_afe2_status_temp(uint8_t temp_value);
  void update_afe2_status_v1(uint16_t v1_value);
  void update_afe2_status_v2(uint16_t v2_value);
  void update_afe2_status_v3(uint16_t v3_value);
  void update_afe3_status_id(uint8_t id_value);
  void update_afe3_status_temp(uint8_t temp_value);
  void update_afe3_status_v1(uint16_t v1_value);
  void update_afe3_status_v2(uint16_t v2_value);
  void update_afe3_status_v3(uint16_t v3_value);
  void update_fast_one_shot_msg_sig1(uint16_t sig1_value);
  void update_fast_one_shot_msg_sig2(uint16_t sig2_value);
  void update_medium_one_shot_msg_sig1(uint16_t sig1_value);
  void update_medium_one_shot_msg_sig2(uint16_t sig2_value);
  void update_slow_one_shot_msg_sig1(uint16_t sig1_value);
  void update_slow_one_shot_msg_sig2(uint16_t sig2_value);
  void update_cc_pedal_throttle_output(uint32_t throttle_output_value);
  void update_cc_pedal_brake_output(uint8_t brake_output_value);
  void update_cc_info_target_velocity(uint32_t target_velocity_value);
  void update_cc_info_drive_state(uint8_t drive_state_value);
  void update_cc_info_cruise_control(uint8_t cruise_control_value);
  void update_cc_info_regen_braking(uint8_t regen_braking_value);
  void update_cc_info_hazard_enabled(uint8_t hazard_enabled_value);
  void update_cc_steering_input_cc(uint8_t input_cc_value);
  void update_cc_steering_input_lights(uint8_t input_lights_value);
  void update_cc_regen_percentage_percent(uint32_t percent_value);
};

#endif