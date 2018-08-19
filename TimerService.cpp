#include "TimerService.h"

TimerService::TimerService(NTPClient* ntpClient) {
    this->_preferences = new Preferences;
    this->_preferences->begin("timer", false);

    this->_clockService = new ClockService(&Serial, ntpClient);
    this->_clockService->init();
}

TimerService::~TimerService() {
    this->_preferences->end();
}

void TimerService::update() {
    this->_clockService->update();
}

int32_t TimerService::getStartHour() {
    return this->_preferences->getInt("start", 9);
}

int32_t TimerService::getEndHour() {
    return this->_preferences->getInt("end", 21);
}

void TimerService::setHours(int32_t start, int32_t end) {
    this->_preferences->putInt("start", start);
    this->_preferences->putInt("end", end);
}

bool TimerService::checkIfEnableLight() {
    return this->_clockService->getHours() >= this->getStartHour() && this->_clockService->getHours() < this->getEndHour();
}