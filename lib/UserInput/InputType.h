#include "Config.h"
#ifdef IS_SERVER
#ifndef PAWS_LIB_USERINPUT_INPUTTYPE_H
#define PAWS_LIB_USERINPUT_INPUTTYPE_H

enum class InputType : uint8_t
{
    BUTTON_PRESS,
    ENCODER_RIGHT,
    ENCODER_LEFT
};

#endif // PAWS_LIB_USERINPUT_INPUTTYPE_H
#endif // IS_SERVER