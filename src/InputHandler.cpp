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
    // salva o valor dos pinos dentro da instancia do objeto
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
    // coloca todos os pinos em um vetor (Array)
    int pins[7] = {    
        this->button_left_pin, 
        this->button_right_pin, 
        this->base_potentiometer_pin, 
        this->body_potentiometer_pin, 
        this->pir_left_pin, 
        this->pir_right_pin,
        this->full_stop_btn_pin
    }; 

    // Realiza uma iteração pelos pinos
    // para cada pino dentro do Array de pinos configura o mesmo 
    // como Entrada Digital ou Analógica
    for (int i = 0; i < 7; i++)
    {
        pinMode(pins[i], INPUT);
    }
}

void InputHandler::loop() 
{
    // cria uma estrutura para salvar as leituras
    state_package state_readings;

    // realiza a leitura dos potenciômetros
    state_readings.base_potentiometer_s = analogRead(this->base_potentiometer_pin); 
    state_readings.body_potentiometer_s = analogRead(this->body_potentiometer_pin);

    // realiza a leitura dos botões de controle dos motores DC
    state_readings.move_left_button_s = digitalRead(this->button_left_pin); 
    state_readings.move_right_button_s = digitalRead(this->button_right_pin); 

    // realiza a leitura dos sensores PIR
    state_readings.pir_left_s = digitalRead(this->pir_left_pin); 
    state_readings.pir_right_s = digitalRead(this->pir_right_pin);

    // realiza a leitura do botão de parada total
    state_readings.full_stop_btn = digitalRead(this->full_stop_btn_pin);
    
    // realiza a alteração do estado
    this->current_state.set_state(state_readings);

    // realiza uma pausa de meio segundo para que as mudanças não sejam tão bruscas 
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