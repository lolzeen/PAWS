#ifndef PAWS_LIB_SCREENVARIABLES_H
#define PAWS_LIB_SCREENVARIABLES_H
#include <Arduino.h>

namespace ScreenVariable
{
    enum class PossibleContents: uint8_t
    {
        INIT,
        MAIN_MENU,
        CONNECT,
        LIVE_DATA,
        SETTINGS,
        BATTERY_LEVEL
    };

    enum class PossibleFocus: uint8_t
    {
        CONNECT,
        LIVE_DATA,
        SETTINGS,
        RETURN_MAIN_MENU,
        RESTART,
        BATTERY_LEVEL
    };

    enum class ScreenActions: uint8_t
    {
        BUTTON_PRESSED,
        ENCODER_RIGHT,
        ENCODER_LEFT
    };
}

#endif // PAWS_LIB_SCREENVARIABLES_H