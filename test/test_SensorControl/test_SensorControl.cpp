#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "SensorControl.h"
#include "Config.h"


// SensorControl sensorControl;

void setup() {
    Serial.begin(BAUDRATE);
    // define logging level
    // Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    // Perform a sensor reading
    // sensorControl.performReading();
}

void loop() {
    

    // Retrieve and print the sensor data
    // SensorData data = sensorControl.getReading();
    // char* parsedData;
    // sensorControl.parseSensorDataToCharArray(data, parsedData, 50);
    // Serial.println(parsedData);

    // Serial.print("Accel X: "); Serial.print(data.accelData.acceleration.x);
    // Serial.print(" | Accel Y: "); Serial.print(data.accelData.acceleration.y);
    // Serial.print(" | Accel Z: "); Serial.print(data.accelData.acceleration.z);
    // Serial.print(" | Gyro X: "); Serial.print(data.gyroData.gyro.x);
    // Serial.print(" | Gyro Y: "); Serial.print(data.gyroData.gyro.y);
    // Serial.print(" | Gyro Z: "); Serial.print(data.gyroData.gyro.z);
    // Serial.print(" | Temp: "); Serial.print(data.temperatureData.temperature);
    Serial.println(" °C");

    delay(1000); // Delay for a second before the next reading
}
