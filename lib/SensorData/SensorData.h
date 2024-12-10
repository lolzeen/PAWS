#ifndef PAWS_INCLUDE_SANSORDATA_H
#define PAWS_INCLUDE_SANSORDATA_H

#include "Adafruit_Sensor.h"
#include "sdkconfig.h"

class SensorData
{
public:
    sensors_event_t accelData;
    sensors_event_t temperatureData;
    sensors_event_t gyroData;

#ifdef ENABLE_GYRO
    
    static const size_t size = sizeof(sensors_event_t) * 3;
#else
    static const size_t size = sizeof(sensors_event_t) * 2;
#endif

};

#endif // PAWS_INCLUDE_SANSORDATA_H