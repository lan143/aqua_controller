/**
 * MIT License
 *
 * Copyright (c) 2020 Kravchenko Artyom
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

#include "DS18B20Driver.h"
#include "log/Log.h"

DS18B20Driver::DS18B20Driver(int pin) : TemperatureDriver(pin) {
    Log.trace("DS18B20Driver: init.\r\n");
    OneWire* wire = new OneWire(this->_pin);
    this->_sensors = new DallasTemperature(wire);
    this->_sensors->begin();
    this->_sensors->begin();

    if (this->_sensors->getDeviceCount() > 0) {
        Log.trace("DS18B20Driver: Found %d sensors.\r\n", this->_sensors->getDeviceCount());
        Log.trace("DS18B20Driver: Parasite power is %s\r\n", this->_sensors->isParasitePowerMode() ? "ON" : "OFF");
        this->_ready = true;
    } else {
        Log.error("DS18B20Driver: sensors not found\r\n");
        this->_ready = false;
    }
}

float DS18B20Driver::getTemperature() {
    if (!this->_ready) {
        return -40.0f;
    }

    Log.trace("DS18B20Driver: start get temperature.\r\n");
    Log.trace("DS18B20Driver: requestTemperatures.\r\n");
    this->_sensors->requestTemperatures();
    
    int countCorrectDevices = 0;
    float value = 0;
    Log.trace("DS18B20Driver: get temp from sensors..\r\n");

    for (int i = 0; i < this->_sensors->getDeviceCount(); i++) {
        float temp = this->_sensors->getTempCByIndex(i);
        Log.trace("DS18B20Driver: sensor #%d: %F\r\n", i, temp);

        if (temp == -85) {
            continue;
        }

        value += this->_sensors->getTempCByIndex(i);
        countCorrectDevices++;
    }

    if (countCorrectDevices > 0) {
        Log.trace("DS18B20Driver: Calculate avg value\r\n");
        value /= countCorrectDevices;
    } else {
        return -40.0f;
    }

    Log.trace("DS18B20Driver: Complete!\r\n");
    Log.trace("DS18B20Driver: Temp: %F\r\n", value);

    return value;
}