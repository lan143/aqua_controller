#ifndef _CLOCK_SERVICE_H_
#define _CLOCK_SERVICE_H_

#include "Wire.h"
#include "RTClib.h"
#include <Udp.h>
#include "NTPClient.h"

class ClockService {
public:
    ClockService(HardwareSerial* serial, NTPClient* ntpClient);

    void init();
    void update();

    int getHours();
    DateTime getCurrentDateTime();

private:
    RTC_DS3231* _rtc;
    NTPClient *_timeClient;
    HardwareSerial* _serial;
    bool _rtcInited;

    NTPClient* _htpClient;
};

#endif
