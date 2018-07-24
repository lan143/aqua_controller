#include <ArduinoJson.h>
#include <DHT.h>
#include <Preferences.h>
#include "RestServer.h"
#include "TimerService.h"

RestServer::RestServer(HardwareSerial* serial, DHT* dht, TimerService* timerService) {
    _server = new AsyncWebServer(80);
    _serial = serial;
    _dht = dht;
    _timerService = timerService;
}

void RestServer::init() {
    _server->begin();

    _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello World");
    });

    _server->on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->_serial->println("GET: /temperature");

        float t = this->_dht->readTemperature();

        if (isnan(t)) {
            request->send(500, "application/json", "{\"message\":\"Failed to get temperature from sensor\"}");
        } else {
            char result[100];
            sprintf(result, "{\"value\": \"%.2f\"}", t);
            request->send(200, "application/json", result);
        }
    });

    _server->on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->_serial->println("GET: /humidity");

        float h = this->_dht->readHumidity();

        if (isnan(h)) {
            request->send(500, "application/json", "{\"message\":\"Failed to get humidity from sensor\"}");
        } else {
            char result[100];
            sprintf(result, "{\"value\": \"%.2f\"}", h);
            request->send(200, "application/json", result);
        }
    });

    _server->on("/settings", HTTP_POST, [this](AsyncWebServerRequest *request) {
        this->_serial->println("POST: /settings");

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

    _server->on("/settings/timer", HTTP_POST, [this](AsyncWebServerRequest *request) {
        this->_serial->println("POST: /settings/timer");

        AsyncWebParameter* body = request->getParam("body", true);

        StaticJsonBuffer<1000> JSONBuffer;
        JsonObject& jsonBody = JSONBuffer.parseObject(body->value().c_str());

        if (!jsonBody.success()) {
            request->send(422, "application/json", "{\"message\":\"Failed to parse json\"}");
            return;
        }

        this->_timerService->setHours(jsonBody["start"], jsonBody["end"]);

        request->send(200, "application/json", "{}");

        delay(2000);
        ESP.restart();
    });
}
