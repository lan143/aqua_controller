#ifndef _TIMER_H_
#define _TIMER_H_

#include <Preferences.h>
#include "ClockService.h"

class TimerService {
public:
    TimerService(NTPClient* ntpClient);
    ~TimerService();

    int32_t getStartHour();
    int32_t getEndHour();

    void setHours(int32_t start, int32_t end);

    bool checkIfEnableLight();

    void update();

protected:
    Preferences* _preferences;
    ClockService* _clockService;
};

#endif
