#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include <WiFi.h>

class WifiService {
public:
    WifiService(WiFiClass* wifi, HardwareSerial* serial);

    void init();

    void update();

protected:
    WiFiClass* _wifi;
    HardwareSerial* _serial;

    const char* _ap_ssid = "lan143-aqua";
    const char* _ap_password = "funfefsdjk";

    bool _wifiLose;

    bool startClientMode(String* ssid, String* password);
    void startAPMode();
    void checkWifiStatus();
};

#endif