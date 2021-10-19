#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include "Emmiter.h"
#include "Arduino.h"


// define uma estrutura para guardar informações do estado e das entradas do 
// InputHandler
typedef struct {

    int base_potentiometer_s; 
    int body_potentiometer_s; 
    int move_left_button_s; 
    int move_right_button_s;
    int pir_left_s; 
    int pir_right_s; 
    int full_stop_btn;

} state_package;  

class ControllerState {
    public: 
        // construtor 
        ControllerState(Emmiter* emmiter_observer);

        /**
         * Realiza alguma alteração no estado
        */
        void set_state(state_package state_from_readings);

        /**
         * Obtêm uma cópia do estado atual
        */
        state_package get_state();

    private:

        // informações do Estado Atual
        int base_potentiometer_s = 0; 
        int body_potentiometer_s = 0; 
        int move_left_button_s = 0; 
        int move_right_button_s = 0;
        int pir_left_s = 0; 
        int pir_right_s = 0; 
        int full_stop_btn = 0;

        // Notifica todos as classes subscritas que houve alguma alteração no 
        // estado
        void notify(const char* channel, int data);

        // Instância do Emissor
        Emmiter* emmiter_observer; 
}; 

#endif