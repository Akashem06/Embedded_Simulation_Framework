#ifndef APP_CALLBACK_H
#define APP_CALLBACK_H

#include <string>

#include "client.h"

void applicationMessageCallback(Client *client, std::string &message);
void applicationConnectCallback(Client *client);
#endif
