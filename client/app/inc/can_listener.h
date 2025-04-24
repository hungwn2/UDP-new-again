#include <atomic>
#include <cstring>
#include <atomic>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

/* Inter-component Headers */
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/bcm.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <nlohmann/json.hpp>


class CanListener{
 private:
    const std::string CAN_INTERFACE_NAME="vcan0";
    const std::string CAN_JSON_NAME="CANListener";
    
    static cosnt constexpr unsigned int UPDATE_CAN_JSON_PERIOD_MS=1000U;

    pthread_mutex_t m_mutex;
    pthread_t m_listenCanBusId;
    pthread_t m_updateJSONId;
    int m_rawCanSocket;
    std::atomic <bool> m_isListening;

    void canMessageHandler(uint32_t id, const uint8_t *data);
    public:
    CanListener();
    ~CanListener();
    void listenCanBus();
    void listenCanBusProcedure();
    void updateJSONProcedure();
};