#include <Arduino.h>

#include "now.h"
#define CHANNEL 5

Now::Now (
    uint8_t gpios[],
    uint8_t macSlaves[][6]
)
{
    
    //Passando o array gpios
    int len = sizeof(gpios)/sizeof(gpios[0]);
    for (int i=0; i<len; i++){
        _gpios[i] =  gpios[i];
    }
    

    //Passando a matriz macSlaves
    len =  sizeof macSlaves / sizeof macSlaves[0];  
    for (int i=0; i<len; i++){
        for (int j=0; j<6; j++){
            _macSlaves[i][j] = macSlaves[i][j];
        }
    }
}

void Now::Master () {

    //Colocamos o ESP em modo station
    WiFi.mode(WIFI_STA);

    //Mostramos no Monitor Serial o Mac Address deste ESP quando em modo station
    Serial.print("Mac Address in Station: "); 
    Serial.println(WiFi.macAddress());

    InitESPNow();

    int slavesCount = sizeof(_macSlaves)/6/sizeof(uint8_t);

    //Para cada slave
    for(int i=0; i<slavesCount; i++){
        //Criamos uma variável que irá guardar as informações do slave
        esp_now_peer_info_t slave;
        //Informamos o canal
        slave.channel = CHANNEL;
        //0 para não usar criptografia ou 1 para usar
        slave.encrypt = 0;
        //Copia o endereço do array para a estrutura
        memcpy(slave.peer_addr, _macSlaves[i], sizeof(_macSlaves[i]));
        //Adiciona o slave
        esp_now_add_peer(&slave);
    }

    //Registra o callback que nos informará sobre o status do envio
    esp_now_register_send_cb(OnDataSent);

    Send();
}

void Now::Slave () {

    //Colocamos o ESP em modo station
    WiFi.mode(WIFI_STA);
    //Mostramos no Monitor Serial o Mac Address deste ESP quando em modo station
    Serial.print("Mac Address in Station: "); 
    Serial.println(WiFi.macAddress());

    //Chama a função que inicializa o ESPNow
    InitESPNow();

    //Registra o callback que nos informará quando o Master enviou algo
    esp_now_register_recv_cb(OnDataRecv);
}

//Verifica a inicializacao da ESP
void Now::InitESPNow() {
  //Se a inicialização foi bem sucedida
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  //Se houve erro na inicialização
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

//Função que recebe os valores a serem enviados e envia os dados
void Now::Send(){

    //Exemplo de passagem de dados
    _data myData;
    myData.time = millis();

    //Envio de dados para todas esps (default)
    uint8_t broadcast[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF};
    esp_err_t result = esp_now_send(broadcast, (uint8_t*) &myData, sizeof(myData));
    Serial.print("Send Status: ");
    //Se o envio foi bem sucedido
    if (result == ESP_OK) {
        Serial.println("Success");
    }
    //Se aconteceu algum erro no envio
    else {
        Serial.println("Error");
    }
}

// Callback do envio da master para slave
void Now::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: "); Serial.println(macStr);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//Função que recebe os dados e o tam da string data
void Now::OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len) {
    char macStr[18];
    
    //Struct que recebere os dados enviados pela Master
    _data myData;

    //Copiamos o Mac Address origem para uma string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    
    //Mostramos o Mac Address que foi a origem da mensagem
    Serial.print("Received from: "); 
    Serial.println(macStr);
    Serial.println("");
    
    //Testando os dados
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Tempo:");
    Serial.println(myData.time); 
}