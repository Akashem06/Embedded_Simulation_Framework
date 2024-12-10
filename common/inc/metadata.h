#ifndef METADATA_H
#define METADATA_H

#include <string>

namespace Datagram {
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

  std::string serialize() const;
  void deserialize(std::string &metadataPayload);

  void setProjectName(const std::string &projectName);
  void setProjectStatus(const std::string &projectStatus);
  void setHardwareModel(const std::string &hardwareModel);
  void setProjectRuntime(const int &projectRuntime);

  std::string getProjectName() const;
  std::string getProjectStatus() const;
  std::string getHardwareModel() const;
  int getProjectRuntime() const;

 private:
  Payload m_metadata;
};

}  // namespace Datagram
#endif
