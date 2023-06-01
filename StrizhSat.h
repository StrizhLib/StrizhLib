#pragma once
#include <Arduino.h>
#include "iarduino_RTC.h"
#include "microDS18B20.h"
#include "BMP180.h"
#include <Wire.h>

class StrizhSat {
  BMP180 bmp;
  iarduino_RTC rtc;
  MicroDS18B20<0> temp;
  float curTemp = -1;
  uint32_t rtcTimer = 0;
  uint32_t dsTimer = 0;
  bool bmpStatus = false, tempStatus = false;
  public:
    StrizhSat() { }
    void init();
    void tick();
    int32_t getPressure();
    float getAltitude();
    float getBmpTemperature();
    uint32_t getUnixTime();
    iarduino_RTC* getTime();
    float getTemperature();
};
