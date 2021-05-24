#ifndef now_h
#define now_h

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

class Now {
    protected:
        uint8_t _gpios[];
        uint8_t _macSlaves[][6];
    public:
        typedef struct _data {
                float time;
            } _data;
        Now (uint8_t gpios[], uint8_t macSlaves[][6]);
        void Master();
        void Slave ();
        
        void InitESPNow();
        void Send();
        void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int data_len);
        void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif 