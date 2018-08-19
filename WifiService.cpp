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

#include <Preferences.h>
#include "AppService.h"
#include "WifiService.h"

WifiService::WifiService() {
}

void WifiService::init() {
    Preferences prefs;
    prefs.begin("wifi", false);

    String ssid = prefs.getString("ssid", "unknown");
    String password = prefs.getString("password", "unknown");

    if (ssid != "unknown" && password != "unknown") {
        this->startClientMode(&ssid, &password);
    } else {
        this->startAPMode();
    }

    prefs.end();
}

void WifiService::update() {
    this->checkWifiStatus();
    this->reconnectToWifiIfNeeded();
}

bool WifiService::startClientMode(String* ssid, String* password) {
    char ssid_buf[50];
    char password_buf[50];

    ssid->toCharArray(ssid_buf, 50);
    password->toCharArray(password_buf, 50);

    App->getWifi()->begin(ssid_buf, password_buf);

    App->getSerial()->println("");

    int numberOfAttempts = 0;

    while (App->getWifi()->status() != WL_CONNECTED) {
        numberOfAttempts++;

        delay(500);
        App->getSerial()->print(".");

        if (numberOfAttempts > 20) {
            break;
        }
    }

    if (App->getWifi()->status() == WL_CONNECTED) {
        App->getSerial()->println("");
        App->getSerial()->print("Connected to ");
        App->getSerial()->println(*ssid);
        App->getSerial()->print("IP address: ");
        App->getSerial()->println(App->getWifi()->localIP());

        _wifiLose = false;

        return true;
    } else {
        App->getSerial()->println("");
        App->getSerial()->print("Cant connect to access point ");
        App->getSerial()->println(*ssid);
        App->getSerial()->println("Trying later.");

        _wifiLose = true;

        return false;
    }
}

void WifiService::startAPMode() {
    App->getSerial()->println("Start in access point mode");
    App->getSerial()->print("SSID: ");
    App->getSerial()->println(_ap_ssid);
    App->getSerial()->print("Password: ");
    App->getSerial()->println(_ap_password);

    App->getWifi()->softAP(_ap_ssid, _ap_password);

    App->getSerial()->println();
    App->getSerial()->print("IP address: ");
    App->getSerial()->println(App->getWifi()->softAPIP());
}

void WifiService::checkWifiStatus()
{
    if (App->getWifi()->status() != WL_CONNECTED && !_wifiLose) {
        App->getSerial()->println("Disconnected from wifi");

        _wifiLose = true;
    } else if (WiFi.status() == WL_CONNECTED && _wifiLose) {
        App->getSerial()->println("Restored wifi connection");
        App->getSerial()->print("IP address: ");
        App->getSerial()->println(App->getWifi()->localIP());

        _wifiLose = false;
    }
}

void WifiService::reconnectToWifiIfNeeded() {
    if (_wifiLose) {
        if ((millis() - _lastReconnect) >= RECONNECT_INTERVAL) {
            App->getSerial()->println("Trying reconnect to wifi access point.");
            App->getWifi()->reconnect();
            _lastReconnect = millis();
        }
    }
}
