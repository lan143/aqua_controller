#include <LiquidCrystal.h>

#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "TimerService.h"
#include "RestServer.h"
#include "WifiService.h"

#define DEBUG_NTPClient true

#define DHT_PIN 26
#define RELAY_ONE_PIN 27

DHT dht(DHT_PIN, DHT22);
WiFiUDP ntpUDP;
NTPClient* timeClient;
TimerService* timerService;
RestServer* restServer;
WifiService* wifiService;

void setup(void)
{
    Serial.begin(115200);

    dht.begin();

    wifiService = new WifiService(&WiFi, &Serial);
    wifiService->init();

    timeClient = new NTPClient(ntpUDP);
    timeClient->setTimeOffset(3 * 3600);
    timeClient->begin();

    timerService = new TimerService(timeClient);

    restServer = new RestServer(&Serial, &dht, timerService);
    restServer->init();

    pinMode(27, OUTPUT);
}

void loop(void)
{
    timeClient->update();
    wifiService->update();

    if (timerService->checkIfEnableLight()) {
        Serial.println("Enabled");
        digitalWrite(RELAY_ONE_PIN, LOW);
    } else {
        Serial.println("Disabled");
        digitalWrite(RELAY_ONE_PIN, HIGH);
    }

    Serial.println(timeClient->getFormattedTime());

    delay(1000);
}
