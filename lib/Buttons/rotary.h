#include <RotaryEncoder.h>
#include "Config.h"
#include "ArduinoLog.h"


template<int enc_a_pin, int enc_b_pin, int enc_btn_pin>
class Rotary{
    private:
        static RotaryEncoder* encoder;
        static bool ISR_status_change;

        int pos = 0;
        int direction = 0;

        static void ISR_checkPosition(){
            instance()->encoder->tick();
            instance()->ISR_status_change = true;
        }


    public:
        Rotary(){
            Log.traceln(F("[Rotary] OBJ created with: %s, %s, %s"), std::to_string(enc_a_pin), std::to_string(enc_b_pin), std::to_string(enc_btn_pin));
        }

        static Rotary* instance(){ //Create Rotrary object (if none was created)  and return its reference.
            static Rotary r;
            return &r;
        }

        void init(){
            Log.traceln(F("[Rotary] Start Rotary;"));
            Log.traceln(F("[Rotary] OBJ created with: %s, %s, %s"), std::to_string(enc_a_pin), std::to_string(enc_b_pin), std::to_string(enc_btn_pin));
            encoder = new RotaryEncoder(enc_a_pin, enc_b_pin, RotaryEncoder::LatchMode::TWO03);
            attachInterrupt(digitalPinToInterrupt(enc_a_pin), ISR_checkPosition, CHANGE);
            attachInterrupt(digitalPinToInterrupt(enc_b_pin), ISR_checkPosition, CHANGE);
            ISR_status_change = false;
        }

        bool has_changed(){
            return ISR_status_change;
        }

        bool process_changes(){
            if(instance()->ISR_status_change){
                int newPos = instance()->encoder->getPosition();
                if(newPos != pos){
                    pos = newPos;
                    direction = instance()->encoder->getDirection();
                    Log.traceln(F("[Rotary] POS: %s;"), String(pos));
                    ISR_status_change = false;
                    return true;
                }
                Log.traceln(F("[Rotary] No change detected;"));
            }
            return false;
        }
        
        int get_pos(){
            instance()->process_changes();
            return pos;
        }

        int get_direction(){
            instance()->process_changes();
            return direction;
        }
};

template<int enc_a_pin, int enc_b_pin, int enc_btn_pin>
RotaryEncoder* Rotary<enc_a_pin, enc_b_pin, enc_btn_pin>::encoder = nullptr;

template<int enc_a_pin, int enc_b_pin, int enc_btn_pin>
bool Rotary<enc_a_pin, enc_b_pin, enc_btn_pin>::ISR_status_change = false;