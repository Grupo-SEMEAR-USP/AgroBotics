#ifndef now_h
#define now_h

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

//Struct que definira todos os dados que serem enviados e recebidos
typedef struct Data {
    int id = 0;
    double time = 0;
    int status = 0; //Ira percorrer ou esperar
    bool position = false; //Esta posicionado ou nao
    bool ready = false; //Posicionamento do robo na colheitadeira
} sdata_t;

class Now {
    protected:
        //Pinos e enderecos das esps que seram comunicadas
        uint8_t _gpios[];
        uint8_t _macSlaves[][6];
    public:
        Now (uint8_t gpios[], uint8_t macSlaves[][6], int);
        
        sdata_t myData;
        sdata_t otherData;

        //Funcoes da biblioteca esp_now
        void Master();
        void Slave ();
        
        void InitESPNow();
        void Send();
};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif 