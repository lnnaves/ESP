#include <DHT.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

//definindo pinos do sensor
#define DHTTYPE DHT11
uint8_t DHTPin = D1;

//criando uma instancia do sensor dht
DHT dht(DHTPIN, DHTTYPE);

//MAC Address modulo receptor
//MAC Address: 48:55:19:EC:33:EB
uint8_t receiverAddress[] = {0x48, 0x55, 0x19, 0xEC, 0x33, 0xEB};

//estrutura para enviar dados
typedef struct {
  float temperature;
  float humidity;
} SensorData;

void setup()
{
    Serial.begin(115200);

    //inicializa o sensor DHT
    dht.begin();

    //inicializacao do ESP-NOW
    if(esp_now_init() != ESP_OK){
	Serial.println("Erro ao inicializar o ESP-NOW");
	return;
    }

    //adicao do modulo receptor
    esp_now_peer_int_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0; //canal de comunicacao
    peerInfo.encrypt = false //sem criptografia
    esp_now_add_peer(&peerInfo);
}

void loop()
{
    //leitura da temperatura e umidade
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    //envio de dados via ESP-NOW
    esp_err_t result = esp_now_send(receiverAddress, (uint8_t*)&data, sizeof(data));
    if (result == ESP_OK){
	Serial.println("Dados enviados com sucesso!");
    }else{
	Serial.println("Erro ao enviar dados");
    }

    delay(1000);
}
