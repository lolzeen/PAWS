#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "SensorControl.h"
#include "Config.h"


SensorControl sensorControl;

void setup() {
  Wire.begin(MPU_SDA_PIN, MPU_SCL_PIN, I2C_FREQ);
  Serial.begin(BAUDRATE);
  // define logging level
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  
  sensorControl.begin();
}

void loop() {
    

  // Retrieve and print the sensor data
  sensorControl.performReading();
  delay(100);
  SensorData data = sensorControl.getReading();
  char parsedData[150];
  sensorControl.parseSensorDataToCharArray(data, parsedData, 50);
  Serial.println(parsedData);

  // Serial.print("Accel X: "); Serial.print(data.accelData.acceleration.x);
  // Serial.print(" | Accel Y: "); Serial.print(data.accelData.acceleration.y);
  // Serial.print(" | Accel Z: "); Serial.print(data.accelData.acceleration.z);
  // Serial.print(" | Gyro X: "); Serial.print(data.gyroData.gyro.x);
  // Serial.print(" | Gyro Y: "); Serial.print(data.gyroData.gyro.y);
  // Serial.print(" | Gyro Z: "); Serial.print(data.gyroData.gyro.z);
  // Serial.print(" | Temp: "); Serial.print(data.temperatureData.temperature);
  // Serial.println(" °C");

  delay(1000); // Delay for a second before the next reading
}
