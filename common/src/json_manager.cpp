#include <iostream>
#include "json_manager.h"

template <typename T>
nlohmann::json JSONManager<T>::createDefaultProjectJSON(const std::string &projectName) {
    return {
        {"project_name", projectName},
        {"version", PROJECT_VERSION}
    };
}

template <typename T>
void JSONManager<T>::loadGlobalJSON() {
    try {
        std::ifstream globalJSON(m_JSONPath);
        m_globalJSON = nlohmann::json::parse(globalJSON);
    } catch (const std::exception &e) {
        std::cerr << "Error loading global JSON: " << e.what() << std::endl;
    }
}

template <typename T>
void JSONManager<T>::saveGlobalJSON() {
    try {
        std::ofstream globalJSON(m_JSONPath);
        globalJSON << m_globalJSON.dump(4);
    } catch (const std::exception &e) {
        std::cerr << "Error saving global JSON: " << e.what() << std::endl;
    }
}

template <typename T>
JSONManager<T>::JSONManager() {
    m_JSONPath = DEFAULT_JSON_PATH;
    
    if (!std::filesystem::exists(m_JSONPath)) {
        /* Initialize global JSON */
        try {
            m_globalJSON = {
                {"version", "1.0.0"},
                {"projects", nlohmann::json::object()}
            };
            saveGlobalJSON();
        } catch (const std::exception &e) {
            std::cerr << "Error initializing global JSON: " << e.what() << std::endl;
        }
    }
}

template <typename T>
nlohmann::json &JSONManager<T>::getProjectJSON(const std::string &projectName) {
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

template <typename T>
void JSONManager<T>::setProjectValue(const std::string &projectName, const std::string &key, T value) {
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
T JSONManager<T>::getProjectValue(const std::string &projectName, const std::string &key) {
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

template class JSONManager<std::string>;
