#pragma once
#include "ArduinoLog.h"

#define IS_SERVER
// #define IS_CLIENT

// #define HAS_RTC
// #define HAS_BATTERY
#define ENABLE_GYRO

#define BAUDRATE 115200

#define WIFI_SSID "PAWS-SERVER"
#define WIFI_PSK "itjx0475"

#ifdef IS_SERVER
    #define ENC_A_PIN 25
    #define ENC_B_PIN 33
    #define BTN_PIN 35
    #define BUZ_PIN 32
    #define LCD_RW_PIN 23 
    #define LCD_RS_PIN 22
    #define LCD_EN_PIN 18
    #define SD_MOSI
    #define SD_CS
    #define SD_SCK
    #define SD_MISO
    #define SD_DETECT
    #define UDP_PORT 6665
#endif

#ifdef IS_CLIENT
    // #define ENABLE_GYRO
    #define MPU_SCL_PIN 22
    #define MPU_SDA_PIN 23
    #define MPU_INT_PIN 34
    #define I2C_FREQ 400000U
    #define UDP_PORT 6666

    #ifdef HAS_BATTERY
        #define BATTERY_IN
    #endif
#endif

#ifdef HAS_RTC
    #define RTC_SS
    #define RTC_MOSI
    #define RTC_MISO
    #define RTC_CLK
    #define RTC_SQW
#endif