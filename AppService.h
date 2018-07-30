#ifndef _APP_SERVICE_H_
#define _APP_SERVICE_H_

#include <DHT.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "TimerService.h"
#include "RestServer.h"
#include "WifiService.h"

#define DHT_PIN 26
#define RELAY_ONE_PIN 27

class AppService {
public:
    AppService(HardwareSerial* serial, WiFiClass* wifi);

    void init();

    void update();

protected:
    HardwareSerial* _serial;
    WiFiClass* _wifi;

    DHT* _dht;
    WiFiUDP* _ntpUDP;
    NTPClient* _timeClient;
    TimerService* _timerService;
    RestServer* _restServer;
    WifiService* _wifiService;
};

#endif