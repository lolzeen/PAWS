#ifndef PAWS_LIB_SCREENCONTROLLER_H
#define PAWS_LIB_SCREENCONTROLLER_H

#include "U8g2lib.h"
#include "rotary.h"

struct StaticContent
{
    unsigned short uid;
    char background[1024];
};

class ScreenController
{
public:
    
    ScreenController(): _display(U8G2_R0, /* clock=*/18, /* data=*/22, /* CS=*/23, U8X8_PIN_NONE) {initScreen();};
    ScreenController(uint8_t clock, uint8_t data, uint8_t chipSelect) : _display(U8G2_R0, clock, data, chipSelect, U8X8_PIN_NONE) {initScreen();};
    ~ScreenController();

    void refresh();


private:
    int encoderPosition;
    bool buttonWasPressed;

    Rotary<ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN>* userInput = Rotary<ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN>::instance();
    U8G2_ST7920_128X64_F_SW_SPI _display;
    void initScreen();

};

#endif // PAWS_LIB_SCREENCONTROLLER_H