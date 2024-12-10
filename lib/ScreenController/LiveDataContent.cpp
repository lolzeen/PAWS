#include "LiveDataContent.h"

void LiveDataContent::setDisplay(U8G2_ST7920_128X64_F_SW_SPI *display)
{
    _display = display;
    _display->setFont(u8g2_font_5x7_tf);
    _display->clearDisplay();
    _display->clearBuffer();
    screenHeight = _display->getDisplayHeight();
    screenWidth = _display->getDisplayWidth();
    frameOriginX = 1;
    frameOriginY = 17;
    frameHeight = screenHeight - frameOriginY;
    frameWidth = round(screenWidth - /*frame thickes*8*/16 - /*white spaces*/7)/8;
    indexOriginX = 5;
    indexOriginY = frameOriginY + 2 + _display->getFontAscent();
    boxHeight = 4;
    boxWidth = frameWidth - /*white spaces + frame thickness*/4;
    boxOriginX = frameOriginX + /*white spaces*/2;
    boxOriginY = indexOriginY + _display->getFontAscent();
    calcMaxNumBoxes();
}

void LiveDataContent::calcMaxNumBoxes()
{
    maxNumBoxes = round(screenHeight - frameHeight - _display->getFontAscent() - /*white spaces*/5); 
}

void LiveDataContent::drawFrames()
{
    _display->drawFrame(frameOriginX, frameOriginY, frameWidth, frameHeight);
    char index[2];
    sprintf(index, "%i", 1);
    _display->drawStr(indexOriginX, indexOriginY, index);
    for (uint8_t i = 2; i < 9; i++)
    {
        _display->drawFrame(frameOriginX + (1 + frameWidth) * (i - 1),
                            frameOriginY, frameWidth, frameHeight);
        sprintf(index, "%i", i);
        _display->drawStr(indexOriginX + (1 + frameWidth) * (i - 1), indexOriginY, index);
    }
}

void LiveDataContent::drawBoxes(uint8_t numBoxes, uint8_t frameIndex)
{
    for (uint8_t i = 0; i < numBoxes; i++)
    {
        _display->drawBox(boxOriginX, boxOriginY + boxHeight * i + 1, boxWidth, boxHeight);
    }
}

uint8_t LiveDataContent::convertAccelToBoxes(uint8_t accel)
{
    numBoxes = static_cast<uint8_t>(accel * maxNumBoxes + 0.5f);
}

void LiveDataContent::updateBoxes(uint8_t accel, uint8_t frameIndex)
{
    drawBoxes(convertAccelToBoxes(accel), frameIndex);
}

void LiveDataContent::updateBoxes(uint8_t *accel, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        updateBoxes(accel[i], i);
    }
}

void LiveDataContent::writeMessage()
{
    const char alerta[] = "Coleiras Ativas: 1,4,5,8";
    _display->drawStr(6, 12, alerta);
}
