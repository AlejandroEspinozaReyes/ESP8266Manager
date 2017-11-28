#include "Arduino.h"
#include "ESP8266Manager.h"
#include "SoftwareSerial.h"

ESP8266Manager::ESP8266Manager(int baudRate, int rxPin, int txPin) : _esp8266(rxPin, txPin) {
    _esp8266.begin(baudRate);
}

String ESP8266Manager::readESP8266() {
    String espMessae = "";

    if (_esp8266.available()) {
        while (_esp8266.available()) {
            espMessae += _esp8266.readString();
        }

        Serial.print("ESP MESSAGE:-");
        Serial.print(espMessae);
        Serial.println("-");   
    }

    return espMessae;
}

String ESP8266Manager::writeESP8266(String command, int timeout) {
    Serial.print("COMMAND:-");
    Serial.print(command);
    Serial.println("-");

    String response = "";
    _esp8266.print(command);
    long int time = 0;
    while (!findText("OK", response) &&
            !findText("ERROR", response) &&
            time < timeout) {
        while (_esp8266.available() > 0) {
            response += _esp8266.readString(); // Storing the response from the ESP8266
        }
        time += 1;
        delay(1);
    }

    Serial.print("RESPONSE:-");
    Serial.print(response);
    Serial.println("-");

    return response;
}

boolean ESP8266Manager::findText(String subStr, String str) {
  int foundpos = -1;

  if (str.length() < 1 || subStr.length() < 1 || str.length() < subStr.length()) {
    return false;
  }

  int index = str.indexOf(subStr.charAt(0));
  
  if (index < 0) {
    return false;
  }

  for (int i = index; i <= str.length() - subStr.length(); i++) {
    if (str.substring(i,subStr.length()+i) == subStr) {
      foundpos = i;
    }
  }

  return foundpos >= 0;
}