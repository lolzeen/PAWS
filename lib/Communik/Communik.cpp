#include "Communik.h"
#include "WiFi.h"
#include "Config.h"
#include "DataStorage.h"
#include "ArduinoLog.h"

Communik::Communik() {
    // constructor
}

void Communik::init() {
    #ifdef IS_SERVER
        Log.trace(F("Communik initialization started.\n"));
        WiFi.softAP(SSID, PSK);
        Log.notice(F("Access point started with IP address: "), WiFi.softAPIP());
    #endif
    #ifdef IS_CLIENT
        Log.traceln(F("Communik initialization started."));
        int wifiStatus = WL_DISCONNECTED;
        uint8_t num_retires = 0;
        while (wifiStatus != WL_CONNECTED) {
            if (num_retires > 1) {
                Log.warning(F("Attempting to connect to server, retries: "), num_retires);
            }
            wifiStatus = WiFi.begin(SSID, PSK);
            delay(500);
            num_retires = num_retires + 1;
        }
        Log.notice(F("Coonected to: "), WiFi.gatewayIP());
    #endif
}

void Communik::sendPacket(AsyncUDPPacket* packet) {

}

void Communik::onPacket(AsyncUDPPacket* recievedPacket) {
    Serial.printf("Received packet from %s:%d\n", recievedPacket->remoteIP().toString().c_str(), recievedPacket->remotePort());
    // if data is complete 
        // parse it
        // store it
}

bool Communik::checkIfDataIsComplete(uint8_t* data) {
    return false;
}

/**
 * @brief 
 * 
 * @param packet 
 */
void Communik::parsePacketToData(AsyncUDPPacket* packet) {
}

/**
 * @brief create packet
 * 
 * @param data 
 */
AsyncUDPPacket Communik::parseDataToPacket(uint8_t* data) {
}