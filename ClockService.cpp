#include "ClockService.h"

ClockService::ClockService(HardwareSerial* serial, NTPClient* ntpClient) {
    this->_rtc = new RTC_DS3231();
    this->_serial = serial;
    this->_htpClient = ntpClient;
}

void ClockService::init() {
    if (_rtc->begin()) {
        this->_rtcInited = true;

        this->_serial->println("Found RTC module");
    } else {
        this->_rtcInited = false;

        this->_serial->println("Couldn't find RTC");
    }

    if (_rtc->lostPower()) {
        this->_serial->println("RTC lost power, lets set the time!");
        this->_rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void ClockService::update() {
    if (this->_htpClient->update()) {
        this->_rtc->adjust(DateTime(this->_htpClient->getEpochTime()));
    }

    DateTime now = this->getCurrentDateTime();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    delay(3000);
}

DateTime ClockService::getCurrentDateTime() {
    return this->_rtc->now();
}

int ClockService::getHours() {
    DateTime now = this->getCurrentDateTime();

    return now.hour();
}