#include <Preferences.h>
#include "SerialService.h"

SerialService::SerialService(HardwareSerial *serial) {
    _serial = serial;
}

void SerialService::update() {
    String command = readLine();

    if (command != "") {
        _serial->print("Read command: ");
        _serial->println(command);

        if (command == "reset") {
            resetSettings();
        }
    }
}

void SerialService::resetSettings() {
    _serial->println("Start reset settings");

    Preferences prefs;
    prefs.begin("wifi", false);

    prefs.putString("ssid", "unknown");
    prefs.putString("password", "unknown");

    prefs.end();

    _serial->println("Complete. Reboot...");

    delay(2000);
    ESP.restart();
}

String SerialService::readLine() {
    String inString = "";

    while (_serial->available() > 0) {
        char inChar = _serial->read();

        if (inChar == '\n') {
            return inString;
        }

        inString += inChar;
    }

    return inString;
}