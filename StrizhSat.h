#pragma once
#include <Arduino.h>
#include "iarduino_RTC.h"
#include "microDS18B20.h"
#include "BMP180.h"
#include <Wire.h>
#include <AT24CX.h>
#ifdef PCF_ENABLE 
#include <PCF8574.h>
#endif

class StrizhSat {
  BMP180 bmp;
  iarduino_RTC rtc;
  MicroDS18B20<0> temp;
  AT24C128 mem;
  #ifdef PCF_ENABLE 
  PCF8574 pcf;
  #endif
  float curTemp = -1;
  uint32_t dsTimer = 0;
  bool bmpStatus = false, tempStatus = false;
  public:
    StrizhSat() { }
    void init();
    void tick();
    void setCurrentTime();
    float getTemperature();
    int32_t getPressure();
    uint32_t getUnixTime();
    float getAltitude();
    float getBmpTemperature();
    uint8_t getTimeSeconds();
    uint8_t getTimeMinutes();
    uint8_t getTimeHours();
    void ATWrite(uint32_t address, uint8_t* data, uint32_t length);
    void ATRead(uint32_t address, uint8_t* data, uint32_t length);
    template <typename T>
    void ATWrite(uint32_t address, T data);
    template <typename T>
    void ATRead(uint32_t address, T data);
    void ATClear();
    #ifdef PCF_ENABLE
    bool readKey1() { return pcf.digitalRead(0); }
    bool readKey2() { return pcf.digitalRead(1); }
    void setLed1(bool value) { pcf.digitalWrite(2, value); }
    void setLed2(bool value) { pcf.digitalWrite(3, value); }
    void PCFDigitialWrite(uint8_t pin, uint8_t value) { pcf.digitalWrite(pin, value); }
    bool PCFDigitialRead(uint8_t pin) { return pcf.digitalRead(pin); }
    void PCFPinMode(uint8_t pin, uint8_t mode) { return pcf.pinMode(pin, mode); }
    #endif
};
