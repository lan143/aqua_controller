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
#include "../AppService.h"
#include "WebServer.h"
#include "../settings/SettingsService.h"
#include "webpage.h"

WebServer::WebServer() {
    _server = new AsyncWebServer(80);
}

void WebServer::init() {
    this->getServer()->begin();

    this->getServer()->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, &processor);
        request->send(response);
    });

    this->getServer()->on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("wifiSSID", true)
                && request->hasParam("wifiPassword", true)
                && request->hasParam("apiAddress", true)
                && request->hasParam("apiToken", true)
                && request->hasParam("apiNo", true)) {
            App->getSettingsService()->setWifiAPSSID(request->getParam("wifiSSID", true)->value().c_str());
            App->getSettingsService()->setWifiAPPassword(request->getParam("wifiPassword", true)->value().c_str());
            App->getSettingsService()->setApiAddress(request->getParam("apiAddress", true)->value().c_str());
            App->getSettingsService()->setApiToken(request->getParam("apiToken", true)->value().c_str());
            App->getSettingsService()->setApiAquariumId(atoi(request->getParam("apiNo", true)->value().c_str()));

            request->send(200, "text/html", "<html><head><meta http-equiv=\"refresh\" content=\"1;URL=/\" /></head><body><p>Settings successful updated</p></body></html>");
        } else {
            request->send(416, "text/html", "Incorrect form data");
        }
    });
}
