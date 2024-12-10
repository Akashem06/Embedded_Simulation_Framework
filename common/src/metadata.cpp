#include "metadata.h"

#include <cstring>
#include <vector>

#include "command_code.h"

namespace Datagram {

std::string Metadata::serialize() const {
  std::string serializedData;

  uint16_t nameLength = m_metadata.projectName.length();
  serializedData.append(reinterpret_cast<const char *>(&nameLength),
                        sizeof(nameLength));
  serializedData.append(m_metadata.projectName);

  uint16_t statusLength = m_metadata.projectStatus.length();
  serializedData.append(reinterpret_cast<const char *>(&statusLength),
                        sizeof(statusLength));
  serializedData.append(m_metadata.projectStatus);

  uint16_t modelLength = m_metadata.hardwareModel.length();
  serializedData.append(reinterpret_cast<const char *>(&modelLength),
                        sizeof(modelLength));
  serializedData.append(m_metadata.hardwareModel);

  uint32_t runtime = static_cast<uint32_t>(m_metadata.projectRuntime);
  serializedData.append(reinterpret_cast<const char *>(&runtime),
                        sizeof(runtime));

  return encodeCommand(CommandCode::METADATA, serializedData);
}

void Metadata::deserialize(std::string &metadataPayload) {
  size_t offset = 0;

  uint16_t nameLength;
  std::memcpy(&nameLength, metadataPayload.data() + offset, sizeof(nameLength));
  offset += sizeof(nameLength);

  m_metadata.projectName = metadataPayload.substr(offset, nameLength);
  offset += nameLength;

  uint16_t statusLength;
  std::memcpy(&statusLength, metadataPayload.data() + offset,
              sizeof(statusLength));
  offset += sizeof(statusLength);

  m_metadata.projectStatus = metadataPayload.substr(offset, statusLength);
  offset += statusLength;

  uint16_t modelLength;
  std::memcpy(&modelLength, metadataPayload.data() + offset,
              sizeof(modelLength));
  offset += sizeof(modelLength);

  m_metadata.hardwareModel = metadataPayload.substr(offset, modelLength);
  offset += modelLength;

  uint32_t runtime;
  std::memcpy(&runtime, metadataPayload.data() + offset, sizeof(runtime));
  m_metadata.projectRuntime = static_cast<int>(runtime);
}

Metadata::Metadata(Payload &data) { m_metadata = data; }

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

std::string Metadata::getProjectName() const { return m_metadata.projectName; }

std::string Metadata::getProjectStatus() const {
  return m_metadata.projectStatus;
}

std::string Metadata::getHardwareModel() const {
  return m_metadata.hardwareModel;
}

int Metadata::getProjectRuntime() const { return m_metadata.projectRuntime; }
}  // namespace Datagram
