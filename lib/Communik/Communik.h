#ifndef PAWS_LIB_COMMUNIK_H
#define PAWS_LIB_COMMUNIK_H
    #include "AsyncUDP.h"

    struct Packet {
        uint8_t deviceName;
    
    };

    /**
     * @brief starts communication, send data and process incomming data.
     * 
     */
    class Communik {
        public:
            Communik();
            void init();
            bool send(uint8_t* data);
            

        private:
            AsyncUDP udp;
            
            void sendPacket(AsyncUDPPacket* packet);
            void onPacket(AsyncUDPPacket* recievedPacket);
            bool checkIfDataIsComplete(uint8_t* data);
            void parsePacketToData(AsyncUDPPacket* packet);
            AsyncUDPPacket parseDataToPacket(uint8_t* data);
    };
#endif // PAWS_LIB_COMMUNIK_H
