//emissor
#include <ESP8266WiFi.h>
#include <espnow.h>

//estrutura para enviar dados
typedef struct {
   char message[32];
   int value;
} MyData;

//MAC Address do receptor
//MAC Address: 48:55:19:EC:33:EB
uint8_t receiverAddress[] = {0x48, 0x55, 0x19, 0xEC, 0x33, 0xEB};

void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
    if(status == ESP_NOW_SEND_SUCESS){
	Serial.println("Dados enviados com sucesso!");
    }else{
	Serial.println("Erro ao enviar dados");
    }
}

void setup()
{
    Serial.begin(115200);

    //incializacao do ESP-NOW
    if(esp_now_init() != ESP_OK){
	Serial.println("Erro ao inicializar o ESP-NOW");
	return;
    }

    //registro da funcao de callback para envio de dados
    esp_now_register_send_cb(onDataSent);

    //adicao do modulo receptor
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0; //canal de comunicacao
    peerInfo.encrypt = false; //sem criptografia
    esp_now_add_peer(&peerInfo);
}

void loop()
{
    //criacao e envio de dados
    MyData data;
    strcpy(data.message, "Hello ESP!");
    data.value = random(100);

    esp_now_send(receiverAddress, (uint8_t*)&data, sizeof(data));

    delay(1000);
}
