#ifndef PAWS_LIB_COMMUNICATION_CONTROL_H
#define PAWS_LIB_COMMUNICATION_CONTROL_H
    #include "AsyncUDP.h"
    #include "WiFi.h"
    #include "Config.h"
    #include "DataStorage.h"
    #include "ArduinoLog.h"
    

    struct Packet {
        uint8_t deviceName;
    
    };

    /**
     * @brief starts communication, send data and process incomming data.
     * 
     */
    class CommunicationControl {
        public:
            CommunicationControl();
            void init_communication();
            void connectToClient();
            void sendData(const char* data);
            
            CommunicationControl(CommunicationControl const&) = delete;
            void operator=(CommunicationControl const&) = delete;
            
        private:

            AsyncUDP udp;
            void sendPacket(AsyncUDPPacket* packet);
            void onPacket(AsyncUDPPacket* recievedPacket);
            bool checkIfDataIsComplete(uint8_t* data);
            // void parsePacketToData(AsyncUDPPacket* packet);
            // AsyncUDPPacket parseDataToPacket(uint8_t* data);
    };

#endif // PAWS_LIB_COMMUNICATION_CONTROL_H

