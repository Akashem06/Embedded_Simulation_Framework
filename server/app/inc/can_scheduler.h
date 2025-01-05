#pragma once

/************************************************************************************************
 * @file   can_scheduler.h
 *
 * @brief  Header file defining the CanScheduler class
 *
 * @date   2025-01-04
 * @author Aryan Kashem
 ************************************************************************************************/

/** @warning  This file is autogenerated */

/* Standard library Headers */
#include <atomic>
#include <string>

/* Inter-component Headers */
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/bcm.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Intra-component Headers */

/**
 * @defgroup CanScheduler
 * @brief    SocketCAN Broadcast Manager abstraction class
 * @{
 */

/**
 * @class   CanScheduler
 * @brief   Class that handles message scheduling over a SocketCAN interface
 * @details This class is responsible scheduling CAN messages based on their cycle speed
 *          Only 3 cycle speeds are supported, Fast (1kHz), medium (10Hz) and slow (1Hz)
 *          The class shall support message updating during run-time for further bus simulation
 */
class CanScheduler {
 private:
  const std::string CAN_INTERFACE_NAME = "vcan0";                   /**< SocketCAN interface name */

  static const constexpr unsigned int FAST_CYCLE_SPEED_MS = 1U;     /**< CAN fast cycle period in milliseconds */
  static const constexpr unsigned int MEDIUM_CYCLE_SPEED_MS = 100U; /**< CAN medium cycle period in milliseconds */
  static const constexpr unsigned int SLOW_CYCLE_SPEED_MS = 1000U;  /**< CAN slow cycle period in milliseconds */

  static const constexpr unsigned int SLOW_CYCLE_BCM_ID = 0U;       /**< Linux Broadcast Manager Id for tracking fast cycle messages */
  static const constexpr unsigned int MEDIUM_CYCLE_BCM_ID = 1U;     /**< Linux Broadcast Manager Id for tracking medium cycle messages */
  static const constexpr unsigned int FAST_CYCLE_BCM_ID = 2U;       /**< Linux Broadcast Manager Id for tracking slow cycle messages */

  static const constexpr unsigned int NUM_FAST_CYCLE_MESSAGES = 3U; /**< Number of fast cycle messages */
  static const constexpr unsigned int NUM_MEDIUM_CYCLE_MESSAGES = 5U; /**< Number of medium cycle messages */
  static const constexpr unsigned int NUM_SLOW_CYCLE_MESSAGES = 5U; /**< Number of slow cycle messages */
  static const constexpr unsigned int NUM_TOTAL_MESSAGES = 13U; /**< Total number of messages */
  static const constexpr unsigned int MAX_MESSAGE_LENGTH = 8U; /**< Max message length in bytes */

  
  static const constexpr unsigned int FAST_BMS_CARRIER_BATTERY_VT_FRAME_INDEX = 0U; /**< Broadcast Manager battery_vt to Frame index mapping */
  static const constexpr unsigned int FAST_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG_FRAME_INDEX = 1U; /**< Broadcast Manager fast_one_shot_msg to Frame index mapping */
  static const constexpr unsigned int FAST_CENTRE_CONSOLE_CC_PEDAL_FRAME_INDEX = 2U; /**< Broadcast Manager cc_pedal to Frame index mapping */

  
  static const constexpr unsigned int MEDIUM_BMS_CARRIER_BATTERY_STATUS_FRAME_INDEX = 0U; /**< Broadcast Manager battery_status to Frame index mapping */
  static const constexpr unsigned int MEDIUM_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG_FRAME_INDEX = 1U; /**< Broadcast Manager medium_one_shot_msg to Frame index mapping */
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_INFO_FRAME_INDEX = 2U; /**< Broadcast Manager cc_info to Frame index mapping */
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_STEERING_FRAME_INDEX = 3U; /**< Broadcast Manager cc_steering to Frame index mapping */
  static const constexpr unsigned int MEDIUM_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE_FRAME_INDEX = 4U; /**< Broadcast Manager cc_regen_percentage to Frame index mapping */

  
  static const constexpr unsigned int SLOW_BMS_CARRIER_BATTERY_INFO_FRAME_INDEX = 0U; /**< Broadcast Manager battery_info to Frame index mapping */
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE1_STATUS_FRAME_INDEX = 1U; /**< Broadcast Manager afe1_status to Frame index mapping */
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE2_STATUS_FRAME_INDEX = 2U; /**< Broadcast Manager afe2_status to Frame index mapping */
  static const constexpr unsigned int SLOW_BMS_CARRIER_AFE3_STATUS_FRAME_INDEX = 3U; /**< Broadcast Manager afe3_status to Frame index mapping */
  static const constexpr unsigned int SLOW_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG_FRAME_INDEX = 4U; /**< Broadcast Manager slow_one_shot_msg to Frame index mapping */

