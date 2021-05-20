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
        Now (uint8_t gpios[], uint8_t macSlaves[][6]);
        void Master();
        void Slave ();
        
        void InitESPNow();
        void Send();
};

#endif 