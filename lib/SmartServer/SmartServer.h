#ifndef PAWS_LIB_SMARTSERVER_H
#define PAWS_LIB_SMARTSERVER_H

#include "CommunicationControl.h"
#include "UUID.h"
#include "Buffer.h"
#include "ScreenController.h"
#include "UserInput.h"
#include "ServerStatus.h"
#include "InputType.h"

class SmartServer : public CommunicationControl, public ScreenController
{
public:
    SmartServer() : CommunicationControl(), ScreenController()
    {
        Serial.begin(BAUDRATE);
        Log.begin(LOG_LEVEL_VERBOSE, &Serial); // define logging level
    }
    ~SmartServer() {};

    void getUUIDAsCharArray(char *output);
    void bootUp();
    void updateSeverStatus();

    void enableLogging() { serverStatus.enableLogging = true; };
    void disableLogging() { serverStatus.enableLogging = false; };
    bool isLoggingEnabled() { return serverStatus.enableLogging; };

    void enableLiveData() { serverStatus.enableLivedata = true; };
    void disableLiveData() { serverStatus.enableLivedata = false; };
    bool isLiveDataEnabled() { return serverStatus.enableLivedata; };

    void setAction(InputType inputType);

private:
    UserInput<ENC_A_PIN, ENC_B_PIN, BTN_PIN>* userInput = nullptr;
    Buffer<String> incomingDatabuffer;
    UUID uuid;
    ServerStatus serverStatus;
};

#endif // PAWS_LIB_SMARTSERVER_H