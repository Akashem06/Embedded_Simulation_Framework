#include <sstream>
#include <vector>

#include "metadata.h"
#include "command_code.h"

std::string Metadata::serialize() const {
    std::stringstream serializedData;
    serializedData << m_metadata.projectName << "|"
                   << m_metadata.projectStatus << "|"
                   << m_metadata.hardwareModel << "|"
                   << m_metadata.projectRuntime;
    std::string metdataPayload = serializedData.str();
    return encodeCommand(CommandCode::METADATA, metdataPayload);
}

void Metadata::deserialize(std::string &metadataPayload) {
    std::vector<std::string> dataParts;
    std::string dataItem;
    std::stringstream serializedData(metadataPayload);

    while(std::getline(serializedData, dataItem, '|')) {
        dataParts.push_back(dataItem);
    }

    m_metadata.projectName = dataParts[0];
    m_metadata.projectStatus = dataParts[1];
    m_metadata.hardwareModel = dataParts[2];

    try {
        m_metadata.projectRuntime = std::stoi(dataParts[3]);
    } catch (const std::exception &e) {
        throw std::runtime_error("Invalid project runtime value");
    }
}

Metadata::Metadata(Payload &data) {
    m_metadata = data;
}

void Metadata::setProjectName(const std::string &projectName) {
    m_metadata.projectName = projectName;
}

void Metadata::setProjectStatus(const std::string &projectStatus) {
    m_metadata.projectStatus = projectStatus;
}

void Metadata::setHardwareModel(const std::string &hardwareModel) {
    m_metadata.hardwareModel = hardwareModel;
}

void Metadata::setProjectRuntime(const int &projectRuntime) {
    m_metadata.projectRuntime = projectRuntime;
}

std::string Metadata::getProjectName() const {
    return m_metadata.projectName;
}

std::string Metadata::getProjectStatus() const {
    return m_metadata.projectStatus;
}

std::string Metadata::getHardwareModel() const {
    return m_metadata.hardwareModel;
}

int Metadata::getProjectRuntime() const {
    return m_metadata.projectRuntime;
}

