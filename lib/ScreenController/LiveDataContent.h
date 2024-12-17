#include "Config.h"
#ifdef IS_SERVER
#ifndef PAWS_LIB_LIVEDATACONTENT_H
#define PAWS_LIB_LIVEDATACONTENT_H

#include "U8g2lib.h"

class LiveDataContent
{
public:
    LiveDataContent() {};
    ~LiveDataContent() {};

    void setDisplayVariables(U8G2_ST7920_128X64_F_SW_SPI *display, u8g2_uint_t* _screenWidth, u8g2_uint_t* _screenHeight);
    void updateBoxes(uint8_t accel, uint8_t frameIndex);
    void updateBoxes(uint8_t *accel, size_t size);

private:
    uint8_t *_accelValues = nullptr;
    u8g2_uint_t _boxHeight;
    u8g2_uint_t _boxWidth;
    u8g2_uint_t _boxOriginX;
    u8g2_uint_t _boxOriginY;
    U8G2_ST7920_128X64_F_SW_SPI *_display = nullptr;
    u8g2_uint_t _frameOriginX;
    u8g2_uint_t _frameOriginY;
    u8g2_uint_t _frameHeight;
    u8g2_uint_t _frameWidth;
    u8g2_uint_t _indexOriginX;
    u8g2_uint_t _indexOriginY;
    uint8_t _numBoxes;
    uint8_t _maxNumBoxes;
    u8g2_uint_t* _screenHeight;
    u8g2_uint_t* _screenWidth;

    void calcMaxNumBoxes();
    uint8_t convertAccelToBoxes(uint8_t accel);
    void drawFrames();
    void drawBoxes(uint8_t _numBoxes, uint8_t frameIndex);
    void writeMessage();
};

#endif // PAWS_LIB_LIVEDATACONTENT_H
#endif // IS_SERVER