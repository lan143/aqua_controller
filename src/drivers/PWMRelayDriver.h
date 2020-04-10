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

#ifndef H_PWM_RELAY_DRIVER_H
#define H_PWM_RELAY_DRIVER_H

#include "PWMDriver.h"
#include "tasks/PeriodicTask.h"

class PWMRelayDriver : public PWMDriver, public PeriodicTask {
public:
    PWMRelayDriver(int pin, int period = 255000, bool dir = false) : PWMDriver(pin), PeriodicTask("PWMRelayDriver", 0, period / 255, 2048) {
        this->_period = period;
        this->_dir = !dir;

      	pinMode(this->_pin, OUTPUT);
        digitalWrite(this->_pin, _dir);
    }

    void update();
    void setPwm(int pwm);

private:
    bool _flag = false;
    int _period;
    bool _dir = false;
    int _activePeriod = 0;
    uint32_t _tmr = 0;
};

#endif