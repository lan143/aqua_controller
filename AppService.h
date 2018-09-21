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

#include <WiFi.h>
#include <WiFiUdp.h>

#include "ClockService.h"
#include "SettingsService.h"
#include "WebServer.h"
#include "WifiService.h"
#include "SerialService.h"
#include "NTPClient.h"
#include "WatchdogService.h"
#include "LightService.h"
#include "HeatingService.h"
#include "AerationService.h"
#include "FilterService.h"
#include "MaintainTemperatureService.h"
#include "OuterTemperatureService.h"
#include "ApiService.h"

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

    WiFiUDP *getNtpUDP() { return this->_ntpUDP; };

    NTPClient *getNtpClient() { return this->_ntpClient; };

    WebServer *getWebServer() { return this->_webServer; };

    WifiService *getWifiService() { return this->_wifiService; };

    SerialService *getSerialService() { return this->_serialService; };

    HardwareSerial *getSerial() { return this->_serial; };

    WiFiClass *getWifi() { return this->_wifi; };

    ClockService *getClockService() { return this->_clockService; };

    WatchdogService *getWatchdogService() { return this->_watchdogService; }

    SettingsService *getSettingsService() { return this->_settingsService; }

    LightService *getLightService() { return this->_lightService; }

    HeatingService *getHeatingService() { return this->_heatingService; }

    AerationService *getAerationService() { return this->_aerationService; }

    FilterService *getFilterService() { return this->_filterService; }

    MaintainTemperatureService *getMaintainTemperatureService() { return this->_maintainTemperatureService; }

    OuterTemperatureService *getOuterTemperatureService() { return this->_outerTemperatureService; }

    ApiService *getApiService() { return this->_apiService; }

private:
    static AppService *_instance;

    AppService() {}

    AppService(const AppService &);

    AppService &operator=(AppService &);

    HardwareSerial *_serial;
    WiFiClass *_wifi;

    WiFiUDP *_ntpUDP;
    NTPClient *_ntpClient;
    WebServer *_webServer;
    WifiService *_wifiService;
    SerialService *_serialService;
    ClockService *_clockService;
    WatchdogService *_watchdogService;
    SettingsService *_settingsService;
    LightService *_lightService;
    HeatingService *_heatingService;
    AerationService *_aerationService;
    FilterService *_filterService;
    MaintainTemperatureService *_maintainTemperatureService;
    OuterTemperatureService *_outerTemperatureService;
    ApiService *_apiService;
};

#endif
