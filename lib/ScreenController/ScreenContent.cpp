#include "ScreenContent.h"

void ScreenContents::ScreenContent::updateContent(ScreenVariable::ScreenActions action) {
    switch (action)
    {
    case ScreenVariable::ScreenActions::BUTTON_PRESSED:
        getResultOfButtonAction();
        break;
    
    default:
        getResultOfEncoderAction(ScreenVariable::ScreenActions::ENCODER_RIGHT);
        break;
    }
}

void ScreenContents::ScreenContent::getResultOfButtonAction() {
    switch (currentFocus)
    {
        case ScreenVariable::PossibleFocus::RETURN_MAIN_MENU:
        currentContent = ScreenVariable::PossibleContents::MAIN_MENU;
        break;

        case ScreenVariable::PossibleFocus::CONNECT:
        currentContent = ScreenVariable::PossibleContents::CONNECT;
        break;

        case ScreenVariable::PossibleFocus::BATTERY_LEVEL:
        currentContent = ScreenVariable::PossibleContents::BATTERY_LEVEL;
        break;

        case ScreenVariable::PossibleFocus::LIVE_DATA:
        currentContent = ScreenVariable::PossibleContents::LIVE_DATA;
        break;

        case ScreenVariable::PossibleFocus::SETTINGS:
        currentContent = ScreenVariable::PossibleContents::SETTINGS;
        break;
    }
}

void ScreenContents::ScreenContent::getResultOfEncoderAction(ScreenVariable::ScreenActions action) {
    
}