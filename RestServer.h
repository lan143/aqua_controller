#ifndef _RESTSERVER_H_
#define _RESTSERVER_H_

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "TimerService.h"

class RestServer {
public:
    RestServer(HardwareSerial* serial, DHT* dht, TimerService* timerService);

    void init();

protected:
    AsyncWebServer* _server;
    HardwareSerial* _serial;
    DHT* _dht;
    TimerService* _timerService;
};

#endif