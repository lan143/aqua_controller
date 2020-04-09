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

#include "defines.h"
#include "SensorService.h"
#include "sensors/WaterTemperatureSensor.h"
#include "drivers/DS18B20Sensor.h"

SensorService::SensorService() {
    this->_sensors = new Sensor*[SENSORS_MAX];
}

void SensorService::init() {
    #ifdef WATER_TEMPERATURE_SENSOR_DS18B20
        this->_sensors[WATER_TEMPERATURE_SENSOR] = new WaterTemperatureSensor(new DS18B20Sensor(PIN_WATER_TEMPERATURE_SENSOR));
        this->_sensors[WATER_TEMPERATURE_SENSOR]->init();
    #endif
}

Sensor* SensorService::getSensor(Sensors index) {
    return this->_sensors[index];
}

SensorService sensorService = SensorService();