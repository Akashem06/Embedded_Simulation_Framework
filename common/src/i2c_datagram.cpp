#include "i2c_datagram.h"

#include <cstring>
#include <sstream>
#include <vector>

namespace Datagram {

I2C::I2C(Payload &data) { m_i2cDatagram = data; }

std::string I2C::serialize(const CommandCode &commandCode) const {}

void I2C::deserialize(std::string &i2cDatagramPayload) {}

void I2C::setI2CPort(const Port &i2cPort) { m_i2cDatagram.i2cPort = i2cPort; }

void I2C::setBuffer(const uint8_t *data, size_t length) {
  std::memcpy(m_i2cDatagram.buffer, data, length);
  m_i2cDatagram.bufferLength = length;
}

void I2C::clearBuffer() {
  std::memset(m_i2cDatagram.buffer, 0U, MAX_BUFFER_SIZE);
}

I2C::Port I2C::getI2CPort() const { return m_i2cDatagram.i2cPort; }

size_t I2C::getBufferLength() const { return m_i2cDatagram.bufferLength; }

const uint8_t *I2C::getBuffer() const { return m_i2cDatagram.buffer; }

}  // namespace Datagram
