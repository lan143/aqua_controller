/**
 * MIT License
 *
 * Copyright (c) 2018 Kravchenko Artyom
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _APP_SERVICE_H_
#define _APP_SERVICE_H_

#include <DHT.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "TimerService.h"
#include "RestServer.h"
#include "WifiService.h"
#include "SerialService.h"
#include "NTPClient.h"

#define DHT_PIN 26
#define RELAY_ONE_PIN 27

#define App AppService::getInstance()

class AppService {
public:
    static AppService *getInstance() {
        if (!_instance) {
            _instance = new AppService();
        }

        return _instance;
    }

    void init();

    void update();

    DHT *getDHT() { return this->_dht; };

    WiFiUDP *getNtpUDP() { return this->_ntpUDP; };

    NTPClient *getNtpClient() { return this->_ntpClient; };

    TimerService *getTimerService() { return this->_timerService; };

    RestServer *getRestServer() { return this->_restServer; };

    WifiService *getWifiService() { return this->_wifiService; };

    SerialService *getSerialService() { return this->_serialService; };

    HardwareSerial *getSerial() { return this->_serial; };

    WiFiClass *getWifi() { return this->_wifi; };

    ClockService *getClockService() { return this->_clockService; };

private:
    static AppService *_instance;

    AppService() {}

    AppService(const AppService &);

    AppService &operator=(AppService &);

    HardwareSerial *_serial;
    WiFiClass *_wifi;

    DHT *_dht;
    WiFiUDP *_ntpUDP;
    NTPClient *_ntpClient;
    TimerService *_timerService;
    RestServer *_restServer;
    WifiService *_wifiService;
    SerialService *_serialService;
    ClockService *_clockService;
};

#endif
