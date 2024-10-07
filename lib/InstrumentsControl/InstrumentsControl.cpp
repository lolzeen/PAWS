#include "InstrumentsControl.h"

InstrumentsControl::InstrumentsControl() {
    if (!instrument.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    instrument.setAccelerometerRange(MPU6050_RANGE_2_G);
    instrument.setGyroRange(MPU6050_RANGE_250_DEG);
    instrument.setHighPassFilter(MPU6050_HIGHPASS_1_25_HZ);
    instrument.setFilterBandwidth(MPU6050_BAND_10_HZ);
}

InstrumentData InstrumentsControl::getReading() {
    InstrumentData data;
    if (instrument.getEvent(&accelReading, &gyroReading, &temperatureReading)) {
        data.accelData = accelReading;
        data.gyroData = gyroReading;
        data.temperatureData = temperatureReading;
        return data;
    }
    else {
        Serial.println("Failed to retrive data from instrument.");
    }
}
