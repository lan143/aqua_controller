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

#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include <WiFi.h>

#define RECONNECT_INTERVAL 120 * 1000

class WifiService {
public:
    WifiService();

    void init();

    void update();

protected:
    const char* _ap_ssid = "aqua-controller";
    const char* _ap_password = "1234567890";

    bool _wifiLose;

    bool startClientMode(String* ssid, String* password);
    void startAPMode();

    void checkWifiStatus();
    void reconnectToWifiIfNeeded();

    unsigned long _lastReconnect = 0;
};

#endif
