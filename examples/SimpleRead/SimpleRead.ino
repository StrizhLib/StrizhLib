#include <Arduino.h>
#include <StrizhSat.h>

StrizhSat sat; // создаем обьект библиотеки
uint32_t timer = 0; 

void setup() {
  sat.init(); // инициализируем датчики спутника
  Serial.begin(9600);
}
void loop() {
  sat.tick(); // обрабатываем значения с датчиков
  if(millis() - timer > 2000) { // каждые 2 секунды выводим значения
    Serial.print("Time: ");
    Serial.print(sat.getTimeHours());
    Serial.print(":");
    Serial.print(sat.getTimeMinutes());
    Serial.print(":");
    Serial.println(sat.getTimeSeconds());
    Serial.print("Temperature: ");
    Serial.println(sat.getTemperature());
    Serial.print("Pressure: ");
    Serial.println(sat.getPressure());
    Serial.print("Altitude: ");
    Serial.println(sat.getAltitude());
    Serial.print("BMP temperature: ");
    Serial.println(sat.getBmpTemperature());
    Serial.println("");
    timer = millis();
  } 
}