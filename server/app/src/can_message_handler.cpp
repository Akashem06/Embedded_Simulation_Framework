#include <cstdint>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "can_manager.h"
#include "system_can.h"

struct battery_status {
  uint16_t fault;
  uint16_t fault_val;
  uint16_t aux_batt_v;
  uint8_t afe_status;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      fault = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      fault_val = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      aux_batt_v = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      afe_status = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"fault", fault}, {"fault_val", fault_val}, {"aux_batt_v", aux_batt_v}, {"afe_status", afe_status}};
  }

  std::string get_message_name() const {
    return "battery_status";
  }
};
struct battery_vt {
  uint16_t voltage;
  uint16_t current;
  uint16_t temperature;
  uint16_t batt_perc;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      voltage = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      current = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      temperature = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      batt_perc = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"voltage", voltage}, {"current", current}, {"temperature", temperature}, {"batt_perc", batt_perc}};
  }

  std::string get_message_name() const {
    return "battery_vt";
  }
};
struct battery_info {
  uint8_t fan1;
  uint8_t fan2;
  uint16_t max_cell_v;
  uint16_t min_cell_v;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      fan1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 1;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      fan2 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      max_cell_v = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      min_cell_v = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"fan1", fan1}, {"fan2", fan2}, {"max_cell_v", max_cell_v}, {"min_cell_v", min_cell_v}};
  }

  std::string get_message_name() const {
    return "battery_info";
  }
};
struct afe1_status {
  uint8_t id;
  uint8_t temp;
  uint16_t v1;
  uint16_t v2;
  uint16_t v3;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      id = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 1;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      temp = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v2 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v3 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"id", id}, {"temp", temp}, {"v1", v1}, {"v2", v2}, {"v3", v3}};
  }

  std::string get_message_name() const {
    return "AFE1_status";
  }
};
struct afe2_status {
  uint8_t id;
  uint8_t temp;
  uint16_t v1;
  uint16_t v2;
  uint16_t v3;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      id = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 1;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      temp = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v2 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v3 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"id", id}, {"temp", temp}, {"v1", v1}, {"v2", v2}, {"v3", v3}};
  }

  std::string get_message_name() const {
    return "AFE2_status";
  }
};
struct afe3_status {
  uint8_t id;
  uint8_t temp;
  uint16_t v1;
  uint16_t v2;
  uint16_t v3;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      id = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 1;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      temp = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v2 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      v3 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"id", id}, {"temp", temp}, {"v1", v1}, {"v2", v2}, {"v3", v3}};
  }

  std::string get_message_name() const {
    return "AFE3_status";
  }
};
struct fast_one_shot_msg {
  uint16_t sig1;
  uint16_t sig2;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig2 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"sig1", sig1}, {"sig2", sig2}};
  }

  std::string get_message_name() const {
    return "fast_one_shot_msg";
  }
};
struct medium_one_shot_msg {
  uint16_t sig1;
  uint16_t sig2;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig2 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"sig1", sig1}, {"sig2", sig2}};
  }

  std::string get_message_name() const {
    return "medium_one_shot_msg";
  }
};
struct slow_one_shot_msg {
  uint16_t sig1;
  uint16_t sig2;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig1 = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 2;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      sig2 = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"sig1", sig1}, {"sig2", sig2}};
  }

  std::string get_message_name() const {
    return "slow_one_shot_msg";
  }
};
struct cc_pedal {
  uint32_t throttle_output;
  uint8_t brake_output;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 2]) << 16U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 3]) << 24U;
      throttle_output = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      brake_output = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"throttle_output", throttle_output}, {"brake_output", brake_output}};
  }

  std::string get_message_name() const {
    return "cc_pedal";
  }
};
struct cc_info {
  uint32_t target_velocity;
  uint8_t drive_state;
  uint8_t cruise_control;
  uint8_t regen_braking;
  uint8_t hazard_enabled;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 2]) << 16U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 3]) << 24U;
      target_velocity = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 4;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      drive_state = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 5;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      cruise_control = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 6;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      regen_braking = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 7;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      hazard_enabled = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"target_velocity", target_velocity},
            {"drive_state", drive_state},
            {"cruise_control", cruise_control},
            {"regen_braking", regen_braking},
            {"hazard_enabled", hazard_enabled}};
  }

  std::string get_message_name() const {
    return "cc_info";
  }
};
struct cc_steering {
  uint8_t input_cc;
  uint8_t input_lights;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      input_cc = raw_val;
    }
    {
      raw_val = 0U;
      start_byte = 1;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      input_lights = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"input_cc", input_cc}, {"input_lights", input_lights}};
  }

  std::string get_message_name() const {
    return "cc_steering";
  }
};
struct cc_regen_percentage {
  uint32_t percent;

  void decode(const uint8_t *data) {
    uint64_t raw_val = 0U;
    uint8_t start_byte = 0U;
    {
      raw_val = 0U;
      start_byte = 0;
      raw_val |= static_cast<uint64_t>(data[start_byte + 0]) << 0U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 1]) << 8U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 2]) << 16U;
      raw_val |= static_cast<uint64_t>(data[start_byte + 3]) << 24U;
      percent = raw_val;
    }
  }

  nlohmann::json to_json() const {
    return {{"percent", percent}};
  }

  std::string get_message_name() const {
    return "cc_regen_percentage";
  }
};

void CanManager::canMessageHandler(uint32_t id, const uint8_t *data) {
  switch (id) {
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_STATUS: {
      battery_status *message = new battery_status();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_VT: {
      battery_vt *message = new battery_vt();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_BATTERY_INFO: {
      battery_info *message = new battery_info();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE1_STATUS: {
      afe1_status *message = new afe1_status();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE2_STATUS: {
      afe2_status *message = new afe2_status();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_BMS_CARRIER_AFE3_STATUS: {
      afe3_status *message = new afe3_status();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_FAST_ONE_SHOT_MSG: {
      fast_one_shot_msg *message = new fast_one_shot_msg();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_MEDIUM_ONE_SHOT_MSG: {
      medium_one_shot_msg *message = new medium_one_shot_msg();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CAN_COMMUNICATION_SLOW_ONE_SHOT_MSG: {
      slow_one_shot_msg *message = new slow_one_shot_msg();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_PEDAL: {
      cc_pedal *message = new cc_pedal();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_INFO: {
      cc_info *message = new cc_info();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_STEERING: {
      cc_steering *message = new cc_steering();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    case SYSTEM_CAN_MESSAGE_CENTRE_CONSOLE_CC_REGEN_PERCENTAGE: {
      cc_regen_percentage *message = new cc_regen_percentage();
      message->decode(data);
      m_canInfo[message->get_message_name()] = message->to_json();
      break;
    }
    default: {
      std::cout << "Unknown message ID: " << static_cast<int>(id) << std::endl;
    }
  }
}