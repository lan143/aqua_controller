#include <LiquidCrystal.h>
#include "AppService.h"

AppService* appService;

void setup(void)
{
    appService = new AppService(&Serial, &WiFi);
    appService->init();
}

void loop(void)
{
    appService->update();
}
