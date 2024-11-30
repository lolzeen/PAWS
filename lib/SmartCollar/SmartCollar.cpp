#include "SmartCollar.h"

SmartCollar::SmartCollar() {
    
}

SmartCollar::~SmartCollar()
{
}

void SmartCollar::init() {
    init_communication();
    init_sensors();

}