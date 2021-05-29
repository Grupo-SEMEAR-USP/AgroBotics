#ifndef now_h
#define now_h

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

class Now {
    protected:
        //Pinos e enderecos das esps que seram comunicadas
        uint8_t _gpios[];
        uint8_t _macSlaves[][6];
    public:
        //Struct que definira todos os dados que serem enviados e recebidos
        typedef struct _data {
                float time;
            } data;
        
        Now (uint8_t gpios[], uint8_t macSlaves[][6]);
        
        //Funcoes da biblioteca esp_now
        void Master();
        void Slave ();
        
        void InitESPNow();
        void Send();
        
        static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len);
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif 