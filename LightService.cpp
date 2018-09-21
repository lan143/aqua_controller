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

#include "defines.h"
#include "AppService.h"
#include "LightService.h"

LightService::LightService() : RelayService(PIN_RELAY_LIGHT) {
}

void LightService::internalUpdate() {
    int32_t mode = App->getSettingsService()->getLightMode();

    if (mode == MODE_DISABLE) {
        App->getSerial()->println("Light: Manual disabled");
        this->disable();
    } else if (mode == MODE_ENABLE) {
        App->getSerial()->println("Light: Manual enabled");
        this->enable();
    } else if (mode == MODE_AUTO) {
        int32_t startTime = App->getSettingsService()->getStartLighting();
        int32_t endTime = App->getSettingsService()->getEndLighting();
        DateTime dateTime = App->getClockService()->getCurrentDateTime();
        int32_t currentTime = dateTime.hour() * 100 + dateTime.minute();

        if (startTime >= currentTime && currentTime <= endTime) {
            App->getSerial()->println("Light: Auto enabled");
            this->enable();
        } else {
            App->getSerial()->println("Light: Auto disabled");
            this->disable();
        }
    }
}
