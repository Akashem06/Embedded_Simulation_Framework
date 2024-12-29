/************************************************************************************************
 * @file   can_hw.c
 *
 * @brief  Source file for CAN HW Interface
 *
 * @date   2024-11-03
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <string.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "can_hw.h"

void can_hw_init(const CanQueue *rx_queue, const CanSettings *settings) {}

void can_hw_add_filter_in(uint32_t mask, uint32_t filter, bool extended) {}

CanHwBusStatus can_hw_bus_status(void) {
  return CAN_HW_BUS_STATUS_OK;
}

void can_hw_transmit(uint32_t id, bool extended, const uint8_t *data, size_t len) {}

bool can_hw_receive(uint32_t *id, bool *extended, uint64_t *data, size_t *len) {
  return true;
}
