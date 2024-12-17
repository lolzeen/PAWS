#include "Config.h"
#ifdef IS_CLIENT
#include "SmartCollar.h"

SmartCollar::SmartCollar() {
    
}

SmartCollar::~SmartCollar()
{
}

void SmartCollar::init() {
    initCommunication();
    initSensors();
    
}
#endif // IS_CLIENT