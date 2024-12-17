#include "Config.h"
#include <Arduino.h>
#include "SmartCollar.h"

#ifdef IS_CLIENT
SmartCollar smartCollarOne;
#endif

bool enable_live_logging = true;
bool acquire_data = true;
bool send_data = true;
bool was_button_pressed = false;
bool encoder_to_the_right = false;
bool encoder_to_the_left = false;

void setup()
{
    Serial.begin(BAUDRATE);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial); // define logging level
    delay(500);
    smartCollarOne.init();
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

    if (enable_live_logging)
    {
        // display data contained in the buffer
    }

    if (was_button_pressed)
    {
        // perform next action (define a state machine for the menu screens)
        // the same function should be used for both button and encoder
    }

    if (encoder_to_the_right)
    {
        // perform next action (define a state machine for the menu screens)
    }

    if (encoder_to_the_left)
    {
        // perform next action (define a state machine for the menu screens)
    }
    Serial.println(WiFi.softAPgetStationNum());
#endif
    delay(100);
}
