#include "ControllerState.h"


ControllerState::ControllerState(Emmiter* emmiter_observer)
{
    // Subscreve o Emissor no Estado
    this->emmiter_observer = emmiter_observer; 
}

void ControllerState::set_state(state_package state_from_readings) 
{
    // se o estado mudou altere o estado atual e notifique o emmisor

    // botão para mover para a esquerda
    if (state_from_readings.move_left_button_s != this->move_left_button_s) 
    {   
        // altera o estado do botão para mover para a esquerda
        this->move_left_button_s = state_from_readings.move_left_button_s; 

        // notifica o emissor da alteração
        this->notify(
            this->emmiter_observer->move_engine_to_left_channel, 
            this->move_left_button_s
        );
    } 

    // botão para mover para a direita
    if (state_from_readings.move_right_button_s != this->move_right_button_s) 
    {
        // altera estado
        this->move_right_button_s = state_from_readings.move_right_button_s; 
        
        // notifica emissor
        this->notify(
            this->emmiter_observer->move_engine_to_right_channel,
            this->move_right_button_s    
        );
    } 


    // sensor pir esquerda
    if (state_from_readings.pir_left_s != this->pir_left_s) 
    {
        // altera estado
        this->pir_left_s = state_from_readings.pir_left_s; 
        
        // notifica emissor
        this->notify(
            this->emmiter_observer->pir_left,
            this->pir_left_s
        );
    } 


    // sensor pir direita
    if (state_from_readings.pir_right_s != this->pir_right_s) 
    {   
        // altera estado 
        this->pir_right_s = state_from_readings.pir_right_s; 
        // notifica o emissor
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
        // altera estado 
        this->base_potentiometer_s = state_from_readings.base_potentiometer_s; 
        // notifica o emissor
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
        // altera o estado
        this->body_potentiometer_s = state_from_readings.body_potentiometer_s; 
        // notifica o emissor
        this->notify(
            this->emmiter_observer->body_potentiometer_channel,
            map(this->body_potentiometer_s, 0, 4095, 0, 180)
        );
    }

    // botão de parada total
    if (state_from_readings.full_stop_btn != this->full_stop_btn) {

        // altera o estado 
        this->full_stop_btn = state_from_readings.full_stop_btn; 
        // notifica o emissor
        this->notify(
            this->emmiter_observer->full_stop_channel, 
            this->full_stop_btn
        );
    }
}

void ControllerState::notify(const char* channel, int data) 
{
    // Executa a função de atualização do emissor
    this->emmiter_observer->on_update(channel, data); 
} 