  /**
   * @brief   Fast cycle Broadcast Manager message for the Linux Kernel
   */
  struct {
    struct bcm_msg_head msg_head;                       /**< Broadcast Manager message head containing metadata */
    struct can_frame frame[NUM_FAST_CYCLE_MESSAGES];    /**< CAN message frames that shall be scheduled for fast cycle */
  } canFastCycleBCM;

  /**
   * @brief   Medium cycle Broadcast Manager message for the Linux Kernel
   */
  struct {
    struct bcm_msg_head msg_head;                       /**< Broadcast Manager message head containing metadata */
    struct can_frame frame[NUM_MEDIUM_CYCLE_MESSAGES];  /**< CAN message frames that shall be scheduled for medium cycle */
  } canMediumCycleBCM;

  /**
   * @brief   Slow cycle Broadcast Manager message for the Linux Kernel
   */
  struct {
    struct bcm_msg_head msg_head;                       /**< Broadcast Manager message head containing metadata */
    struct can_frame frame[NUM_SLOW_CYCLE_MESSAGES];    /**< CAN message frames that shall be scheduled for slow cycle */
  } canSlowCycleBCM;

  int m_bcmCanSocket;               /**< The CAN schedulers Broadcast Manager socket FD */
  std::atomic<bool> m_isConnected;  /**< Boolean flag to track the CAN schedulers connection status */

  /**
   * @brief   Schedules all CAN data by updating the Broacast Manager socket
   * @details This function is called by startCanScheduler
   *          This function shall initialize all CAN message values to 0
   */
  void scheduleCanMessages();

 public:
  /**
   * @brief   Constructs a CanScheduler object
   * @details Initializes the CanScheduler. The constructor sets up internal variables
   */
  CanScheduler();

