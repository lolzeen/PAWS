#include "CommunicationControl.h"

CommunicationControl::CommunicationControl() {}

void CommunicationControl::initCommunication()
{
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
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Log.errorln(F("Failed to connect to server."));
        delay(500);
    }
    Log.noticeln(F("Coonected to: %s"), WiFi.localIP().toString().c_str(), F("\n"));
    _udp.connect(IPAddress(192, 0, 0, 2), 5555);
    _udp.print("Hello Server!");
#endif
}

void CommunicationControl::connectToClient()
{
#ifdef IS_SERVER
    // get client ip
    // WiFi.broadcastIP()
    IPv6Address clientIp;
    uint16_t clientPort = 5050;
    _udp.connect(clientIp, clientPort);
#endif
}

void CommunicationControl::sendData(const char *data)
{
    _udp.print(data);
}

void CommunicationControl::sendData(Communication::UdpMessage<String> message)
{
    _udp.print(message.toString());
}

void CommunicationControl::sendDataXTimes(Communication::UdpMessage<String> message, uint8_t times)
{
    for (size_t i = 0; i < times; i++)
    {
        sendData(message);
    }
}

bool CommunicationControl::checkIfDataIsComplete(String data)
{
    return false;
}

bool CommunicationControl::checkIfDataIsNew(String data)
{
    // check latest timesstamp vs current
    return false;
}

void CommunicationControl::convertAsyncUDPPacketToUDPMessage(AsyncUDPPacket packet, Communication::UdpMessage<String> *output)
{
}

void CommunicationControl::receiveData(String *output)
{
    _udp.onPacket([this](AsyncUDPPacket packet) {
        Communication::UdpMessage<String> udpMessage;
        switch (udpMessage.getType())
        {
        case Communication::UdpMessage<String>::MessageType::DATA:
            if (checkIfDataIsComplete(udpMessage.getPayload()) and checkIfDataIsNew(udpMessage.getPayload())) {
                // assign data to buffer
            }
            break;

        case Communication::UdpMessage<String>::MessageType::CMD:
            break;

        case Communication::UdpMessage<String>::MessageType::STAT:
            break;

        case Communication::UdpMessage<String>::MessageType::ERROR:
            break;

        default:
            break;
        }
    });
}

/**
 * @brief
 *
 * @param packet
 */
// void CommunicationControl::parsePacketToData(AsyncUDPPacket* packet) {}
