#include "ControllerState.h"


ControllerState::ControllerState(Emmiter* emmiter_observer)
{
    this->emmiter_observer = emmiter_observer; 
}

void ControllerState::set_state(state_package state_from_readings) 
{
    // se o estado mudou altere o estado atual e notifique o emmisor

    // botão para mover oara a esquerda
    if (state_from_readings.move_left_button_s != this->move_left_button_s) 
    {
        this->move_left_button_s = state_from_readings.move_left_button_s; 

        this->notify(
            this->emmiter_observer->move_engine_to_left_channel, 
            this->move_left_button_s
        );
    } 

    // botão para mover para a direita
    if (state_from_readings.move_right_button_s != this->move_right_button_s) 
    {
        this->move_right_button_s = state_from_readings.move_right_button_s; 
        this->notify(
            this->emmiter_observer->move_engine_to_right_channel,
            this->move_right_button_s    
        );
    } 


    // sensor pir esquerda
    if (state_from_readings.pir_left_s != this->pir_left_s) 
    {
        this->pir_left_s = state_from_readings.pir_left_s; 
        this->notify(
            this->emmiter_observer->pir_left,
            this->pir_left_s
        );
    } 


    // sensor pir direita
    if (state_from_readings.pir_right_s != this->pir_right_s) 
    {
        this->pir_right_s = state_from_readings.pir_right_s; 
        this->notify(
            this->emmiter_observer->pir_right,
            this->pir_right_s
        );
    } 

    // potenciometro da base
    if (
        state_from_readings.base_potentiometer_s <= this->base_potentiometer_s - 220 || 
        state_from_readings.base_potentiometer_s >= this->base_potentiometer_s + 220
    ) 
    {
        this->base_potentiometer_s = state_from_readings.base_potentiometer_s; 
        this->notify(
            this->emmiter_observer->base_potentiometer_channel,
            map(this->base_potentiometer_s, 0, 4095, 0, 180)
        );
    }

    // potenciometro do corpo

    if (
        state_from_readings.body_potentiometer_s <= this->body_potentiometer_s - 220 || 
        state_from_readings.body_potentiometer_s >= this->body_potentiometer_s + 220
    ) 
    {
        this->body_potentiometer_s = state_from_readings.body_potentiometer_s; 
        this->notify(
            this->emmiter_observer->body_potentiometer_channel,
            map(this->body_potentiometer_s, 0, 4095, 0, 180)
        );
    }
  
}

void ControllerState::notify(const char* channel, int data) 
{
    this->emmiter_observer->on_update(channel, data); 
} 