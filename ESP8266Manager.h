#ifndef ESP8266Manager_h
#define ESP8266Manager_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class ESP8266Manager {
    public:
        ESP8266Manager(int baudRate, int rxPin, int txPin);
        String readESP8266();
        String writeESP8266(String command, int timeout);
        boolean findText(String subStr, String str);
    private:
        SoftwareSerial _esp8266;
        
};

#endif