#include "Config.h"
#include "SensorControl.h"
#include "ArduinoLog.h"


SensorControl::SensorControl() {
    
}

void SensorControl::init_sensors() {
    Log.noticeln(F("Initializing SensorControl...\n"));
    Wire.begin(MPU_SDA_PIN, MPU_SCL_PIN, I2C_FREQ);
    if (!sensor.begin()) {
        Log.errorln(F("Failed to find MPU6050 chip\n"));
        delay(1000);
        ESP.restart();
        return;
    }
    Log.noticeln(F("MPU6050 chip found. Configuring sensor settings...\n"));
    sensor.setAccelerometerRange(MPU6050_RANGE_2_G);
    sensor.setGyroRange(MPU6050_RANGE_250_DEG);
    sensor.setHighPassFilter(MPU6050_HIGHPASS_1_25_HZ);
    sensor.setFilterBandwidth(MPU6050_BAND_10_HZ);
    sensorUUID.generate();
    Log.noticeln(F("Sensor UUID generated: %s\n"), sensorUUID.toCharArray());
}

SensorData SensorControl::getReading() {
    Log.traceln(F("Attempting to get a reading from the buffer...%d\n"), bufferTail);
    if (bufferHead == bufferTail and !bufferIsFull) {
        Log.errorln(F("Failed to retrieve data from Sensor. Buffer is empty!\n"));
        return SensorData();
    }
    else {
        Log.noticeln(F("Buffer not empty, returning reading from buffer position %d\n"), bufferTail);
        uint8_t tempIndex = bufferTail;
        advanceBufferTail();
        return circularBuffer[tempIndex];
    }
}

void SensorControl::getSensorUUIDAsCharArray(char* output) {
    sprintf(output, "%s", sensorUUID.toCharArray());
    Log.traceln(F("Retrieving Sensor UUID: %s\n"), output);
}

void SensorControl::parseSensorDataToCharArray(const SensorData& data, char* output, size_t outputSize) {
    snprintf(output, outputSize,
            "Accel: X: %.2f m/s², Y: %.2f m/s², Z: %.2f m/s²\n"
            "Gyro: X: %.2f rad/s, Y: %.2f rad/s, Z: %.2f rad/s\n"
            "Temperature: %.2f °C",
            data.accelData.acceleration.x,
            data.accelData.acceleration.y,
            data.accelData.acceleration.z,
            data.gyroData.gyro.x, data.gyroData.gyro.y, data.gyroData.gyro.z,
            data.temperatureData.temperature);
    Log.traceln("Parsed data to char array.");
}

void SensorControl::performReading() {
    SensorData data;
    char parsedData[128];
    Log.traceln(F("Performing reading from MPU6050 sensor...\n"));
    sensor.getEvent(&data.accelData, &data.gyroData, &data.temperatureData);
    parseSensorDataToCharArray(data, parsedData, sizeof(parsedData));
    Log.traceln(F("Captured Sensor Data: %s\n"), parsedData);
    Log.traceln(F("Saving data at buffer position %d\n"), bufferHead);
    circularBuffer[bufferHead] = data;
    advanceBufferHead();
}

void SensorControl::advanceBufferHead() {
    Log.traceln(F("Advancing buffer head from position %d...\n"), bufferHead);
    bufferHead = (bufferHead + 1) % BUFFER_SIZE;
    if (bufferHead == bufferTail && bufferHead == BUFFER_SIZE) {
        Log.warningln(F("Buffer is full. Buffer head at %d\n"), bufferHead);
        bufferIsFull = true;
    }
    else {
        Log.noticeln(F("Buffer head advanced to %d. Buffer is not full.\n"), bufferHead);
        bufferIsFull = false;
    }
}
void SensorControl::advanceBufferTail() {
    Log.traceln(F("Advancing buffer tail from position %d...\n"), bufferTail);
    bufferTail = (bufferTail + 1) % BUFFER_SIZE;
    Log.noticeln(F("Buffer tail advanced to %d\n"), bufferTail);
}


