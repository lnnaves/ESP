//Emissor
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "DHT.h"
#define DHTTYPE DHT11
//Coloque na linha abaixo o Mac Address do NodeMCU receptor
//MAC Address: 48:55:19:ec:60:cb // MAC Address: 48:55:19:EC:33:EB(motor)
uint8_t broadcastAddress[] = {0x48, 0x55, 0x19, 0xEC, 0x33, 0xEB};
//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct struct_message
{
  //String a;
  float Temperature;
  float Humidity;
} struct_message;
//Definicoes sensor
uint8_t DHTPin =  D2;
//inicializa o sensor
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

//Cria uma struct_message chamada myData
struct_message myData;
//Callback quando os dados sao enviados
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
  Serial.print("Status dos dados enviados: ");
  if (sendStatus == 0) {
    Serial.println("Envio ok!");
  }
  else {
    Serial.println("Falha no envio!");
  }
}
void setup()
{
  Serial.begin(115200);
  //Inicializa o pino do botao
  pinMode(DHTPin, INPUT);
  dht.begin();
  //Coloca o dispositivo no modo Wi-Fi Station
  WiFi.mode(WIFI_STA);
  //Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  //Registra o destinatario da mensagem
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
void loop()
{
  valor = digitalRead(DHTPin);
  if (valor == 1)
  {
    while (digitalRead(DHTPin) == 1)
    {
      delay(50);
    }
    //Serial.println("Botao pressionado!");
    //Inverte o estado do led
    //inverte_led = !inverte_led;
    //Envia a string de acordo com o estado do led
    //if (inverte_led == 1)
    //{
      //myData.a = "L_Led";
    //}
    //if (inverte_led == 0)
    //{
      //myData.a = "D_Led";
    //}
    //Envia a mensagem usando o ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
}
