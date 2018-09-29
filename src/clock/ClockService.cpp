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

#include "../AppService.h"
#include "ClockService.h"

ClockService::ClockService() {
    this->_rtc = new RTC_DS3231();
}

void ClockService::init() {
    this->getRtc()->begin();

    Wire.beginTransmission(DS3231_ADDRESS);
    byte error = Wire.endTransmission();

    if (error == 0) {
        this->_rtcInited = true;

        App->getSerial()->println("Found RTC module");

        if (this->getRtc()->lostPower()) {
            App->getSerial()->println("RTC module lost power, lets set the time!");
            this->getRtc()->adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
    } else {
        this->_rtcInited = false;

        App->getSerial()->println("Couldn't find RTC module. The clock will work on the controller's internal timer.");
    }
}

void ClockService::update() {
    if (App->getNtpClient()->update() && this->_rtcInited) {
        this->getRtc()->adjust(DateTime(App->getNtpClient()->getEpochTime()));
    }

    if (this->_lastDisplayTime == 0 || millis() - this->_lastDisplayTime >= 1000) {
        DateTime now = this->getCurrentDateTime();

        App->getSerial()->print(now.year(), DEC);
        App->getSerial()->print('/');
        App->getSerial()->print(now.month(), DEC);
        App->getSerial()->print('/');
        App->getSerial()->print(now.day(), DEC);
        App->getSerial()->print(" ");
        App->getSerial()->print(now.hour(), DEC);
        App->getSerial()->print(':');
        App->getSerial()->print(now.minute(), DEC);
        App->getSerial()->print(':');
        App->getSerial()->print(now.second(), DEC);
        App->getSerial()->println();

        this->_lastDisplayTime = millis();
    }
}

DateTime ClockService::getCurrentDateTime() {
    if (this->_rtcInited) {
        return this->getRtc()->now();
    } else {
        return DateTime(App->getNtpClient()->getEpochTime());
    }
}
