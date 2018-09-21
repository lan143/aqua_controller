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

#include "SettingsService.h"

SettingsService::SettingsService() {
    this->_preferences = new Preferences;
    this->_preferences->begin("settings", false);
}

SettingsService::~SettingsService() {
    this->_preferences->end();
}

void SettingsService::setAerationMode(int32_t mode) {
    this->_preferences->putInt("aerationMode", mode);
}

void SettingsService::setFilteringMode(int32_t mode) {
    this->_preferences->putInt("filteringMode", mode);
}

void SettingsService::setHeatingMode(int32_t mode) {
    this->_preferences->putInt("heatingMode", mode);
}

void SettingsService::setLightMode(int32_t mode) {
    this->_preferences->putInt("lightMode", mode);
}

void SettingsService::setWifiAPSSID(const char *ssid) {
    this->_preferences->putString("wifiSSID", ssid);
}

void SettingsService::setWifiAPPassword(const char *password) {
    this->_preferences->putString("wifiPassword", password);
}

void SettingsService::setMaintainTemperature(int32_t temperature) {
    this->_preferences->putInt("maintainTemperature", temperature);
}

void SettingsService::setStartLighting(int32_t time) {
    this->_preferences->putInt("startLighting", time);
}

void SettingsService::setEndLighting(int32_t time) {
    this->_preferences->putInt("endLighting", time);
}

void SettingsService::setApiAddress(const char *address) {
    this->_preferences->putString("apiAddress", address);
}

void SettingsService::setApiToken(const char *token) {
    this->_preferences->putString("apiToken", token);
}

void SettingsService::setApiAquariumId(int32_t id) {
    this->_preferences->putInt("apiAquariumId", id);
}

int32_t SettingsService::getAerationMode() {
    return this->_preferences->getInt("aerationMode", MODE_AUTO);
}

int32_t SettingsService::getLightMode() {
    return this->_preferences->getInt("lightMode", MODE_AUTO);
}

int32_t SettingsService::getHeatingMode() {
    return this->_preferences->getInt("heatingMode", MODE_AUTO);
}

int32_t SettingsService::getFilteringMode() {
    return this->_preferences->getInt("filteringMode", MODE_AUTO);
}

String SettingsService::getWifiAPSSID() {
    return this->_preferences->getString("wifiSSID", "unknown");
}

String SettingsService::getWifiAPPassword() {
    return this->_preferences->getString("wifiPassword", "unknown");
}

int32_t SettingsService::getMaintainTemperature() {
    return this->_preferences->getInt("maintainTemperature", 25);
}

int32_t SettingsService::getStartLighting() {
    return this->_preferences->getInt("startLighting", 900);
}

int32_t SettingsService::getEndLighting() {
    return this->_preferences->getInt("endLighting", 2100);
}

String SettingsService::getApiAddress() {
    return this->_preferences->getString("apiAddress", "http://aqua.lan143.ru/api");
}

String SettingsService::getApiToken() {
    return this->_preferences->getString("apiToken");
}

int32_t SettingsService::getApiAquariumId() {
    return this->_preferences->getInt("apiAquariumId");
}