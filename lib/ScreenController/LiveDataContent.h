#ifndef PAWS_LIB_LIVEDATACONTENT_H
#define PAWS_LIB_LIVEDATACONTENT_H

#include "U8g2lib.h"



class LiveDataContent
{
public:
    LiveDataContent(/* args */) {};
    ~LiveDataContent() {};

    void setDisplay(U8G2_ST7920_128X64_F_SW_SPI *display);
    void updateBoxes(uint8_t accel, uint8_t frameIndex);
    void updateBoxes(uint8_t* accel, size_t size);

private:
    U8G2_ST7920_128X64_F_SW_SPI *_display = nullptr;
    u8g2_uint_t screenHeight;
    u8g2_uint_t screenWidth;
    u8g2_uint_t frameOriginX;
    u8g2_uint_t frameOriginY;
    u8g2_uint_t frameHeight;
    u8g2_uint_t frameWidth;
    u8g2_uint_t indexOriginX;
    u8g2_uint_t indexOriginY;
    u8g2_uint_t boxHeight;
    u8g2_uint_t boxWidth;
    u8g2_uint_t boxOriginX;
    u8g2_uint_t boxOriginY;
    uint8_t numBoxes;
    uint8_t maxNumBoxes;
    uint8_t* accelValues = nullptr;
    uint8_t accelValue;

    void calcMaxNumBoxes();
    uint8_t convertAccelToBoxes(uint8_t accel);
    void drawFrames();
    void drawBoxes(uint8_t numBoxes, uint8_t frameIndex);
    void writeMessage();
};

#endif // PAWS_LIB_LIVEDATACONTENT_H