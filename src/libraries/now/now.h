#ifndef now_h
#define now_h

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

//Struct que definira todos os dados que serem enviados e recebidos
typedef struct Data {
    int id;
    double time;
    int status; //Ira percorrer ou esperar
    bool position; //Esta posicionado ou nao
    bool ready; //Posicionamento do robo na colheitadeira
} sdata_t;

class Now {
    protected:
        //Pinos e enderecos das esps que seram comunicadas
        uint8_t _gpios[];
        uint8_t _macSlaves[][6];
    public:
        Now (uint8_t gpios[], uint8_t macSlaves[][6], int);
        
        sdata_t myData;
        
        myData.id = 0;
        myData.time = 0;
        myData.status = 0;
        myData.position = false;
        myData.ready = false;
        
        sdata_t otherData = {
            id = 0;
            time = 0;
            status = 0;
            position = false;
            ready = false;
        };

        //Funcoes da biblioteca esp_now
        void Master();
        void Slave ();
        
        void InitESPNow();
        void Send();
        
        static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len);
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif 