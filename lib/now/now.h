#ifndef now_h
#define now_h

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

/* Struct que definira os dados a serem enviados e recebidos pelo robô */
typedef struct Data {
    int id = 0;             //ID do robô
    int moveType = 0;       //Tipo de movimento que o robô ira fazer
    double time = 0;        //Tempo total de movimento
    int status = 0;         //Irá percorrer o trajeto ou não
    bool position = false;  //Está posicionado na trajetória ou não
    bool ready = false;     //Está posicionado na colheitadeira ou não
} sdata_t;

/* Classe para comunicação entre ESPs (ESP Now)*/
class Now {
    protected:
        uint8_t _gpios[];           //Pinos que serão utilizados na comunicação
        uint8_t _macSlaves[][6];    //Endereços das ESPs que receberam os dados da Master
    public:
        Now (uint8_t gpios[], uint8_t macSlaves[][6], int id);
        
        static sdata_t myData;      //Dados do robô
        static sdata_t otherData;   //Dados recebidos de outro robô

        void Init ();
        void InitESPNow();

        void Master();
        void Slave ();
        
        void Send();
};

 /* Funções complementares para funcionabilidade da classe Now */

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif 