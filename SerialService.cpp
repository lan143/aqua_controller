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
#include "SerialService.h"

SerialService::SerialService() {
}

void SerialService::update() {
    std::vector<String> line = readLine();
    String command = (String)*line.begin();

    if (command != "") {
        App->getSerial()->print("Read command: ");
        App->getSerial()->println(command);

        if (command == "reset") {
            this->resetSettings();
        } else if (command == "set") {
            this->setSettings(line);
        } else if (command == "restart") {
            App->getSerial()->println("Restart...");

            delay(2000);
            ESP.restart();
        }
    }
}

void SerialService::resetSettings() {
    App->getSerial()->println("Start reset settings");

    Preferences prefs;
    prefs.begin("wifi", false);

    prefs.putString("ssid", "unknown");
    prefs.putString("password", "unknown");

    prefs.end();

    App->getSerial()->println("Complete. Restart...");

    delay(2000);
    ESP.restart();
}

void SerialService::setSettings(std::vector<String> data) {
    App->getSerial()->println("Start set settings");

    Preferences prefs;
    prefs.begin("wifi", false);

    if (data[1] == "ssid") {
        prefs.putString("ssid", data[2]);
    } else if (data[1] == "password") {
        prefs.putString("password", data[2]);
    }

    prefs.end();
    App->getSerial()->println("Complete.");
}

std::vector<String> SerialService::readLine() {
    std::vector<String> out;
    String inString = "";

    while (App->getSerial()->available() > 0) {
        char inChar = App->getSerial()->read();

        if (inChar == '\n') {
            return out;
        } else if (inChar == ' ') {
            out.push_back(inString);
            inString = "";
        } else {
            inString += inChar;
        }
    }

    return out;
}
