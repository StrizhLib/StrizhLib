#include <StrizhSat.h>

void StrizhSat::init() {
  bmpStatus = bmp.begin();
  rtc.begin();
  rtc.period(5);
  tempStatus = temp.online();
  #ifdef PCF_ENABLE 
  pcf.begin();
  pcf.pinMode(2, OUTPUT);
  pcf.pinMode(3, OUTPUT);
  #endif
  temp.requestTemp();
  dsTimer = millis();
}
void StrizhSat::tick() {
  if(millis() - dsTimer >= 1000) {
    if (temp.readTemp())
      curTemp = temp.getTemp();
    else
      curTemp = -1;
    temp.requestTemp();
    dsTimer = millis();
  }
}
void StrizhSat::setCurrentTime() {
  const char* strM="JanFebMarAprMayJunJulAugSepOctNovDec";
  const int i[6] {
    (__TIME__[6]-48)*10+(__TIME__[7]-48), 
    (__TIME__[3]-48)*10+(__TIME__[4]-48), 
    (__TIME__[0]-48)*10+(__TIME__[1]-48), 
    (__DATE__[4]-48)*10+(__DATE__[5]-48), 
    ((int)memmem(strM,36,__DATE__,3)+3-(int)&strM[0])/3, 
    (__DATE__[9]-48)*10+(__DATE__[10]-48)
    
  };
  rtc.settime(i[0],i[1],i[2],i[3],i[4],i[5]);
}

int32_t StrizhSat::getPressure() {
  return bmp.getPressure();
}
float StrizhSat::getAltitude() {
  return 44330 * (1.0 - pow(bmp.getPressure() / 101325.0, 0.1903));
}
float StrizhSat::getBmpTemperature() {
  return bmp.getTemperature();
}
uint32_t StrizhSat::getUnixTime() {
  return rtc.gettimeUnix();
}
uint8_t StrizhSat::getTimeSeconds() {
  rtc.gettime();
  return rtc.seconds;
}
uint8_t StrizhSat::getTimeMinutes() {
  rtc.gettime();
  return rtc.minutes;
}
uint8_t StrizhSat::getTimeHours() {
  rtc.gettime();
  return rtc.Hours;
}
float StrizhSat::getTemperature() {
  return curTemp;
}
/*void StrizhSat::ATWrite(uint32_t address, uint8_t* data, uint32_t length) {
  mem.write(address, data, length);
}
void StrizhSat::ATRead(uint32_t address, uint8_t* data, uint32_t length) {
  mem.read(address, data, length);
}*/

void StrizhSat::ATClear() {
  for(uint32_t i = 0; i < 16384; i++)
    mem.write(i, (byte)0);
}
