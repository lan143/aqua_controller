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

#include "../AppService.h"
#include "SerialService.h"

SerialService::SerialService() {
}

void SerialService::update() {
    std::vector<String> line = readLine();

    if (line.size() > 0) {
        String command = *line.begin();

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
}

void SerialService::resetSettings() {
    App->getSerial()->println("Start reset settings");

    App->getSettingsService()->setWifiAPSSID("unknown");
    App->getSettingsService()->setWifiAPPassword("unknown");

    App->getSerial()->println("Complete. Restart...");

    delay(2000);
    ESP.restart();
}

void SerialService::setSettings(std::vector<String> data) {
    App->getSerial()->println("Start set settings");

    if (data.size() == 3) {
        if (data[1] == "ssid") {
            App->getSettingsService()->setWifiAPSSID(data[2].c_str());
        } else if (data[1] == "password") {
            App->getSettingsService()->setWifiAPPassword(data[2].c_str());
        } else {
            App->getSerial()->println("Unknown command argument.");
        }

        App->getSerial()->println("Complete.");
    } else {
        App->getSerial()->println("Incorrect command arguments count.");
    }
}

std::vector<String> SerialService::readLine() {
    std::vector<String> out;
    String inString = "";

    while (App->getSerial()->available() > 0) {
        char inChar = App->getSerial()->read();

        if (inChar == '\n') {
            out.push_back(inString);
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
