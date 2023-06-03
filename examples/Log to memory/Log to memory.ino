#include <Arduino.h>
#include <StrizhSat.h>

StrizhSat sat; // создаем обьект библиотеки
uint32_t timer = 0;
uint16_t counter = 0;

struct Telemetry {
    uint32_t time;
    float temperature;
    int32_t pressure;
    float altitude;
}; // создаем структуру, которая объеденит всю телеметрию

void setup() {
  sat.init(); // инициализируем датчики спутника
  Serial.begin(9600);
  uint8_t memcheck; // с помощью этой переменной проверим пустоту памяти
  sat.ATRead(2, memcheck); // считываем 3 ячейку памяти
  if(memcheck != 48) { // если она не 48 сделаем её 48
    sat.ATWrite(2, 48);
    sat.ATWrite(0, (uint16_t)0); // текущая позичия записи = 0
  }
}
void loop() {
  sat.tick(); // обрабатываем значения с датчиков
  if(millis() - timer > 2000) { // каждые 2 секунды выводим значения
    Telemetry data; // создаем объект структуры
    data.time = sat.getUnixTime(); // записываем в обьект время
    data.temperature = sat.getTemperature(); // записываем температуру
    data.pressure = sat.getPressure(); // записываем давление
    data.altitude = sat.getAltitude(); // записываем высоту
    uint16_t curPos; // текущая позиция записи
    sat.ATRead(0, curPos); 
    sat.ATWrite(curPos * sizeof(Telemetry) + 3, data); // записываем данные
    sat.ATWrite(0, curPos + 1);
    // + 3 потому что 3 ячейки в начале памяти использованы для хранения текущей позиции и тестового значения
    timer = millis();
    if(counter++ == 5) { // каждые 10 секунд
      for(uint16_t i = 0; i < curPos; i++) {
        Telemetry readed; // создаем обьект структуры в который прочитаем данные
        sat.ATRead(curPos * sizeof(Telemetry) + 3, readed); // читаем
        Serial.println(readed.time); // выводим телеметрию
        Serial.println(readed.temperature);
        Serial.println(readed.pressure);
        Serial.println(readed.altitude);
      }
      counter = 0;
    }
  } 
  
}