#ifndef PAWS_LIB_SMARTSERVER_H
#define PAWS_LIB_SMARTSERVER_H

#include "CommunicationControl.h"
#include "UUID.h"
#include "Buffer.h"

class SmartServer : public CommunicationControl
{
public:
    SmartServer(/* args */);
    ~SmartServer();

    void getUUIDAsCharArray(char* output);

private:
    Buffer<String> incomingDatabuffer;
    UUID uuid;
};

#endif // PAWS_LIB_SMARTSERVER_H