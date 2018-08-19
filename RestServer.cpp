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

#include <ArduinoJson.h>
#include <DHT.h>
#include <Preferences.h>
#include "AppService.h"
#include "RestServer.h"
#include "TimerService.h"

RestServer::RestServer() {
    _server = new AsyncWebServer(80);
}

void RestServer::init() {
    this->getServer()->begin();

    this->getServer()->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello World");
    });

    this->getServer()->on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request) {
        App->getSerial()->println("GET: /temperature");

        float t = App->getDHT()->readTemperature();

        if (isnan(t)) {
            request->send(500, "application/json", "{\"message\":\"Failed to get temperature from sensor\"}");
        } else {
            char result[100];
            sprintf(result, "{\"value\": \"%.2f\"}", t);
            request->send(200, "application/json", result);
        }
    });

    this->getServer()->on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request) {
        App->getSerial()->println("GET: /humidity");

        float h = App->getDHT()->readHumidity();

        if (isnan(h)) {
            request->send(500, "application/json", "{\"message\":\"Failed to get humidity from sensor\"}");
        } else {
            char result[100];
            sprintf(result, "{\"value\": \"%.2f\"}", h);
            request->send(200, "application/json", result);
        }
    });

    this->getServer()->on("/settings", HTTP_POST, [this](AsyncWebServerRequest *request) {
        App->getSerial()->println("POST: /settings");

        AsyncWebParameter* body = request->getParam("body", true);

        StaticJsonBuffer<1000> JSONBuffer;
        JsonObject& jsonBody = JSONBuffer.parseObject(body->value().c_str());

        if (!jsonBody.success()) {
            request->send(422, "application/json", "{\"message\":\"Failed to parse json\"}");
            return;
        }

        Preferences prefs;
        prefs.begin("wifi", false);

        prefs.putString("ssid", (const char*)jsonBody["ssid"]);
        prefs.putString("password", (const char*)jsonBody["password"]);

        prefs.end();

        request->send(200, "application/json", "{}");

        delay(2000);
        ESP.restart();
    });

    this->getServer()->on("/settings/timer", HTTP_POST, [this](AsyncWebServerRequest *request) {
        App->getSerial()->println("POST: /settings/timer");

        AsyncWebParameter* body = request->getParam("body", true);

        StaticJsonBuffer<1000> JSONBuffer;
        JsonObject& jsonBody = JSONBuffer.parseObject(body->value().c_str());

        if (!jsonBody.success()) {
            request->send(422, "application/json", "{\"message\":\"Failed to parse json\"}");
            return;
        }

        App->getTimerService()->setHours(jsonBody["start"], jsonBody["end"]);

        request->send(200, "application/json", "{}");

        delay(2000);
        ESP.restart();
    });
}
