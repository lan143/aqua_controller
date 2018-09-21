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
#include <HTTPClient.h>
#include "AppService.h"
#include "ApiService.h"

ApiService::ApiService() {}

void ApiService::update() {
    if (this->_lastUpdateTime == 0 || millis() - this->_lastUpdateTime > 300000) {
        this->internalUpdate();
        this->_lastUpdateTime = millis();
    }
}

void ApiService::internalUpdate() {
    this->sendStats();
    this->updateSettings();
}

void ApiService::updateSettings() {
    HTTPClient client;

    char url[1000];

    sprintf(url, "%s/aquariums/%d/settings", App->getSettingsService()->getApiAddress(),
            App->getSettingsService()->getApiAquariumId());

    client.begin((String) url);
    client.addHeader("Content-Type", "application/json");
    client.addHeader("Authorization", "Bearer " + App->getSettingsService()->getApiToken());

    int httpResponseCode = client.GET();

    if (httpResponseCode == 200) {
        String response = client.getString();

        StaticJsonBuffer<2000> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(response);

        App->getSettingsService()->setLightMode(root["lighting"]);
        App->getSettingsService()->setHeatingMode(root["heating"]);
        App->getSettingsService()->setAerationMode(root["aeration"]);
        App->getSettingsService()->setFilteringMode(root["filtering"]);
        App->getSettingsService()->setStartLighting(root["startLighting"]);
        App->getSettingsService()->setEndLighting(root["endLighting"]);
        App->getSettingsService()->setMaintainTemperature(root["maintainTemperature"]);
    }

    client.end();
}

void ApiService::sendStats() {
    HTTPClient client;

    char url[1000];

    sprintf(url, "%s/aquariums/%d/stats", App->getSettingsService()->getApiAddress(),
            App->getSettingsService()->getApiAquariumId());

    char data[1000];
    sprintf(
            data,
            "{\"heating\":\"%d\", \"aeration\": \"%d\", \"lighting\": \"%d\", \"filtering\": \"%d\", \"maintainTemperature\": \"%f\", \"outerTemperature\": \"%f\"}",
            (int) App->getHeatingService()->isEnabled(),
            (int) App->getAerationService()->isEnabled(),
            (int) App->getLightService()->isEnabled(),
            (int) App->getFilterService()->isEnabled(),
            App->getMaintainTemperatureService()->getValue(),
            App->getOuterTemperatureService()->getValue()
    );

    client.begin((String) url);
    client.addHeader("Content-Type", "application/json");
    client.addHeader("Authorization", "Bearer " + App->getSettingsService()->getApiToken());

    client.POST((String) data);

    client.end();
}
