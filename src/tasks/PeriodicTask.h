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

#ifndef H_PERIODIC_TASK_H
#define H_PERIODIC_TASK_H

#include "log/Log.h"

void startTaskImpl(void *pvParameters);

class PeriodicTask {
public:
    PeriodicTask(const char* taskName, int priority, int loopTime, int stackSize) {
        this->_taskName = taskName;
        this->_priority = priority;
        this->_loopTime = loopTime;
        this->_stackSize = stackSize;
    }

    void init() {
        Log.trace("Init %s task.\r\n", this->_taskName);

        portBASE_TYPE result = xTaskCreate(startTaskImpl, this->_taskName, this->_stackSize, this, 1, NULL);

        if (result == pdTRUE) {
            Log.trace("Success create task %s.\r\n", this->_taskName);
        } else if (result == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY) {
            Log.error("Cant create task %s. Could not allocate required memory.\r\n", this->_taskName);
        } else {
            Log.error("Cant create task %s.\r\n", this->_taskName);
        }
    }

    int getLoopTime() { return this->_loopTime; }

    virtual void update() = 0;

protected:
    const char* _taskName;
    int _priority;
    int _loopTime;
    int _stackSize;
};

#endif