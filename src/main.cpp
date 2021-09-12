#include <Arduino.h>

#include "Emmiter.h"
#include "ControllerState.h"
#include "InputHandler.h"

#include <PubSubClient.h>
#include <WiFiClient.h>

#define NUMBER_OF_INPUTS 6

// pinos de entrada analógicos
#define BASE_POT 33
#define CORPO_POT 32

// pinos de entrada digitais 
#define BTN_LEFT 16
#define BTN_RIGHT 17
#define PIR_SENSOR_01 23 
#define PIR_SENSOR_02 22

// pinos de saída digital
#define LED_COM 18
#define LED_INIT 19


char* ssid = "Cesar"; 
char* pass = "pedro0908fernandes"; 

char* broker = "broker.hivemq.com";
int port = 1883;
char* device_id = "SV-CONTROLADOR";

WiFiClient wifi_client; 
PubSubClient client(wifi_client);

Emmiter data_emmiter(ssid, pass, client); 
ControllerState controller_state(&data_emmiter);
InputHandler input_handler(
    controller_state,
    BTN_LEFT,
    BTN_RIGHT,
    BASE_POT,
    CORPO_POT,
    PIR_SENSOR_01,
    PIR_SENSOR_02
);


void setup() {
    Serial.begin(9600);

    data_emmiter.setup(broker, port, device_id); 
    input_handler.setup_pins();
}

void loop() {

    input_handler.loop();
    
    // mantem a conexão ativa
    data_emmiter.mqtt_client.loop();

}