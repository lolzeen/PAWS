#ifdef IS_CLIENT
#ifndef PAWS_LIB_SMART_COLLAR_H
#define PAWS_LIB_SMART_COLLAR_H
#include "SensorControl.h"
#include "CommunicationControl.h"

class SmartCollar : public SensorControl, public CommunicationControl
{
public:
    SmartCollar();
    ~SmartCollar();

    void init();
    void loop();

private:
};

#endif // PAWS_LIB_SMART_COLLAR_H
#endif // IS_CLIENT