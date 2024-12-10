#ifndef PAWS_LIB_COMMUNICATION_CONTROL_H
#define PAWS_LIB_COMMUNICATION_CONTROL_H
    #include "AsyncUDP.h"
    #include "WiFi.h"
    #include "Config.h"
    #include "ArduinoLog.h"
    #include "UdpMessage.h"
    #include "SensorData.h"

    /**
     * @brief starts communication, send data and process incomming data.
     * 
     */
    class CommunicationControl {
        public:
            CommunicationControl();
            void init_communication();
            void connectToClient();
            void convertAsyncUDPPacketToUDPMessage(AsyncUDPPacket packet, Communication::UdpMessage<String>* output);
            void receiveData(String* output); 
            void sendData(Communication::UdpMessage<String> message);
            void sendData(Communication::UdpMessage<char*> message);
            void sendData(Communication::UdpMessage<SensorData*> buffer);
            void sendDataXTimes(Communication::UdpMessage<String> message, uint8_t times);
            void sendDataXTimes(Communication::UdpMessage<SensorData*> buffer, uint8_t times); 
        private:
            AsyncUDP _udp;

            void sendData(const char* data);
            bool checkIfDataIsComplete(String data);
            bool checkIfDataIsNew(String data);
    };

#endif // PAWS_LIB_COMMUNICATION_CONTROL_H

