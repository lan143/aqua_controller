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

#ifndef AQUA_CONTROLLER_WEBPAGE_H
#define AQUA_CONTROLLER_WEBPAGE_H

#include "../AppService.h"

const char index_html[] PROGMEM = "<!doctype html><html lang=\"ru\"> <head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <title>Aquarium Controller</title> </head> <body><div class=\"container\"><h1>Aquarium Controller</h1><div class=\"row\"><div class=\"col-md-12\"><h3>Статистика</h3><ul><li>Дата сборки прошивки: %BUILD_TIME%</li><li>Текущее время: %TIME%</li><li>Температура воды: %MAINTAIN_TEMPERATURE%</li><li>Температура воздуха: %OUTER_TEMPERATURE%</li><li>Обогрев включен: %HEATING_STATUS%</li><li>Освещение включено: %LIGHTING_STATUS%</li><li>Аэрация включена: %AERATION_STATUS%</li><li>Фильтрация включена: %FILTERING_STATUS%</li></ul></div></div><div class=\"row\"><div class=\"col-md-12\"><h3>Настройки</h3><form method=\"POST\" action=\"/\"><div class=\"form-group\"><label>WiFi SSID</label><input name=\"wifiSSID\" type=\"text\" class=\"form-control\" placeholder=\"Укажите SSID\" value=\"%WIFI_SSID%\" /></div><div class=\"form-group\"><label>WiFi Пароль</label><input name=\"wifiPassword\" type=\"password\" class=\"form-control\" placeholder=\"Укажите пароль\" value=\"%WIFI_PASSWORD%\" /></div><div class=\"form-group\"><label>Адрес API</label><input name=\"apiAddress\" type=\"text\" class=\"form-control\" placeholder=\"Укажите адрес api\" value=\"%API_ADDRESS%\" /></div><div class=\"form-group\"><label>Токен API</label><input name=\"apiToken\" type=\"text\" class=\"form-control\" placeholder=\"Укажите токен\" value=\"%API_TOKEN%\" /></div><div class=\"form-group\"><label>Номер аквариума</label><input name=\"apiNo\" type=\"number\" class=\"form-control\" placeholder=\"Укажите номер аквариума\" value=\"%API_NO%\" /></div><div class=\"form-group\"><input type=\"submit\" class=\"btn btn-primary\" value=\"Сохранить\" /></div></form></div></div></div> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\" integrity=\"sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO\" crossorigin=\"anonymous\"> <script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\" integrity=\"sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49\" crossorigin=\"anonymous\"></script> <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\" integrity=\"sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy\" crossorigin=\"anonymous\"></script> </body></html>";

String processor(const String &var) {
    if (var == "BUILD_TIME") {
        return F(__DATE__);
    } else if (var == "TIME") {
        char str[80];
        DateTime dateTime = App->getClockService()->getCurrentDateTime();

        sprintf(str, "%02d.%02d.%d %02d:%02d:%02d", dateTime.day(), dateTime.month(), dateTime.year(), dateTime.hour(), dateTime.minute(), dateTime.second());

        return F(str);
    } else if (var == "MAINTAIN_TEMPERATURE") {
        char str[10];
        sprintf(str, "%0.2f", App->getMaintainTemperatureService()->getValue());

        return str;
    } else if (var == "OUTER_TEMPERATURE") {
        char str[10];
        sprintf(str, "%0.2f", App->getOuterTemperatureService()->getValue());

        return str;
    } else if (var == "HEATING_STATUS") {
        if (App->getHeatingService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "LIGHTING_STATUS") {
        if (App->getLightService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "AERATION_STATUS") {
        if (App->getAerationService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "FILTERING_STATUS") {
        if (App->getFilterService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "API_ADDRESS") {
        return App->getSettingsService()->getApiAddress();
    } else if (var == "API_TOKEN") {
        return App->getSettingsService()->getApiToken();
    } else if (var == "API_NO") {
        char str[10];
        sprintf(str, "%d", App->getSettingsService()->getApiAquariumId());

        return str;
    } else if (var == "WIFI_SSID") {
        return App->getSettingsService()->getWifiAPSSID();
    } else if (var == "WIFI_PASSWORD") {
        return App->getSettingsService()->getWifiAPPassword();
    }

    return String();
}

#endif //AQUA_CONTROLLER_WEBPAGE_H
