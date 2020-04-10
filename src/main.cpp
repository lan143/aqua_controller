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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include <Arduino.h>
#include "log/Log.h"
#include "services/SensorService.h"
#include "services/HeatingService.h"
#include "defines.h"
#include "drivers/PWMRelayDriver.h"

void setup() {
  delay(3000);

  Serial.begin(115200);

  while (!Serial) {}

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.trace("Serial inited. Start init other...\r\n");

  sensorService.init();

  #ifdef HEATING_DRIVER_PWM_RELAY
    HeatingService* heatingService = new HeatingService(new PWMRelayDriver(PIN_HEATING_RELAY));
  #endif
  heatingService->init();

  Log.trace("Init completed. Running...\r\n");
}

void loop() {
}
