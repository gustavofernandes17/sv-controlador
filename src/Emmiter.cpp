#include "Emmiter.h"


Emmiter::Emmiter(
    char* custom_network_ssid, 
    char* custom_network_pass,
    PubSubClient& mqtt_client
): mqtt_client(mqtt_client)
{
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
  
    // se conecta com o servidor mqtt
    while (!this->mqtt_client.connected()) 
    {
        this->mqtt_client.connect(this->device_id); 
    }

    Serial.println("Finished setup"); 
}

/**
 * Connects to the wifi network
*/
void Emmiter::handle_network_connection()
{
    WiFi.begin(this->network_ssid, this->network_password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }   

    Serial.println("Connected to wifi"); 
}

void Emmiter::on_update(const char* channel, int data) {

    

    Serial.println(channel);
    Serial.println(String(data));

    if (this->mqtt_client.connected()) Serial.println("is connected");
    else Serial.println("is not connected");

    if (this->mqtt_client.publish(channel, String(data).c_str())) Serial.println("message sent");
    else Serial.println("error sending message"); 
}
