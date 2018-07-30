#include "AppService.h"

AppService::AppService(HardwareSerial* serial, WiFiClass* wifi) {
    _serial = serial;
    _wifi = wifi;
}

void AppService::init() {
    _serial->begin(115200);

    _dht = new DHT(DHT_PIN, DHT22);
    _dht->begin();

    _wifiService = new WifiService(_wifi, _serial);
    _wifiService->init();

    _ntpUDP = new WiFiUDP();

    _timeClient = new NTPClient(*_ntpUDP);
    _timeClient->setTimeOffset(3 * 3600);
    _timeClient->begin();

    _timerService = new TimerService(_timeClient);

    _restServer = new RestServer(_serial, _dht, _timerService);
    _restServer->init();

    pinMode(RELAY_ONE_PIN, OUTPUT);
}

void AppService::update() {
    _timeClient->update();
    _wifiService->update();

    if (_timerService->checkIfEnableLight()) {
        _serial->println("Enabled");
        digitalWrite(RELAY_ONE_PIN, LOW);
    } else {
        _serial->println("Disabled");
        digitalWrite(RELAY_ONE_PIN, HIGH);
    }

    _serial->println(_timeClient->getFormattedTime());

    delay(1000);
}