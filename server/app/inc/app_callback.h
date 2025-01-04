#pragma once

/************************************************************************************************
 * @file   app_callback.h
 *
 * @brief  Header file defining the Server Application Callback functions
 *
 * @date   2025-01-04
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <string>

/* Inter-component Headers */
#include "client_connection.h"
#include "server.h"

/* Intra-component Headers */

/**
 * @defgroup ServerAppCallback
 * @brief    Application Callback functions for the Server
 * @{
 */

/**
 * @brief   Handle receiving new client messages
 * @details This shall handle all CommandCodes received
 *          This shall branch out to the GpioManager, I2CManager, SPIManager or InterruptManager
 *          based on the CommandCode
 */
void applicationMessageCallback(Server *srv, ClientConnection *src, std::string &message);

/**
 * @brief   Handle connecting to a new client
 * @details This shall notify the user about a new client connection
 *          This shall refresh the application interface with the new client data
 */
void applicationConnectCallback(Server *srv, ClientConnection *src);

/** @} */
