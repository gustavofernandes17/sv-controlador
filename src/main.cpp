#include <Arduino.h>

#include "Emmiter.h"
#include "ControllerState.h"
#include "InputHandler.h"

#include <PubSubClient.h>
#include <WiFiClient.h>

#define NUMBER_OF_INPUTS 7 // número de pinos I/O sendo utilizados

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

// pino do botão de parada total
#define FULL_STOP 20

// Rede WiFi
char* ssid = "Redmi Note 7"; 
char* pass = "b6ee8b98282c"; 

// Informações do Broker MQTT 
char* broker = "broker.hivemq.com"; // URI do Servidor
int port = 1883; // Porta do Servidor
char* device_id = "SV-CONTROLADOR"; // ID do dispositivo

// Inicializa os Objetos

// Inicializa o Client WiFi
WiFiClient wifi_client; 

// Inicializa o Client MQTT
PubSubClient client(wifi_client);

// Inicializa o Emissor
Emmiter data_emmiter(ssid, pass, client); 

// Inicializa o Estado do Controlador
ControllerState controller_state(&data_emmiter);

// Inicializa o InputHandler
InputHandler input_handler(
    controller_state,
    BTN_LEFT,
    BTN_RIGHT,
    BASE_POT,
    CORPO_POT,
    PIR_SENSOR_01,
    PIR_SENSOR_02,
    FULL_STOP
);


void setup() {

    // inicia comunicação serial para fins de depuração
    Serial.begin(9600);

    // inicializa o Emissor
    data_emmiter.setup(broker, port, device_id); 

    // inicializa o InputHandler e configura todos os pinos de I/O
    input_handler.setup_pins();
}

void loop() {

    // Realiza a leitura das entradas de maneira contínua
    input_handler.loop();
    
    // mantem a conexão ativa com a ESP32-CAM
    data_emmiter.mqtt_client.loop();

}