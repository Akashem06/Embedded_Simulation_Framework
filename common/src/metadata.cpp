#include "metadata.h"

#include <cstring>
#include <vector>

#include "command_code.h"
#include "serialization.h"

namespace Datagram {

std::string Metadata::serialize() const {
  std::string serializedData;

  serializeString(serializedData, m_metadata.projectName);
  serializeString(serializedData, m_metadata.projectStatus);
  serializeString(serializedData, m_metadata.hardwareModel);
  serializeInteger<uint32_t>(serializedData, m_metadata.projectRuntime);

  return encodeCommand(CommandCode::METADATA, serializedData);
}

void Metadata::deserialize(std::string &metadataPayload) {
  size_t offset = 0;

  m_metadata.projectName = deserializeString(metadataPayload, offset);
  m_metadata.projectStatus = deserializeString(metadataPayload, offset);
  m_metadata.hardwareModel = deserializeString(metadataPayload, offset);
  m_metadata.projectRuntime = deserializeInteger<uint32_t>(metadataPayload, offset);
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
