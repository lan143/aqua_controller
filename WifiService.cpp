#include <Preferences.h>
#include "WifiService.h"

WifiService::WifiService(WiFiClass* wifi, HardwareSerial* serial) {
    _wifi = wifi;
    _serial = serial;
}

void WifiService::init() {
    Preferences prefs;
    prefs.begin("wifi", true);

    String ssid = prefs.getString("ssid", "unknown");
    String password = prefs.getString("password", "unknown");

    prefs.end();

    if (ssid != "unknown" && password != "unknown") {
        startClientMode(&ssid, &password);
    } else {
        startAPMode();
    }
}

void WifiService::update() {
    checkWifiStatus();
}

bool WifiService::startClientMode(String* ssid, String* password) {
    char ssid_buf[50];
    char password_buf[50];

    ssid->toCharArray(ssid_buf, 50);
    password->toCharArray(password_buf, 50);

    _wifi->begin(ssid_buf, password_buf);

    _serial->println("");

    int numberOfAttempts = 0;

    while (_wifi->status() != WL_CONNECTED) {
        numberOfAttempts++;

        delay(500);
        _serial->print(".");

        if (numberOfAttempts > 20) {
            break;
        }
    }

    if (_wifi->status() == WL_CONNECTED) {
        _serial->println("");
        _serial->print("Connected to ");
        _serial->println(*ssid);
        _serial->print("IP address: ");
        _serial->println(WiFi.localIP());

        _wifiLose = false;

        return true;
    } else {
        _serial->println("");
        _serial->print("Cant connect to access point ");
        _serial->println(*ssid);
        _serial->println("Trying later.");

        _wifiLose = true;

        return false;
    }
}

void WifiService::startAPMode() {
    _serial->println("Start in access point mode");
    _serial->print("SSID: ");
    _serial->println(_ap_ssid);
    _serial->print("Password: ");
    _serial->println(_ap_password);

    _wifi->softAP(_ap_ssid, _ap_password);

    _serial->println();
    _serial->print("IP address: ");
    _serial->println(_wifi->softAPIP());
}

void WifiService::checkWifiStatus()
{
    if (_wifi->status() != WL_CONNECTED && !_wifiLose) {
        _serial->println("Disconnected from wifi");

        _wifiLose = true;
    } else if (WiFi.status() == WL_CONNECTED && _wifiLose) {
        _serial->println("Restored wifi connection");

        _wifiLose = false;
    }
}