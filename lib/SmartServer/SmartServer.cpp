#include "SmartServer.h"

void SmartServer::bootUp() {
    initCommunication();
    initScreen();
    uuid.generate();
    Log.noticeln(F("Server UUID generated: %s\n"), uuid.toCharArray());
    userInput = UserInput<ENC_A_PIN, ENC_B_PIN, BTN_PIN>::getInstance();
    userInput->init();
}

void SmartServer::getUUIDAsCharArray(char* output) {
    sprintf(output, "%s", uuid.toCharArray());
    Log.traceln(F("Retrieving Server UUID: %s\n"), output);
}

void SmartServer::setAction(InputType inputType) {
    switch (inputType)
    {
    case InputType::BUTTON_PRESS:
        serverStatus.wasButtonPressed = true;
        break;
    case InputType::ENCODER_LEFT:
        serverStatus.encoderToTheLeft = true;
        break;
    case InputType::ENCODER_RIGHT:
        serverStatus.encoderToTheRight = true;
        break;
    default:
        Log.errorln(F("SetActionError: Invalid input type."));
        break;
    }
}

void SmartServer::updateSeverStatus()
{
    if (userInput->hasEncoderChanged())
    {
    if (serverStatus.encoderToTheLeft)
    {
        setContentBasedOnAction(InputType::ENCODER_LEFT);
    }

    if (serverStatus.encoderToTheRight)
    {
        setContentBasedOnAction(InputType::ENCODER_RIGHT);
    }
    }
    if (userInput->isButtonPressed())
    {
        setContentBasedOnAction(InputType::BUTTON_PRESS);
        userInput->updateButtonState();
    }

    if (serverStatus.wasButtonPressed)
    {
    }

    if (serverStatus.enableLogging)
    {
        // display data contained in the buffer
    }

    if (serverStatus.enableLivedata)
    {
        // perform next action (define a state machine for the menu screens)
        // the same function should be used for both button and encoder
    }
}
