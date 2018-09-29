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

#include "AppService.h"

AppService* AppService::_instance = 0;

void AppService::init() {
    _serial = &Serial;
    _serial->begin(115200);

    _settingsService = new SettingsService();

    _watchdogService = new WatchdogService();
    _watchdogService->init();

    _serialService = new SerialService();

    _wifiService = new WifiService();
    _wifiService->init();

    _ntpUDP = new WiFiUDP();

    _ntpClient = new NTPClient(*_ntpUDP);
    _ntpClient->setTimeOffset(3 * 3600);
    _ntpClient->begin();

    _clockService = new ClockService();
    _clockService->init();

    _webServer = new WebServer();
    _webServer->init();

    _lightService = new LightService();

    _heatingService = new HeatingService();

    _aerationService = new AerationService();

    _filterService = new FilterService();

    _maintainTemperatureService = new MaintainTemperatureService();

    _outerTemperatureService = new OuterTemperatureService();

    _apiService = new ApiService();
}

void AppService::update() {
    this->getWatchdogService()->update();
    this->getSerialService()->update();
    this->getWifiService()->update();
    this->getClockService()->update();
    this->getLightService()->update();
    this->getHeatingService()->update();
    this->getAerationService()->update();
    this->getFilterService()->update();
    this->getMaintainTemperatureService()->update();
    this->getOuterTemperatureService()->update();
    this->getApiService()->update();
}
