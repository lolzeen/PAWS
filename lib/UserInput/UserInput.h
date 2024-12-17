#include "Config.h"
#ifdef IS_SERVER
#ifndef PAWS_LIB_USERINPUT_H
#define PAWS_LIB_USERINPUT_H
#include <RotaryEncoder.h>
#include "ArduinoLog.h"

template <int encoderPinA, int encoderPinB, int buttonPin>
class UserInput
{
public:
    UserInput();
    
    static UserInput* getInstance()
    {
        static UserInput u;
        return &u;
    }

    bool buttonJustPressed(); // Returns true if the button was just pressed (after debounce)
    int getPosition();
    RotaryEncoder::Direction getDirection();
    bool hasEncoderChanged() { return ISR_statusChange;}
    void init();
    bool isButtonPressed() const { return _buttonState; } // Returns true if the button is currently pressed (debounced)
    void updateButtonState();                             // Call this function in the loop to process the button reading and debouncing
    bool processChanges();

    void IRAM_ATTR onTimer(); // Timer ISR for button polling
    static void enableInputMonitoring();

private:
    // button
    uint8_t _pin;                     // GPIO pin for the button
    unsigned long _debounceTime;      // Debounce interval in milliseconds
    volatile bool _buttonPressedFlag; // Raw flag indicating whether button was pressed
    bool _buttonState;                // Current debounced state of the button
    bool _lastButtonState;            // Last debounced state of the button
    bool _justPressed;                // Flag for just-pressed state
    unsigned long _lastDebounceTime;  // Last time the button state was changed
    // encoder
    int pos = 0;
    RotaryEncoder::Direction direction;
    static RotaryEncoder *encoder;
    static bool ISR_statusChange;

    static void ISR_checkPosition();
};

template <int encoderPinA, int encoderPinB, int buttonPin>
RotaryEncoder* UserInput<encoderPinA, encoderPinB, buttonPin>::encoder = nullptr;
template <int encoderPinA, int encoderPinB, int buttonPin>
bool UserInput<encoderPinA, encoderPinB, buttonPin>::ISR_statusChange = false;

#endif // PAWS_LIB_USERINPUT_H
#endif // IS_SERVER