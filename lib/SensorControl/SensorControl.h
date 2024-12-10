#ifndef PAWS_LIB_SENSOR_CONTROL_H
#define PAWS_LIB_SENSOR_CONTROL_H

#include <Adafruit_MPU6050.h>
#include "UUID.h"
#include "SensorData.h"
#include "Buffer.h"

class SensorControl
{
public:
    SensorControl();

    SensorData getReading();
    void getSensorUUIDAsCharArray(char *output);
    void init_sensors();
    void parseSensorDataToCharArray(const SensorData &data, char *output, size_t outputSize);
    void performReading();

    Buffer<SensorData> buffer;

private:
    UUID sensorUUID;
    Adafruit_MPU6050 sensor;

};

#endif // PAWS_LIB_SENSOR_CONTROL_H