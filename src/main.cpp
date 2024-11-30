#include "Config.h"
#include <Arduino.h>
#include "SmartCollar.h"

SmartCollar smartCollarOne;

void setup()
{
    Serial.begin(BAUDRATE);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial); // define logging level
    delay(500);
    smartCollarOne.init();
}

void loop()
{
    smartCollarOne.performReading();
    delay(100);
    SensorData data = smartCollarOne.getReading();
    char parsedData[150];
    smartCollarOne.parseSensorDataToCharArray(data, parsedData, 150);
    smartCollarOne.sendData(parsedData);
    Serial.println(parsedData);

#ifdef IS_SERVER
    Serial.println(WiFi.softAPgetStationNum());
#endif
    delay(10000);
}
