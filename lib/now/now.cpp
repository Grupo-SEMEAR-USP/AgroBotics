#include <Arduino.h>

#include "now.h"
#define CHANNEL 5

/** DECLARANDO STRUCTS **/

sdata_t Now::myData; 
sdata_t Now::otherData;

/** DECLARANDO MÉTODOS **/

/**
 * @brief Construtura da  classe
 * @param gpios Pinos que terão seus valores enviados
 * @param macSlaves Endereços das ESPs que receberam os dados da Master
 * @param id ID de identificação do robô
*/
Now::Now (
    uint8_t gpios[],
    uint8_t macSlave[6],
    int id)
{
    
    //Passando o array gpios
    int len = sizeof(gpios)/sizeof(gpios[0]);
    for (int i=0; i<len; i++){
        _gpios[i] =  gpios[i];
    }
    

    //Passando a matriz macSlaves
    for (int i=0; i<6; j++){
        _macSlave[i] = macSlave[i];
    }
    
    //Passando o ID
    Now::myData.id = id;
}

/* Inicializa o modo de comunicação na ESP */
void Now::Init (){
   //Colocamos o ESP em modo station
    WiFi.mode(WIFI_STA);

    //Mostramos no Monitor Serial o Mac Address deste ESP
    Serial.print("Mac Address no modo Station: "); 
    Serial.println(WiFi.macAddress());

    InitESPNow();

    //Criamos uma variável que irá guardar as informações do slave
    esp_now_peer_info_t slave;
    //Informamos o canal
    slave.channel = CHANNEL;
    //0 para não usar criptografia
    slave.encrypt = 0;
    //Copia o endereço do array para a estrutura
    memcpy(slave.peer_addr, _macSlave, sizeof(_macSlave));
    //Adiciona o slave
    esp_now_add_peer(&slave);
}

/* Verifica a inicialização da ESP */
void Now::InitESPNow() {
    //Se a inicialização foi bem sucedida
    if (esp_now_init() == ESP_OK) {
        Serial.println("ESPNow Init sucedida");
    }
    //Se houve erro na inicialização
    else {
        Serial.println("ESPNow Init erro");
        ESP.restart();
    }
}

/* Envio de dados para os Slaves */
void Now::Master () {
    //Registra o callback que nos informará sobre o status do envio
    esp_now_register_send_cb(OnDataSent);

    Send();
}

/* Recebimento de dados da Master */
void Now::Slave () {
    //Registra o callback que nos informará quando o Master enviou algo
    esp_now_register_recv_cb(OnDataRecv);
}

/* Faz o envio de fato para os Slaves */
void Now::Send(){

    esp_err_t result = esp_now_send(_macSlave, (uint8_t*) &(Now::myData), sizeof(Now::myData));
    Serial.print("Send status: ");
    //Se o envio foi bem sucedido
    if (result == ESP_OK) {
        Serial.println("Sucedido");
    }
    //Se aconteceu algum erro no envio
    else {
        Serial.println("Erro");
    }
}

/* Callback do envio da master para slave */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print("Último pacote mandado para: "); Serial.println(macStr);
    Serial.print("Último pacote status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "mandado com sucesso" : "erro");
}

/* Callback do recebimento de dados e armazenamento dele */
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len) {
    char macStr[18];

    //Copiamos o Mac Address origem para uma string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

    //Mostramos o Mac Address que foi a origem da mensagem
    Serial.print("Recebido do: "); 
    Serial.println(macStr);
    Serial.println("");

    //Salvamos a string na struct
    memcpy(&(Now::otherData), incomingData, sizeof(Now::otherData));
}