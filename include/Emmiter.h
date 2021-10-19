#ifndef EMMITER_H
#define EMMITER_H

// Realiza todas as importações necessárias
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "WiFi.h"

// define a classe do Emissor
class Emmiter {

    public: 
        /**
         * É chamada toda vez que ocorre uma alteração no estado do controlador
         * ela é a responsável por enviar os dados para a ESP32-CAM
        */
        void on_update(const char* channel, int data);

        // informações do servidor MQTT
        char* host; 
        int host_port; 
        char* device_id;

        // tópicos MQTT em que o painel de controle está subscrito

        // canal do servo da base
        const char* base_potentiometer_channel = "controlador/base"; 

        // canal do servo do corpo
        const char* body_potentiometer_channel = "controlador/corpo"; 

        // canal para movimentar os motores para esquerda
        const char* move_engine_to_left_channel = "controlador/esquerda";

        // canal para movimentar os motores para a direita
        const char* move_engine_to_right_channel = "controlador/direita"; 

        // canal para enviar informações sobre os sensores PIR
        const char* pir_left = "controlador/left"; 
        const char* pir_right = "controlador/right";

        // canal para para todos os motores
        const char* full_stop_channel = "controlador/stop";

        /**
         * Realiza a configuração e conexão como Servidor MQTT 
        */
        void setup(char* host, int host_port, char* device_id);

        // Método construtor
        Emmiter(
            char* custom_network_ssid, 
            char* custom_network_pass, 
            PubSubClient& mqtt_client
        ); 

        // Cliente MQTT 
        PubSubClient& mqtt_client;
    

    private: 
        // informações da rede WiFi
        char* network_ssid; 
        char* network_password;

        /**
         * Realiza conexão com o WiFi
        */
        void handle_network_connection();
};


#endif