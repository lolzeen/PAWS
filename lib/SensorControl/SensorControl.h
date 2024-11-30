#ifndef PAWS_LIB_SENSOR_CONTROL_H
#define PAWS_LIB_SENSOR_CONTROL_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "UUID.h"

struct SensorData {
    sensors_event_t accelData, gyroData, temperatureData;
};

class SensorControl {
    public:
        SensorControl();
        void init_sensors();
        SensorData getReading();
        void getSensorUUIDAsCharArray(char* output);
        void parseSensorDataToCharArray(const SensorData& data, char* output, size_t outputSize);
        void performReading();
        uint8_t getBufferHead() const { return bufferHead; }
        uint8_t getBufferTail() const { return bufferTail; }
        uint8_t getBufferSize() const { return BUFFER_SIZE; }
        bool isBufferFull() const { return bufferIsFull; }
    private:
        UUID sensorUUID;
        static const uint8_t BUFFER_SIZE = 42;
        SensorData circularBuffer[BUFFER_SIZE];
        uint8_t bufferHead = 0;
        uint8_t bufferTail = 0;
        bool bufferIsFull = false;
        Adafruit_MPU6050 sensor;

        void advanceBufferHead();
        void advanceBufferTail();
};


#endif // PAWS_LIB_SENSOR_CONTROL_H