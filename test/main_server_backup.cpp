#include "Config.h"
#include <Arduino.h>
#ifdef IS_CLIENT
#include "SmartCollar.h"
#elif defined IS_SERVER
#include "SmartServer.h"
#endif

#ifdef IS_CLIENT
// #undef IS_CLIENT
SmartCollar smartCollarOne;
// #define IS_SERVER
#endif
#ifdef IS_SERVER
SmartServer smartServer;
#endif

void setup()
{
#ifdef IS_CLIENT
    smartCollarOne.init();
#elif defined IS_SERVER
    smartServer.bootUp();
    delay(500);
#endif
}

void loop()
{
    Log.traceln("void loop");
#ifdef IS_CLIENT

    // collect data
    if (enable_live_logging and acquire_data)
    {
        smartCollarOne.performReading();
    }

    // process and send data
    if (enable_live_logging and send_data)
    {
        SensorData data = smartCollarOne.getReading();
        char parsedData[150];
        smartCollarOne.parseSensorDataToCharArray(data, parsedData, 150);
        Communication::UdpMessage<String> udpMessage;
        udpMessage.setPayload(parsedData);
        udpMessage.setTimestamp(millis());
        udpMessage.setType(Communication::UdpMessage<String>::MessageType::DATA);
        smartCollarOne.sendDataXTimes(udpMessage, 5);
    }
    delay(100);
#elif defined IS_SERVER
    Serial.println(WiFi.softAPgetStationNum());
    // update display
#endif
    delay(1000);
}
