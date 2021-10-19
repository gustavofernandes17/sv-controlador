#include "Emmiter.h"


Emmiter::Emmiter(
    char* custom_network_ssid, 
    char* custom_network_pass,
    PubSubClient& mqtt_client
): mqtt_client(mqtt_client)
{

    // salva informações da rede wifi no Emissor
    this->network_password = custom_network_pass; 
    this->network_ssid = custom_network_ssid;
    this->mqtt_client = mqtt_client;
}

void Emmiter::setup(char* host, int host_port, char* device_id)
{
    // salva dados em memória
    this->host      = host; 
    this->device_id = device_id; 
    this->host_port = host_port; 

    // configura o cliente wifi com o cliente MQTT
    this->mqtt_client.setServer(host, host_port); 
    this->mqtt_client.setCallback([](char* topic, byte* payload, unsigned int lenght) {}); 

    this->handle_network_connection();
  
    // se conecta com o servidor mqtt caso ainda não esteja conectado 
    while (!this->mqtt_client.connected()) 
    {
        this->mqtt_client.connect(this->device_id); 
    }

    Serial.println("Finished setup"); 
}

void Emmiter::handle_network_connection()
{
    // inicia conexão com o wifi
    WiFi.begin(this->network_ssid, this->network_password);

    // enquanto não estiver conectado insista na conexão
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }   

    Serial.println("Conectado ao WiFi");
}

void Emmiter::on_update(const char* channel, int data) {

    Serial.println(channel);
    Serial.println(String(data));

    // indica que não houve conexão com o servidor mqtt
    if (this->mqtt_client.connected()) Serial.println("is connected");
    else Serial.println("is not connected");

    // envia os dados para a ESP32-CAM
    if (this->mqtt_client.publish(channel, String(data).c_str())) 
        Serial.println("message sent");
    else 
        Serial.println("error sending message"); 
}
