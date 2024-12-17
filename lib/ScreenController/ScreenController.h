#include "Config.h"
#ifdef IS_SERVER
#ifndef PAWS_LIB_SCREENCONTROLLER_H
#define PAWS_LIB_SCREENCONTROLLER_H

#include "U8g2lib.h"
#include "ScreenVariables.h"
#include "InputType.h"

struct StaticContent
{
    unsigned short uid;
    char background[1024];
};

class ScreenController
{
public:
    ScreenController() : _display(U8G2_R0, LCD_EN_PIN, LCD_RS_PIN, LCD_RW_PIN, U8X8_PIN_NONE) {};
    ~ScreenController();

    void initScreen();
    template <ScreenVariable::PossibleContents content, ScreenVariable::PossibleFocus focus = ScreenVariable::PossibleFocus::UNDEFINED, uint8_t* ...>
    void refresh();
    void refresh(uint8_t* accel, size_t numAccels);
    ScreenVariable::PossibleContents getCurrentContent() { return _currentContent; }
    void setContentBasedOnAction(InputType action);

private:

    enum ScreenVariable::PossibleContents _currentContent = ScreenVariable::PossibleContents::INIT;
    enum ScreenVariable::PossibleFocus _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
    U8G2_ST7920_128X64_F_SW_SPI _display;
    bool _encoderHasChangedPosition;
    u8g2_uint_t _screenHeight;
    u8g2_uint_t _screenWidth;
    void getResultOfButtonAction();
    void getResultOfEncoderAction(InputType action);
    void setFocusOnContentChage();
};

template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::INIT>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::LIVE_DATA>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::CONNECT>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::BATTERY_LEVEL>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::CONNECT>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::SETTINGS>();
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::SETTINGS>();

#endif // PAWS_LIB_SCREENCONTROLLER_H
#endif // IS_SERVER