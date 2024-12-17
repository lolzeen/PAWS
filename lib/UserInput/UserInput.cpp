#include "Config.h"
#ifdef IS_SERVER
#include "UserInput.h"

template  <int encoderPinA, int encoderPinB, int buttonPin>
UserInput<encoderPinA, encoderPinB, buttonPin>::UserInput()
{
    Log.traceln(F("[UserInput] OBJ created with: %s, %s, %s"), std::to_string(encoderPinA), std::to_string(encoderPinB), std::to_string(buttonPin));
}

template  <int encoderPinA, int encoderPinB, int buttonPin>
void UserInput<encoderPinA, encoderPinB, buttonPin>::init()
{
    Log.traceln(F("[UserInput] Start UserInput;"));
    Log.traceln(F("[UserInput] OBJ created with: %s, %s, %s"), std::to_string(encoderPinA), std::to_string(encoderPinB), std::to_string(buttonPin));
    encoder = new RotaryEncoder(encoderPinA, encoderPinB, RotaryEncoder::LatchMode::TWO03);
    attachInterrupt(digitalPinToInterrupt(encoderPinA), ISR_checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), ISR_checkPosition, CHANGE);
    ISR_statusChange = false;
    /*
    _buttonState = false;
    _lastButtonState = false;
    _buttonPressedFlag = false;
    _debounceTime = 50;
    _justPressed = false;
    pinMode(buttonPin, INPUT_PULLUP);
    timerBegin(0, 80, true);                 // Timer 0, prescaler of 80, count up
    // timerAttachInterrupt(0, timerISR, true); // Attach the interrupt function
    timerAlarmWrite(0, 100000, true);        // Trigger every 100 ms
    timerAlarmEnable(0);                     // Enable the timer
    */   
}
template  <int encoderPinA, int encoderPinB, int buttonPin>
bool UserInput<encoderPinA, encoderPinB, buttonPin>::processChanges()
{
    if (getInstance()->ISR_statusChange)
    {
        int newPos = getInstance()->encoder->getPosition();
        if (newPos != pos)
        {
            pos = newPos;
            direction = getInstance()->getDirection();
            Log.traceln(F("[UserInput] POS: %s;"), String(pos));
            ISR_statusChange = false;
            return true;
        }
        Log.traceln(F("[UserInput] No change detected;"));
    }
    return false;
}
template  <int encoderPinA, int encoderPinB, int buttonPin>
int UserInput<encoderPinA, encoderPinB, buttonPin>::getPosition()
{
    getInstance()->processChanges();
    return pos;
}
template  <int encoderPinA, int encoderPinB, int buttonPin>
RotaryEncoder::Direction UserInput<encoderPinA, encoderPinB, buttonPin>::getDirection()
{
    getInstance()->processChanges();
    return direction;
}

/*void UserInput::updateButtonState()
{
    if (_buttonPressedFlag)
    {
        unsigned long currentMillis = millis();
        bool rawState = digitalRead(_pin) == LOW; // Button pressed is LOW

        // If the state has changed, reset the debounce timer
        if (rawState != _lastButtonState)
        {
            _lastDebounceTime = currentMillis;
        }

        // If enough time has passed since the last debounce, update the button state
        if ((currentMillis - _lastDebounceTime) > _debounceTime)
        {
            if (rawState != _buttonState)
            {
                _buttonState = rawState;

                // If the button was pressed, set the justPressed flag
                _justPressed = _buttonState;
            }
            else
            {
                _justPressed = false; // Reset justPressed if button not pressed
            }
        }

        _lastButtonState = rawState; // Update last button state
        _buttonPressedFlag = false;  // Reset the flag after processing
    }
}

bool UserInput::buttonJustPressed()
{
    bool wasJustPressed = _justPressed;
    _justPressed = false; // Clear the flag after it is read
    return wasJustPressed;
}

// Timer ISR: Sets the flag if the button state has changed
void IRAM_ATTR UserInput::onTimer()
{
    enableInputMonitoring();
}

void UserInput::enableInputMonitoring()
{
}*/
template  <int encoderPinA, int encoderPinB, int buttonPin>
void UserInput<encoderPinA, encoderPinB, buttonPin>::ISR_checkPosition()
{
    getInstance()->encoder->tick();
    getInstance()->ISR_statusChange = true;
}

template class UserInput<ENC_A_PIN, ENC_B_PIN, BTN_PIN>;
#endif // IS_SERVER