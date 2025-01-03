#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <arpa/inet.h>
#include <pthread.h>

#include <atomic>
#include <string>

/* Forward declaration */
class Server;

class ClientConnection {
 private:
  std::atomic<bool> m_isConnected;
  int m_clientPort;
  int m_clientSocket;
  struct sockaddr_in m_clientAddress;
  std::string m_clientName;

  Server *server;

 public:
  ClientConnection(Server *server);
  ~ClientConnection();

  bool acceptClient(int listeningSocket);

  void monitorThreadProcedure();
  void sendMessage(const std::string &message);

  std::string getClientName() const;
  void setClientName(const std::string &name);

  int getClientPort() const;
  void setClientPort(int port);

  int getSocketFd() const;
  std::string getClientAddress() const;

  bool isConnected();
};

#endif
