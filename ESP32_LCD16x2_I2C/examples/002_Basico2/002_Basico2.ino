#include <Arduino.h>
#include "ESP32_LCD16x2_I2C.h"

ESP32_LCD16x2_I2C lcd(0x27, I2C_NUM_1);

void setup() {
  lcd.begin(22, 21);       // SDA=22, SCL=21

  lcd.setCursor(0,0);
  lcd.imprimir("Hola Mundo");

  lcd.setCursor(1,0);
  lcd.imprimirFloat(3.1415, 3); // Ejemplo float
  delay(1000);

  lcd.setCursor(1,8);
  lcd.imprimirNum(1234); // Ejemplo entero
}

void loop() {
  lcd.scrollDerecha();
  delay(500);
  lcd.scrollIzquierda();
  delay(500);
}
