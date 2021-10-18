#include "InputHandler.h"


InputHandler::InputHandler(
    ControllerState& current_state,
    int button_left_pin, 
    int button_right_pin, 
    int base_potentiometer_pin, 
    int body_potentiometer_pin, 
    int pir_left_pin, 
    int pir_right_pin,
    int full_stop_btn_pin
): current_state(current_state) 
{
    this->current_state = current_state;

    this->button_left_pin = button_left_pin;
    this->button_right_pin = button_right_pin; 
    this->base_potentiometer_pin = base_potentiometer_pin;
    this->body_potentiometer_pin = body_potentiometer_pin;
    this->pir_left_pin = pir_left_pin; 
    this->pir_right_pin = pir_right_pin;
}

void InputHandler::setup_pins() 
{
    int pins[7] = {    
        this->button_left_pin, 
        this->button_right_pin, 
        this->base_potentiometer_pin, 
        this->body_potentiometer_pin, 
        this->pir_left_pin, 
        this->pir_right_pin,
        this->full_stop_btn_pin
    }; 

    for (int i = 0; i < 6; i++)
    {
        pinMode(pins[i], INPUT);
    }
}

void InputHandler::loop() 
{
    state_package state_readings;

    state_readings.base_potentiometer_s = analogRead(this->base_potentiometer_pin); 
    state_readings.body_potentiometer_s = analogRead(this->body_potentiometer_pin);

    state_readings.move_left_button_s = digitalRead(this->button_left_pin); 
    state_readings.move_right_button_s = digitalRead(this->button_right_pin); 

    state_readings.pir_left_s = digitalRead(this->pir_left_pin); 
    state_readings.pir_right_s = digitalRead(this->pir_right_pin);
    state_readings.full_stop_btn = digitalRead(this->full_stop_btn_pin);


    this->current_state.set_state(state_readings);
    delay(500); 

    // char msg[100]; 
    
    // sprintf(
    //     msg, 
    //     "base pot: %i\n body pot: %i\n left btn: %i\n right btn: %i\n",
    //     state_readings.base_potentiometer_s,
    //     state_readings.body_potentiometer_s,
    //     state_readings.move_left_button_s,
    //     state_readings.move_right_button_s
    // );

    // Serial.println(msg);
}