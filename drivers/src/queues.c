/************************************************************************************************
 * @file   queues.c
 *
 * @brief  Queue Source file
 *
 * @date   2024-11-02
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <string.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "queues.h"

#define QUEUE_EMPTY 0U

void queue_init(Queue *queue) {
  if (queue == NULL || queue->storage_buf == NULL) {
    return;
  }

  queue->private_storage.head = 0U;
  queue->private_storage.tail = 0U;
  queue->private_storage.count = 0U;

  memset(queue->storage_buf, 0U, queue->item_size * queue->num_items);
}

void queue_send(Queue *queue, const void *item, uint32_t delay_ms) {
  if (queue == NULL || item == NULL || queue->storage_buf == NULL) {
    return;
  }

  if (queue->private_storage.count >= queue->num_items) {
    /* Full. Implement delay logic */
    return;
  }

  uint32_t write_pos = queue->private_storage.head * queue->item_size;
  memcpy(&queue->storage_buf[write_pos], item, queue->item_size);

  queue->private_storage.head = (queue->private_storage.head + 1U) % queue->num_items;
  queue->private_storage.count++;
}

void queue_send_from_isr(Queue *queue, const void *item, bool *higher_prio_woken) {
  if (queue == NULL || item == NULL || queue->storage_buf == NULL) {
    return;
  }

  if (queue->private_storage.count >= queue->num_items) {
    /* Full. Implement delay logic */
    return;
  }

  uint32_t write_pos = queue->private_storage.head * queue->item_size;
  memcpy(&queue->storage_buf[write_pos], item, queue->item_size);

  queue->private_storage.head = (queue->private_storage.head + 1U) % queue->num_items;
  queue->private_storage.count++;

  if (higher_prio_woken != NULL) {
    *higher_prio_woken = false; /* This should be set depending on your scheduler (FreeRTOS stuff) */
  }
}

void queue_receive(Queue *queue, void *buf, uint32_t delay_ms) {
  if (queue == NULL || buf == NULL || queue->storage_buf == NULL) {
    return;
  }

  if (queue->private_storage.count == QUEUE_EMPTY) {
    /* Empty. Implement delay logic */
    return;
  }

  uint32_t read_pos = queue->private_storage.tail * queue->item_size;
  memcpy(buf, &queue->storage_buf[read_pos], queue->item_size);

  queue->private_storage.tail = (queue->private_storage.tail + 1U) % queue->num_items;
  queue->private_storage.count--;
}

void queue_receive_from_isr(Queue *queue, void *buf, bool *higher_prio_woken) {
  if (queue == NULL || buf == NULL || queue->storage_buf == NULL) {
    return;
  }

  if (queue->private_storage.count == QUEUE_EMPTY) {
    /* Empty. Implement delay logic */
    return;
  }

  uint32_t read_pos = queue->private_storage.tail * queue->item_size;
  memcpy(buf, &queue->storage_buf[read_pos], queue->item_size);

  queue->private_storage.tail = (queue->private_storage.tail + 1U) % queue->num_items;
  queue->private_storage.count--;

  if (higher_prio_woken != NULL) {
    *higher_prio_woken = false; /* This should be set depending on your scheduler (FreeRTOS stuff) */
  }
}

void queue_peek(Queue *queue, void *buf, uint32_t delay_ms) {
  if (queue == NULL || buf == NULL || queue->storage_buf == NULL) {
    return;
  }

  uint32_t read_pos = queue->private_storage.tail * queue->item_size;
  memcpy(buf, &queue->storage_buf[read_pos], queue->item_size);
}

void queue_reset(Queue *queue) {
  if (queue == NULL || queue->storage_buf == NULL) {
    return;
  }

  queue->private_storage.head = 0U;
  queue->private_storage.tail = 0U;
  queue->private_storage.count = 0U;

  memset(queue->storage_buf, 0U, queue->item_size * queue->num_items);
}

uint32_t queue_get_num_items(Queue *queue) {
  if (queue == NULL) {
    return 0;
  }
  return queue->num_items;
}

uint32_t queue_get_spaces_available(Queue *queue) {
  if (queue == NULL) {
    return 0;
  }

  return (queue->num_items - queue->private_storage.count);
}
