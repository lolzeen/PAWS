#include <Arduino.h>
#include "Config.h"
#include "ScreenController.h"
#include "UserInput.h"

ScreenController screenController;
UserInput* userInput = UserInput::getInstance();

void setup()
{
    // Sensor control --- Wire.begin(MPU_SDA_PIN, MPU_SCL_PIN, I2C_FREQ);
    Serial.begin(BAUDRATE);
    // define logging level
    // Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    // Sensor control --- sensorControl.begin();
    userInput->init();
    delay(1000);
}

void loop()
{
    screenController.refresh();
    int pos = userInput->getPosition();
    Log.traceln(F("[Main] Pos: %s"), String(pos));
    delay(200);
}