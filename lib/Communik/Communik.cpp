#include "Communik.h"
#include "WiFi.h"
#include "Config.h"
#include "DataStorage.h"

Communik::Communik() {
    // constructor
}

void Communik::init() {
    Serial.println("Communik initialization started.");
    WiFi.softAP(SSID, PSK);
    Serial.print("Access point started with IP address: ");
    Serial.println(WiFi.softAPIP());

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