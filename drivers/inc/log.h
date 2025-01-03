#pragma once

/************************************************************************************************
 * @file   log.h
 *
 * @brief  Header file for the logging library used to debug all modules
 *
 * @date   2024-11-02
 * @author Midnight Sun Team #24 - MSXVI
 ************************************************************************************************/

/* Standard library Headers */
#include <stdio.h>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup  Logger
 * @brief     Logging library
 * @{
 */

typedef enum {
  LOG_LEVEL_DEBUG = 0, /**< Debug level */
  LOG_LEVEL_WARN,      /**< Warning level */
  LOG_LEVEL_CRITICAL,  /**< Critical level */
  NUM_LOG_LEVELS,      /**< Number of Log levels */
} LogLevel;

#define LOG_DEBUG(fmt, ...) LOG(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) LOG(LOG_LEVEL_CRITICAL, fmt, ##__VA_ARGS__)

#define LOG(level, fmt, ...) printf("[%u] %s:%u: " fmt, (level), __FILE__, __LINE__, ##__VA_ARGS__)

/** @} */