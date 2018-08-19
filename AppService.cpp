#include "AppService.h"

AppService::AppService(HardwareSerial* serial, WiFiClass* wifi) {
    _serial = serial;
    _wifi = wifi;
}

void AppService::init() {
    _serial->begin(115200);

    _serialService = new SerialService(_serial);

    _dht = new DHT(DHT_PIN, DHT22);
    _dht->begin();

    _wifiService = new WifiService(_wifi, _serial);
    _wifiService->init();

    _ntpUDP = new WiFiUDP();

    _ntpClient = new NTPClient(*_ntpUDP);
    _ntpClient->setTimeOffset(3 * 3600);
    _ntpClient->begin();

    _timerService = new TimerService(_ntpClient);

    _restServer = new RestServer(_serial, _dht, _timerService);
    _restServer->init();

    pinMode(RELAY_ONE_PIN, OUTPUT);
}

void AppService::update() {
    _serialService->update();
    _wifiService->update();
    _timerService->update();

    if (_timerService->checkIfEnableLight()) {
        _serial->println("Enabled");
        digitalWrite(RELAY_ONE_PIN, LOW);
    } else {
        _serial->println("Disabled");
        digitalWrite(RELAY_ONE_PIN, HIGH);
    }

    delay(1000);
}