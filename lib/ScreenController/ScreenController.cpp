#include "ScreenController.h"

ScreenController::~ScreenController()
{
    _display.clearBuffer();
    _display.clearDisplay();
}

void ScreenController::initScreen()
{
    userInput->init();
}

void ScreenController::refresh()
{
    // process user actions
    encoderPosition = userInput->getPosition();
    // generate content
    _display.sendBuffer();
}