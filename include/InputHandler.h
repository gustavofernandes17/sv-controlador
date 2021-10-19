#ifndef INPUT_HANDLER_H 
#define INPUT_HANDLER_H

// Faz a importação do Estado do controlador
#include "ControllerState.h"

// importa o Framework do Arduino
#include "Arduino.h"

// Define a Classe
class InputHandler {
    public: 
        /**
         * Função responsável por configurar todos pinos como Entrada ou Saída 
        */
        void setup_pins(); 
        /**
         * Função que realiza as leituras do Hardware e as passa para o Estado 
         * do Controlador (Painel de Controle)
        */
        void loop();   

        /**
         * Construtor inicializa o objeto
        */
        InputHandler(
            ControllerState& current_state,
            int button_left_pin, 
            int button_right_pin, 
            int base_potentiometer_pin, 
            int body_potentiometer_pin, 
            int pir_left_pin, 
            int pir_right_pin,
            int full_stop_btn_pin
        );

    private:
        // Pinos, dos botões, sensores e potenciometros 
        int button_left_pin; 
        int button_right_pin; 
        int base_potentiometer_pin; 
        int body_potentiometer_pin; 
        int pir_left_pin; 
        int pir_right_pin;
        int full_stop_btn_pin;

        // instancia do estado atual
        ControllerState& current_state; 
        
};

#endif