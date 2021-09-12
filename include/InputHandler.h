#ifndef INPUT_HANDLER_H 
#define INPUT_HANDLER_H

#include "ControllerState.h"
#include "Arduino.h"

class InputHandler {
    public: 
        void setup_pins(); 
        void loop();   
        InputHandler(
            ControllerState& current_state,
            int button_left_pin, 
            int button_right_pin, 
            int base_potentiometer_pin, 
            int body_potentiometer_pin, 
            int pir_left_pin, 
            int pir_right_pin
        );

    private:
        int button_left_pin; 
        int button_right_pin; 
        int base_potentiometer_pin; 
        int body_potentiometer_pin; 
        int pir_left_pin; 
        int pir_right_pin;
        ControllerState& current_state;
        
};

#endif