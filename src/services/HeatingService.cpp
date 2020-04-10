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

#include "log/Log.h"
#include "HeatingService.h"
#include "SensorService.h"
#include "sensors/WaterTemperatureSensor.h"

HeatingService::HeatingService(PWMDriver* driver) : PeriodicTask("HeatingService", 2, 2000, 6000) {
    this->_driver = driver;
    double Kp = 2, Ki = 0.8, Kd = 0.5;
    this->_pid = new PID(&this->_input, &this->_output, &this->_setPoint, Kp, Ki, Kd, DIRECT);
    this->_pid->SetOutputLimits(0, 255);
	this->_pid->SetSampleTime(2000);
	this->_pid->SetMode(AUTOMATIC);
}

void HeatingService::update() {
    Log.trace("HeatingService: start update\r\n");
    float temp = ((WaterTemperatureSensor*)sensorService.getSensor(WATER_TEMPERATURE_SENSOR))->getValue();

    if (temp > -40) {
        this->_input = temp;
        Log.trace("HeatingService: current temp is %F\r\n", this->_input);
        this->_setPoint = 25; // @todo: load from EEPROM
        Log.trace("HeatingService: try PID compute\r\n");

        if (this->_pid->Compute()) {
            Log.trace("HeatingService: PID computed!\r\n");
            Log.trace("HeatingService: PWM Level: %F\r\n", this->_output);
            this->_driver->setPwm(this->_output);
        }
    } else {
        Log.error("HeatingService: got incorrect current temperature\r\n");
    }
}