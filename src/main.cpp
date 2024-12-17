#include "Config.h"
#include <Arduino.h>
#include "UserInput.h"

UserInput<ENC_A_PIN, ENC_B_PIN, BTN_PIN>* r = UserInput<ENC_A_PIN, ENC_B_PIN, BTN_PIN>::getInstance();

void setup()
{
    Serial.begin(BAUDRATE);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial); // define logging level
    delay(2000);
    r->init();
    delay(1000);
}

void loop(){
    int pos = r->getPosition();
    Log.traceln(F("[Main] Pos: %s"), String(pos));
    delay(200);
}