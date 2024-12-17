#include "Config.h"
#ifdef IS_SERVER
#include "LiveDataContent.h"

void LiveDataContent::setDisplayVariables(U8G2_ST7920_128X64_F_SW_SPI *display, u8g2_uint_t* _screenWidth, u8g2_uint_t* _screenHeight)
{
    _display = display;
    _display->setFont(u8g2_font_5x7_tf);
    _display->clearDisplay();
    _display->clearBuffer();
    _frameOriginX = 1;
    _frameOriginY = 17;
    _frameHeight = *_screenHeight - _frameOriginY;
    _frameWidth = round(*_screenWidth - /*frame thickes*8*/16 - /*white spaces*/7)/8;
    _indexOriginX = 5;
    _indexOriginY = _frameOriginY + 2 + _display->getFontAscent();
    _boxHeight = 4;
    _boxWidth = _frameWidth - /*white spaces + frame thickness*/4;
    _boxOriginX = _frameOriginX + /*white spaces*/2;
    _boxOriginY = _indexOriginY + _display->getFontAscent();
    calcMaxNumBoxes();
}

void LiveDataContent::calcMaxNumBoxes()
{
    _maxNumBoxes = round(*_screenHeight - _frameHeight - _display->getFontAscent() - /*white spaces*/5); 
}

void LiveDataContent::drawFrames()
{
    _display->drawFrame(_frameOriginX, _frameOriginY, _frameWidth, _frameHeight);
    char index[2];
    sprintf(index, "%i", 1);
    _display->drawStr(_indexOriginX, _indexOriginY, index);
    for (uint8_t i = 2; i < 9; i++)
    {
        _display->drawFrame(_frameOriginX + (1 + _frameWidth) * (i - 1),
                            _frameOriginY, _frameWidth, _frameHeight);
        sprintf(index, "%i", i);
        _display->drawStr(_indexOriginX + (1 + _frameWidth) * (i - 1), _indexOriginY, index);
    }
}

void LiveDataContent::drawBoxes(uint8_t _numBoxes, uint8_t frameIndex)
{
    for (uint8_t i = 0; i < _numBoxes; i++)
    {
        _display->drawBox(_boxOriginX, _boxOriginY + _boxHeight * i + 1, _boxWidth, _boxHeight);
    }
}

uint8_t LiveDataContent::convertAccelToBoxes(uint8_t accel)
{
    _numBoxes = static_cast<uint8_t>(accel * _maxNumBoxes + 0.5f);
    return _numBoxes;
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

#endif // IS_SERVER