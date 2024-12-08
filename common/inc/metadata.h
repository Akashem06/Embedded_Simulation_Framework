#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <chrono>
#include <ctime>

#define METADATA_HEADER "METADATA"

class Metadata {
    public:
        struct Payload {
            std::string projectName;
            std::string projectStatus;
            std::string hardwareModel;
            
            int projectRuntime;
        };
        explicit Metadata(Payload &data);
        Metadata() = default;

        void setProjectName(const std::string &projectName);
        void setProjectStatus(const std::string &projectStatus);
        void setHardwareModel(const std::string &hardwareModel);
        void setProjectRuntime(const int &projectRuntime);

        std::string getProjectName() const;
        std::string getProjectStatus() const;
        std::string getHardwareModel() const;
        int getProjectRuntime() const;

        std::string serialize() const;
        void deserialize(std::string &data);

        private:
            Payload m_metadata;
};

#endif