  /**
   * @brief   Starts the CAN scheduler and sets all messages to 0. Must only be called once
   * @details This function will connect to the Linux Broadcast Manager
   *          This function must only be called once, and it will set all messages to 0
   */
  void startCanScheduler();
  /**
   * @brief   Update the CAN value for battery_status fault
   * @param   fault_value New value for the signal
   */
  void update_battery_status_fault(uint16_t fault_value);
  /**
   * @brief   Update the CAN value for battery_status fault_val
   * @param   fault_val_value New value for the signal
   */
  void update_battery_status_fault_val(uint16_t fault_val_value);
  /**
   * @brief   Update the CAN value for battery_status aux_batt_v
   * @param   aux_batt_v_value New value for the signal
   */
  void update_battery_status_aux_batt_v(uint16_t aux_batt_v_value);
  /**
   * @brief   Update the CAN value for battery_status afe_status
   * @param   afe_status_value New value for the signal
   */
  void update_battery_status_afe_status(uint8_t afe_status_value);
  /**
   * @brief   Update the CAN value for battery_vt voltage
   * @param   voltage_value New value for the signal
   */
  void update_battery_vt_voltage(uint16_t voltage_value);
  /**
   * @brief   Update the CAN value for battery_vt current
   * @param   current_value New value for the signal
   */
  void update_battery_vt_current(uint16_t current_value);
  /**
   * @brief   Update the CAN value for battery_vt temperature
   * @param   temperature_value New value for the signal
   */
  void update_battery_vt_temperature(uint16_t temperature_value);
  /**
   * @brief   Update the CAN value for battery_vt batt_perc
   * @param   batt_perc_value New value for the signal
   */
  void update_battery_vt_batt_perc(uint16_t batt_perc_value);
  /**
   * @brief   Update the CAN value for battery_info fan1
   * @param   fan1_value New value for the signal
   */
  void update_battery_info_fan1(uint8_t fan1_value);
  /**
   * @brief   Update the CAN value for battery_info fan2
   * @param   fan2_value New value for the signal
   */
  void update_battery_info_fan2(uint8_t fan2_value);
  /**
   * @brief   Update the CAN value for battery_info max_cell_v
   * @param   max_cell_v_value New value for the signal
   */
  void update_battery_info_max_cell_v(uint16_t max_cell_v_value);
  /**
   * @brief   Update the CAN value for battery_info min_cell_v
   * @param   min_cell_v_value New value for the signal
   */
  void update_battery_info_min_cell_v(uint16_t min_cell_v_value);
  /**
   * @brief   Update the CAN value for afe1_status id
   * @param   id_value New value for the signal
   */
  void update_afe1_status_id(uint8_t id_value);
  /**
   * @brief   Update the CAN value for afe1_status temp
   * @param   temp_value New value for the signal
   */
  void update_afe1_status_temp(uint8_t temp_value);
  /**
   * @brief   Update the CAN value for afe1_status v1
   * @param   v1_value New value for the signal
   */
  void update_afe1_status_v1(uint16_t v1_value);
  /**
   * @brief   Update the CAN value for afe1_status v2
   * @param   v2_value New value for the signal
   */
  void update_afe1_status_v2(uint16_t v2_value);
  /**
   * @brief   Update the CAN value for afe1_status v3
   * @param   v3_value New value for the signal
   */
  void update_afe1_status_v3(uint16_t v3_value);
  /**
   * @brief   Update the CAN value for afe2_status id
   * @param   id_value New value for the signal
   */
  void update_afe2_status_id(uint8_t id_value);
  /**
   * @brief   Update the CAN value for afe2_status temp
   * @param   temp_value New value for the signal
   */
  void update_afe2_status_temp(uint8_t temp_value);
  /**
   * @brief   Update the CAN value for afe2_status v1
   * @param   v1_value New value for the signal
   */
  void update_afe2_status_v1(uint16_t v1_value);
  /**
   * @brief   Update the CAN value for afe2_status v2
   * @param   v2_value New value for the signal
   */
  void update_afe2_status_v2(uint16_t v2_value);
  /**
   * @brief   Update the CAN value for afe2_status v3
   * @param   v3_value New value for the signal
   */
  void update_afe2_status_v3(uint16_t v3_value);
  /**
   * @brief   Update the CAN value for afe3_status id
   * @param   id_value New value for the signal
   */
  void update_afe3_status_id(uint8_t id_value);
  /**
   * @brief   Update the CAN value for afe3_status temp
   * @param   temp_value New value for the signal
   */
  void update_afe3_status_temp(uint8_t temp_value);
  /**
   * @brief   Update the CAN value for afe3_status v1
   * @param   v1_value New value for the signal
   */
  void update_afe3_status_v1(uint16_t v1_value);
  /**
   * @brief   Update the CAN value for afe3_status v2
   * @param   v2_value New value for the signal
   */
  void update_afe3_status_v2(uint16_t v2_value);
  /**
   * @brief   Update the CAN value for afe3_status v3
   * @param   v3_value New value for the signal
   */
  void update_afe3_status_v3(uint16_t v3_value);
  /**
   * @brief   Update the CAN value for fast_one_shot_msg sig1
   * @param   sig1_value New value for the signal
   */
  void update_fast_one_shot_msg_sig1(uint16_t sig1_value);
  /**
   * @brief   Update the CAN value for fast_one_shot_msg sig2
   * @param   sig2_value New value for the signal
   */
  void update_fast_one_shot_msg_sig2(uint16_t sig2_value);
  /**
   * @brief   Update the CAN value for medium_one_shot_msg sig1
   * @param   sig1_value New value for the signal
   */
  void update_medium_one_shot_msg_sig1(uint16_t sig1_value);
  /**
   * @brief   Update the CAN value for medium_one_shot_msg sig2
   * @param   sig2_value New value for the signal
   */
  void update_medium_one_shot_msg_sig2(uint16_t sig2_value);
  /**
   * @brief   Update the CAN value for slow_one_shot_msg sig1
   * @param   sig1_value New value for the signal
   */
  void update_slow_one_shot_msg_sig1(uint16_t sig1_value);
  /**
   * @brief   Update the CAN value for slow_one_shot_msg sig2
   * @param   sig2_value New value for the signal
   */
  void update_slow_one_shot_msg_sig2(uint16_t sig2_value);
  /**
   * @brief   Update the CAN value for cc_pedal throttle_output
   * @param   throttle_output_value New value for the signal
   */
  void update_cc_pedal_throttle_output(uint32_t throttle_output_value);
  /**
   * @brief   Update the CAN value for cc_pedal brake_output
   * @param   brake_output_value New value for the signal
   */
  void update_cc_pedal_brake_output(uint8_t brake_output_value);
  /**
   * @brief   Update the CAN value for cc_info target_velocity
   * @param   target_velocity_value New value for the signal
   */
  void update_cc_info_target_velocity(uint32_t target_velocity_value);
  /**
   * @brief   Update the CAN value for cc_info drive_state
   * @param   drive_state_value New value for the signal
   */
  void update_cc_info_drive_state(uint8_t drive_state_value);
  /**
   * @brief   Update the CAN value for cc_info cruise_control
   * @param   cruise_control_value New value for the signal
   */
  void update_cc_info_cruise_control(uint8_t cruise_control_value);
  /**
   * @brief   Update the CAN value for cc_info regen_braking
   * @param   regen_braking_value New value for the signal
   */
  void update_cc_info_regen_braking(uint8_t regen_braking_value);
  /**
   * @brief   Update the CAN value for cc_info hazard_enabled
   * @param   hazard_enabled_value New value for the signal
   */
  void update_cc_info_hazard_enabled(uint8_t hazard_enabled_value);
  /**
   * @brief   Update the CAN value for cc_steering input_cc
   * @param   input_cc_value New value for the signal
   */
  void update_cc_steering_input_cc(uint8_t input_cc_value);
  /**
   * @brief   Update the CAN value for cc_steering input_lights
   * @param   input_lights_value New value for the signal
   */
  void update_cc_steering_input_lights(uint8_t input_lights_value);
  /**
   * @brief   Update the CAN value for cc_regen_percentage percent
   * @param   percent_value New value for the signal
   */
  void update_cc_regen_percentage_percent(uint32_t percent_value);
};

/** @} */