//Reciver
#include <ESP8266WiFi.h>
#include <espnow.h>

//estrutura para receber dados
typedef struct {
    char message[32];
    int value;
}MyData;

//funcao callback para receber dados
void onDataReceived(const uint8_t *macAddr, const uint8_t *data, int len){
    MyData receivedData;
    memcpy(&receivedData, data, sizeof(receivedData));

    Serial.print("Mensagem recebida: ");
    Serial.println(receivedData.message);
    Serial.print("Valor recebido: ");
    Serial.println(receivedData.value);
}

void setup()
{
   Serial.begin(115200);

   //inicializacao do ESP-NOW
   if(esp_now_init() != ESP_OK){
	Serial.println("Error!!!!");
	return;
   }

   //registro da funcao de callback para receber dados
   esp_now_register_recv_cb(onDataReceived);
}

void loop(){}
