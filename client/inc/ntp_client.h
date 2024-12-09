#ifndef NTP_CLIENT_H
#define NTP_CLIENT_H

#include <string>
#include <atomic>
#include <chrono>
#include <ctime>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include "network_time_protocol.h"

#define NTP_SYNC_PERIOD_S       60

class NTPClient {
    private:
        static constexpr int NTP_PORT = 123;
        int m_NTPSocket;
        std::string m_serverAddress;
        NTPPacket m_serverResponse;
        pthread_t m_NTPClientThreadId;
        std::atomic<bool> m_isSynchronizing;
        
    public:
        NTPClient();
        void NTPClientProcedure();
        void startSynchronization(const std::string &serverAddress);
};

#endif
