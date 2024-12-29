#ifndef QUEUES_H
#define QUEUES_H

/************************************************************************************************
 * @file   queues.h
 *
 * @brief  Queue Header file
 *
 * @date   2024-11-02
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup Queues
 * @brief    Queue library
 * @{
 */

/**
 * @brief   Queue storage and access struct
 */
typedef struct {
  uint32_t num_items;   /**< Number of items the queue can hold */
  uint32_t item_size;   /**< Size of each item */
  uint8_t *storage_buf; /**< Must be declared statically, and have size num_items*item_size */
} Queue;

/**
 * @brief   Create a queue with the parameters specified in settings
 * @param   queue Pointer to queue handle
 */
void queue_init(Queue *queue);

/**
 * @brief   Place an item into the queue, delaying for delay_ms before timing out
 * @param   queue Pointer to queue handle
 * @param   item Pointer to the item sent to the queue
 * @param   delay_ms Time in milliseconds to wait for space in the queue before timing out
 */
void queue_send(Queue *queue, const void *item, uint32_t delay_ms);

/**
 * @brief   Place an item into the queue from an ISR
 * @param   queue Pointer to queue handle
 * @param   item Pointer to the item sent to the queue
 * @param   higher_prio_woken Boolean to indicate a context switch after exiting the ISR
 */
void queue_send_from_isr(Queue *queue, const void *item, bool *higher_prio_woken);

/**
 * @brief   Retrieve an item from the queue, delaying for delay_ms before timing out
 * @param   queue Pointer to queue handle
 * @param   item Pointer to the buffer to fill from the queue
 * @param   delay_ms Time in milliseconds to wait for data in the queue before timing out
 */
void queue_receive(Queue *queue, void *buf, uint32_t delay_ms);

/**
 * @brief   Retrieve an item from the queue, delaying for delay_ms before timing out
 * @param   queue Pointer to queue handle
 * @param   item Pointer to the buffer to fill from the queue
 * @param   higher_prio_woken Boolean to indicate a context switch after exiting the ISR
 */
void queue_receive_from_isr(Queue *queue, void *buf, bool *higher_prio_woken);

// Attempt to receive an item from the queue without removing it from the queue, delaying for
// delay_ms in ms before timing out.

/**
 * @brief   Receive an item from the queue without removing it
 * @param   queue Pointer to queue handle
 * @param   item Pointer to the buffer to fill from the queue
 * @param   delay_ms Time in milliseconds to wait for data in the queue before timing out
 */
void queue_peek(Queue *queue, void *buf, uint32_t delay_ms);

/**
 * @brief   Reset all data in the queue
 * @param   queue Pointer to queue handle
 */
void queue_reset(Queue *queue);

/**
 * @brief   Retrieve the total number of spaces in the queue
 * @param   queue Pointer to queue handle
 * @return  Total number of spaces available
 */
uint32_t queue_get_num_items(Queue *queue);

/**
 * @brief   Retrieve the space left in the queue
 * @param   queue Pointer to queue handle
 * @return  Remaining number of spaces available
 */
uint32_t queue_get_spaces_available(Queue *queue);

/** @} */

#endif
