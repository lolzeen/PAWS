#include "CommunicationControl.h"
#include "UdpMessage.h"

CommunicationControl::CommunicationControl() {}

void CommunicationControl::init_communication() {
    Log.traceln(F("CommunicationControl initialization started."));
    #ifdef IS_SERVER
        WiFi.mode(WIFI_AP);
        WiFi.softAP(WIFI_SSID, WIFI_PSK);
        Log.noticeln(F("Access point started with IP address: %s"), WiFi.softAPIP().toString().c_str(), F("\n"));
    #endif
    #ifdef IS_CLIENT
        Log.traceln(F("Client attepting to stablish connection"));
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PSK);
        WiFi.setAutoReconnect(true);
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Log.errorln(F("Failed to connect to server."));
            delay(500);
        }
        Log.noticeln(F("Coonected to: %s"), WiFi.localIP().toString().c_str(), F("\n"));
        udp.connect(IPAddress(192, 0, 0, 2), 5555);
        udp.print("Hello Server!");
        Communication::UdpMessage message(,
        "server",
        "clientOne",
        "Hello Serever");
    #endif
}


void CommunicationControl::connectToClient() {
    #ifdef IS_SERVER
        // get client ip
        // WiFi.broadcastIP()
        IPv6Address clientIp;
        uint16_t clientPort;
        udp.connect(clientIp, clientPort);
    #endif
}

void CommunicationControl::sendData(const Communication::UdpMessage message) {
    udp.print(message.toString());
}

void CommunicationControl::onPacket(AsyncUDPPacket* recievedPacket) {
    Serial.printf("Received packet from %s:%d\n", recievedPacket->remoteIP().toString().c_str(), recievedPacket->remotePort());
    // if data is complete 
        // parse it
        // store it
}

bool CommunicationControl::checkIfDataIsComplete(uint8_t* data) {
    return false;
}

/**
 * @brief 
 * 
 * @param packet 
 */
// void CommunicationControl::parsePacketToData(AsyncUDPPacket* packet) {}
