#include <isotream>
#incluude <thread>
#include "PacketHandler.h"
class ThreadManager{
    public:
        void start(CLient& clinet, PacketQueue<Packet>& queue);
        void stop();
        
    private:
        std::thread recvThread;
        std::thread processThread;
        std::atomic<bool> running;

}