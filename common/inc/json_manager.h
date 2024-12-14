#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#define DEFAULT_JSON_PATH "ProjectInfo.json"
#define PROJECT_VERSION "1.0.0"

class JSONManager {
 private:
  std::string m_JSONPath;
  nlohmann::json m_globalJSON;

  nlohmann::json createDefaultProjectJSON(const std::string &projectName);
  void loadGlobalJSON();
  void saveGlobalJSON();

 public:
  JSONManager();
  nlohmann::json &getProjectJSON(const std::string &projectName);

  template <typename T>
  void setProjectValue(const std::string &projectName, const std::string &key,
                       T value) {
    try {
      loadGlobalJSON();

      if (!m_globalJSON["projects"].contains(projectName)) {
        createDefaultProjectJSON(projectName);
      }

      m_globalJSON["projects"][projectName][key] = value;
      saveGlobalJSON();
    } catch (const std::exception &e) {
      std::cerr << "Error setting project value: " << e.what() << std::endl;
    }
  }

  template <typename T>
  T getProjectValue(const std::string &projectName, const std::string &key) {
    try {
      loadGlobalJSON();

      if (!m_globalJSON["projects"].contains(projectName)) {
        throw std::runtime_error("Project not found " + projectName);
      }

      return m_globalJSON["projects"][projectName].at(key).get<T>();
    } catch (const std::exception &e) {
      std::cerr << "Error getting project value: " << e.what() << std::endl;
    }

    return static_cast<T>(0U);
  }
};

#endif
