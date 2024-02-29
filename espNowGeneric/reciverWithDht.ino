#include <espnow.h>
#include <ESP8266WiFi.h>

//estrutura para receber dados
typedef struct{
   float temperature;
   float humidity;
}SensorData;

//funcao callback para receber dados
void onDataReceived(const uint8_t *macAddr, const uint8_t *data, int len){
    SensorData receivedData;
    memcpy(&receivedData, data, sizeof(receivedData));

    Serial.print("Temperatura recebida: ");
    Serial.print(receivedData.temperature);
    Serial.print("C | Umidade recebida");
    Serial.print(receivedData.humidity);
    serial.println(" %");
}

void setup()
{
    Serial.begin(115200);

    //inicializacao do ESP-NOW
    if (esp_now_init() != ESP_OK){
	Serial.println("Erro ao inicializar o ESP-NOW");
	return;
    }

    //registro da funcao callback para receber dados
    esp_now_register_recv_cb(onDataReceived);
}

void loop(){}
