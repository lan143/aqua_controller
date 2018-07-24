#include "TimerService.h"

TimerService::TimerService(NTPClient *timeClient) {
    _prefs = new Preferences;
    _prefs->begin("timer", false);

    _timeClient = timeClient;
}

TimerService::~TimerService() {
    _prefs->end();
}

int32_t TimerService::getStartHour() {
    return _prefs->getInt("start", 9);
}

int32_t TimerService::getEndHour() {
    return _prefs->getInt("end", 21);
}

void TimerService::setHours(int32_t start, int32_t end) {
    _prefs->putInt("start", start);
    _prefs->putInt("end", end);
}

bool TimerService::checkIfEnableLight() {
    return _timeClient->getHours() >= getStartHour() && _timeClient->getHours() < getEndHour();
}