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

#ifndef AQUA_CONTROLLER_SETTINGSSERVICE_H
#define AQUA_CONTROLLER_SETTINGSSERVICE_H

#include <Preferences.h>

enum {
    MODE_AUTO = 1,
    MODE_ENABLE = 2,
    MODE_DISABLE = 3,
};

class SettingsService {
public:
    SettingsService();

    ~SettingsService();

    void setLightMode(int32_t mode);

    void setHeatingMode(int32_t mode);

    void setAerationMode(int32_t mode);

    void setFilteringMode(int32_t mode);

    void setWifiAPSSID(const char *ssid);

    void setWifiAPPassword(const char *password);

    void setMaintainTemperature(int32_t temperature);

    void setStartLighting(int32_t time);

    void setEndLighting(int32_t time);

    void setApiAddress(const char *address);

    void setApiToken(const char *token);

    void setApiAquariumId(int32_t id);

    int32_t getLightMode();

    int32_t getHeatingMode();

    int32_t getAerationMode();

    int32_t getFilteringMode();

    String getWifiAPSSID();

    String getWifiAPPassword();

    int32_t getMaintainTemperature();

    int32_t getStartLighting();

    int32_t getEndLighting();

    String getApiAddress();

    String getApiToken();

    int32_t getApiAquariumId();

protected:
    Preferences *_preferences;
};

#endif //AQUA_CONTROLLER_SETTINGSSERVICE_H
