#ifndef PAWS_LIB_INSTRUMENTS_CONTROL_H
#define PAWS_LIB_INSTRUMENTS_CONTROL_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

struct InstrumentData {
    sensors_event_t accelData, gyroData, temperatureData;
};

class InstrumentsControl {
    public:
        InstrumentsControl();
        InstrumentData getReading();

    private:
        sensors_event_t accelReading, gyroReading, temperatureReading;
        uint8_t buffer[42];
        Adafruit_MPU6050 instrument;
};


#endif // PAWS_LIB_INSTRUMENTS_CONTROL_H
