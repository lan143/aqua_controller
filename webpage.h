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

#include "AppService.h"

const char index_html[] PROGMEM = "<!doctype html><html lang=\"ru\"> <head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <title>Aquarium Controller</title> </head> <body><div class=\"container\"><h1>Aquarium Controller</h1><div class=\"row\"><div class=\"col-md-12\"><h3>Статистика</h3><ul><li>Дата сборки прошивки: __BUILD_TIME__</li><li>Текущее время: __TIME__</li><li>Температура воды: __MAINTAIN_TEMPERATURE__</li><li>Температура воздуха: __OUTER_TEMPERATURE__</li><li>Обогрев включен: __HEATING_STATUS__</li><li>Освещение включено: __LIGHTING_STATUS__</li><li>Аэрация включена: __AERATION_STATUS__</li><li>Фильтрация включена: __FILTERING_STATUS__</li></ul></div></div><div class=\"row\"><div class=\"col-md-12\"><h3>Настройки</h3><form method=\"POST\" action=\"/\"><div class=\"form-group\"><label>WiFi SSID</label><input name=\"wifiSSID\" type=\"text\" class=\"form-control\" placeholder=\"Укажите SSID\" value=\"__WIFI_SSID__\" /></div><div class=\"form-group\"><label>WiFi Пароль</label><input name=\"wifiPassword\" type=\"password\" class=\"form-control\" placeholder=\"Укажите пароль\" value=\"__WIFI_PASSWORD__\" /></div><div class=\"form-group\"><label>Адрес API</label><input name=\"apiAddress\" type=\"text\" class=\"form-control\" placeholder=\"Укажите адрес api\" value=\"__API_ADDRESS__\" /></div><div class=\"form-group\"><label>Токен API</label><input name=\"apiToken\" type=\"number\" class=\"form-control\" placeholder=\"Укажите токен\" value=\"__API_TOKEN__\" /></div><div class=\"form-group\"><label>Номер аквариума</label><input name=\"apiNo\" type=\"number\" class=\"form-control\" placeholder=\"Укажите номер аквариума\" value=\"__API_NO__\" /></div><div class=\"form-group\"><input type=\"submit\" class=\"btn btn-primary\" value=\"Сохранить\" /></div></form></div></div></div> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\" integrity=\"sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO\" crossorigin=\"anonymous\"> <script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\" integrity=\"sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49\" crossorigin=\"anonymous\"></script> <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\" integrity=\"sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy\" crossorigin=\"anonymous\"></script> </body></html>";

String processor(const String &var) {
    if (var == "__BUILD_TIME__") {
        return F(__DATE__);
    } else if (var == "__TIME__") {
        char str[80];
        DateTime dateTime = App->getClockService()->getCurrentDateTime();

        sprintf(str, "%d.%d.%d %d.%d.%d", dateTime.day(), dateTime.month(), dateTime.year(), dateTime.hour(), dateTime.minute(), dateTime.second());

        return F(str);
    } else if (var == "__MAINTAIN_TEMPERATURE__") {
        char str[10];
        sprintf(str, "%f.2", App->getMaintainTemperatureService()->getValue());

        return str;
    } else if (var == "__OUTER_TEMPERATURE__") {
        char str[10];
        sprintf(str, "%f.2", App->getOuterTemperatureService()->getValue());

        return str;
    } else if (var == "__HEATING_STATUS__") {
        if (App->getHeatingService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "__LIGHTING_STATUS__") {
        if (App->getLightService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "__AERATION_STATUS__") {
        if (App->getAerationService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "__FILTERING_STATUS__") {
        if (App->getFilterService()->isEnabled()) {
            return "Yes";
        } else {
            return "No";
        }
    } else if (var == "__API_ADDRESS__") {
        return App->getSettingsService()->getApiAddress();
    } else if (var == "__API_TOKEN__") {
        return App->getSettingsService()->getApiToken();
    } else if (var == "__API_NO__") {
        char str[10];
        sprintf(str, "%d", App->getSettingsService()->getApiAquariumId());

        return str;
    } else if (var == "__WIFI_SSID__") {
        return App->getSettingsService()->getWifiAPSSID();
    } else if (var == "__WIFI_PASSWORD__") {
        return App->getSettingsService()->getWifiAPPassword();
    }

    return String();
}

#endif //AQUA_CONTROLLER_WEBPAGE_H
