#include <Arduino.h>
#include <StrizhSat.h>

StrizhSat strizh;
uint32_t timer = 0;

void setup() {
  strizh.init();
  Serial.begin(9600);
}
void loop() {
  strizh.tick();
  if(millis() - timer > 2000) {
    Serial.print("Time: ");
    Serial.print(strizh.getTime()->Hours);
    Serial.print(":");
    Serial.print(strizh.getTime()->minutes);
    Serial.print(":");
    Serial.println(strizh.getTime()->seconds);
    Serial.print("Temperature: ");
    Serial.println(strizh.getTemperature());
    Serial.print("Pressure: ");
    Serial.println(strizh.getPressure());
    Serial.print("Altitude: ");
    Serial.println(strizh.getAltitude());
    Serial.print("BMP temperature: ");
    Serial.println(strizh.getBmpTemperature());
    Serial.println("");
    timer = millis();
  } 
}