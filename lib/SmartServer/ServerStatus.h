#include "Config.h"
#ifdef IS_SERVER
#ifndef PAWS_LIB_SMARTSERVER_SERVERSTATUS_H
#define PAWS_LIB_SMARTSERVER_SERVERSTATUS_H

struct ServerStatus {
    bool enableLogging = true;
    bool enableLivedata = true;
    bool wasButtonPressed = false;
    bool encoderToTheRight = false;
    bool encoderToTheLeft = false;
};

#endif // PAWS_LIB_SMARTSERVER_SERVERSTATUS_H
#endif // IS_SERVER