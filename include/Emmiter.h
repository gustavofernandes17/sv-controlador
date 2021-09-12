#ifndef EMMITER_H
#define EMMITER_H

#include "PubSubClient.h"
#include "WiFiClient.h"
#include "WiFi.h"

class Emmiter {

    public: 

        void on_update(const char* channel, int data);

        char* host; 
        int host_port; 
        char* device_id;

        const char* base_potentiometer_channel = "controlador/base"; 
        const char* body_potentiometer_channel = "controlador/corpo"; 
        const char* move_engine_to_left_channel = "controlador/esquerda";
        const char* move_engine_to_right_channel = "controlador/direita"; 

        const char* pir_left = "controlador/left"; 
        const char* pir_right = "controlador/right";

        void setup(char* host, int host_port, char* device_id);
        Emmiter(
            char* custom_network_ssid, 
            char* custom_network_pass, 
            PubSubClient& mqtt_client
        ); 

        PubSubClient& mqtt_client;
    

    private: 

        char* network_ssid; 
        char* network_password;

        void handle_network_connection();
};


#endif