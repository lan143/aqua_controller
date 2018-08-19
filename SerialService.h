#ifndef _SERIAL_SERVICE_H_
#define _SERIAL_SERVICE_H_

class SerialService {
public:
    SerialService(HardwareSerial* serial);

    void update();

private:
    HardwareSerial* _serial;

    String readLine();

    void resetSettings();
};

#endif