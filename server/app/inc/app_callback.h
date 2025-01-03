#ifndef APP_CALLBACK_H
#define APP_CALLBACK_H

#include <string>

#include "client_connection.h"
#include "server.h"

void applicationMessageCallback(Server *srv, ClientConnection *src, std::string &message);
void applicationConnectCallback(Server *srv, ClientConnection *src);
#endif
