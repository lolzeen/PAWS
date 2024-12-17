#include "Config.h"
#ifdef IS_SERVER
#include "ScreenController.h"
#include "LiveDataContent.h"

ScreenController::~ScreenController()
{
    _display.clearBuffer();
    _display.clearDisplay();
}

void ScreenController::initScreen()
{
    _display.begin();
    _display.clearBuffer();
    _display.clearDisplay();
    Log.traceln(F("Started display with CLK: %d, DATA: %d and CS: %d"), LCD_EN_PIN, LCD_RS_PIN, LCD_RW_PIN);
    _screenHeight = _display.getDisplayHeight();
    Log.traceln(F("Screen height: %d"), _screenHeight);
    _screenWidth = _display.getDisplayWidth();
    Log.traceln(F("Screen width: %d"), _screenWidth);
    refresh<ScreenVariable::PossibleContents::INIT>();
}

void ScreenController::getResultOfButtonAction()
{
    switch (_currentFocus)
    {
    case ScreenVariable::PossibleFocus::RETURN_MAIN_MENU:
        _currentContent = ScreenVariable::PossibleContents::MAIN_MENU;
        break;

    case ScreenVariable::PossibleFocus::CONNECT:
        _currentContent = ScreenVariable::PossibleContents::CONNECT;
        break;

    case ScreenVariable::PossibleFocus::BATTERY_LEVEL:
        _currentContent = ScreenVariable::PossibleContents::BATTERY_LEVEL;
        break;

    case ScreenVariable::PossibleFocus::LIVE_DATA:
        _currentContent = ScreenVariable::PossibleContents::LIVE_DATA;
        break;

    case ScreenVariable::PossibleFocus::SETTINGS:
        _currentContent = ScreenVariable::PossibleContents::SETTINGS;
        break;

    case ScreenVariable::PossibleFocus::UNDEFINED:
        Log.errorln(F("Undefined button action ocurred at %s with current focus set to %s."), _currentContent, _currentFocus);
    }
}

void ScreenController::getResultOfEncoderAction(InputType action)
{
    switch (_currentContent)
    {
    case ScreenVariable::PossibleContents::MAIN_MENU:
        switch (_currentFocus)
        {
        case ScreenVariable::PossibleFocus::SETTINGS:
            if (action == InputType::ENCODER_RIGHT)
            {
                _currentFocus = ScreenVariable::PossibleFocus::CONNECT;
            }
            else
            {
                _currentFocus = ScreenVariable::PossibleFocus::LIVE_DATA;
            }
            break;
        case ScreenVariable::PossibleFocus::CONNECT:
            if (action == InputType::ENCODER_RIGHT)
            {
                _currentFocus = ScreenVariable::PossibleFocus::LIVE_DATA;
            }
            else
            {
                _currentFocus = ScreenVariable::PossibleFocus::SETTINGS;
            }
            break;
        case ScreenVariable::PossibleFocus::LIVE_DATA:
            if (action == InputType::ENCODER_RIGHT)
            {
                _currentFocus = ScreenVariable::PossibleFocus::SETTINGS;
            }
            else
            {
                _currentFocus = ScreenVariable::PossibleFocus::CONNECT;
            }
            break;

        default:
            break;
        }
        break;
    case ScreenVariable::PossibleContents::CONNECT:
        /* code */
        break;
    case ScreenVariable::PossibleContents::BATTERY_LEVEL:
        /* code */
        break;
    case ScreenVariable::PossibleContents::SETTINGS:
        /* code */
        break;
    case ScreenVariable::PossibleContents::LIVE_DATA:
        /* code */
        break;
    case ScreenVariable::PossibleContents::INIT:
        /* code */
        break;

    default:
        break;
    }
}

void ScreenController::refresh(uint8_t* accel, size_t numAccels)
{
    // funcao que desenha a tela conforme o conteudo
    LiveDataContent content;
    content.setDisplayVariables(&_display, &_screenWidth, &_screenHeight);
    content.updateBoxes(accel, numAccels);
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::INIT>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.drawXBM(0,0, _screenWidth, _screenHeight, ScreenVariable::initScreenXBM);
    _display.sendBuffer();
    Log.traceln("Displaying welcome screen.");
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::CONNECT>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::SETTINGS>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::BATTERY_LEVEL>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::CONNECT>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::LIVE_DATA>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}
template <>
void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::SETTINGS>()
{
    // funcao que desenha a tela conforme o conteudo
    _display.sendBuffer();
}

void ScreenController::setContentBasedOnAction(InputType action)
{
    if (action == InputType::BUTTON_PRESS)
    {
        getResultOfButtonAction();
        setFocusOnContentChage();
    }
    else
    {
        getResultOfEncoderAction(action);
    }
}

void ScreenController::setFocusOnContentChage()
{
    switch (_currentContent)
    {
    case ScreenVariable::PossibleContents::MAIN_MENU:
        _currentFocus = ScreenVariable::PossibleFocus::CONNECT;
        break;
    case ScreenVariable::PossibleContents::CONNECT:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
        break;
    case ScreenVariable::PossibleContents::BATTERY_LEVEL:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
        break;
    case ScreenVariable::PossibleContents::SETTINGS:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
        break;
    case ScreenVariable::PossibleContents::LIVE_DATA:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
        break;
    case ScreenVariable::PossibleContents::INIT:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
        break;
    default:
        _currentFocus = ScreenVariable::PossibleFocus::UNDEFINED;
    }
}

// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::INIT>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::LIVE_DATA>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::CONNECT>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::BATTERY_LEVEL>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::CONNECT>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::LIVE_DATA>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::MAIN_MENU, ScreenVariable::PossibleFocus::SETTINGS>();
// template <>
// void ScreenController::refresh<ScreenVariable::PossibleContents::SETTINGS>();

#endif // IS_SERVER
