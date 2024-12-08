#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#define DEFAULT_JSON_PATH       "ProjectInfo.json"
#define PROJECT_VERSION         "1.0.0"

template <typename T>
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
        void setProjectValue(const std::string &projectName, const std::string &key, T value);
        T getProjectValue(const std::string &projectName, const std::string &key);
};

#endif
