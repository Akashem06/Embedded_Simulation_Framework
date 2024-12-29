#include "i2c.h"

#include "queues.h"

// void i2c_set_data(I2CPort i2c, uint8_t *tx_data, size_t tx_len) {
//   for (size_t tx = 0; tx < tx_len; tx++) {
//     if (queue_send(&s_port[i2c].i2c_rx_buf.queue, &tx_data[tx], 0)) {
//       queue_reset(&s_port[i2c].i2c_rx_buf.queue);
//       return STATUS_CODE_RESOURCE_EXHAUSTED;
//     }
//   }
// }

// void i2c_get_data(I2CPort i2c, uint8_t *rx_data, size_t rx_len) {
//   for (size_t rx = 0; rx < rx_len; rx++) {
//     if (queue_receive(&s_port[i2c].i2c_tx_buf.queue, &rx_data[rx], 0)) {
//       queue_reset(&s_port[i2c].i2c_tx_buf.queue);
//       return STATUS_CODE_INTERNAL_ERROR;
//     }
//   }
// }
