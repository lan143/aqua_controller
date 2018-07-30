#ifndef _TIMER_H_
#define _TIMER_H_

#include <Preferences.h>
#include <NTPClient.h>

class TimerService {
public:
    TimerService(NTPClient *timeClient);

    ~TimerService();

    int32_t getStartHour();

    int32_t getEndHour();

    void setHours(int32_t start, int32_t end);

    bool checkIfEnableLight();

protected:
    Preferences *_prefs;
    NTPClient *_timeClient;
};

#endif