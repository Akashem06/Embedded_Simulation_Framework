#include "json_manager.h"

nlohmann::json JSONManager::createDefaultProjectJSON(const std::string &projectName) {
  return {{"project_name", projectName}, {"version", PROJECT_VERSION}};
}

void JSONManager::loadGlobalJSON() {
  try {
    std::ifstream globalJSON(m_JSONPath);
    m_globalJSON = nlohmann::json::parse(globalJSON);
  } catch (const std::exception &e) {
    std::cerr << "Error loading global JSON: " << e.what() << std::endl;
  }
}

void JSONManager::saveGlobalJSON() {
  try {
    std::ofstream globalJSON(m_JSONPath);
    globalJSON << m_globalJSON.dump(2);
  } catch (const std::exception &e) {
    std::cerr << "Error saving global JSON: " << e.what() << std::endl;
  }
}

JSONManager::JSONManager() {
  m_JSONPath = DEFAULT_JSON_PATH;

  try {
    m_globalJSON = {{"version", "1.0.0"}, {"projects", nlohmann::json::object()}};
    saveGlobalJSON();
  } catch (const std::exception &e) {
    std::cerr << "Error initializing global JSON: " << e.what() << std::endl;
  }
}

nlohmann::json &JSONManager::getProjectJSON(const std::string &projectName) {
  try {
    loadGlobalJSON();

    if (!m_globalJSON["projects"].contains(projectName)) {
      m_globalJSON["projects"][projectName] = createDefaultProjectJSON(projectName);
      saveGlobalJSON();
    }

    return m_globalJSON["projects"][projectName];
  } catch (const std::exception &e) {
    std::cerr << "Error getting project JSON: " << e.what() << std::endl;
  }

  return m_globalJSON;
}
