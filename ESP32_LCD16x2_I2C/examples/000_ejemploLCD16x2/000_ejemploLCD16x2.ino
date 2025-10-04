#include <Arduino.h>
#include "ESP32_LCD16x2_I2C.h"

ESP32_LCD16x2_I2C lcd(0x27, I2C_NUM_1);

void setup() {
  lcd.begin(22, 21);

  lcd.setCursor(0,0);
  lcd.imprimir("Texto corto");

  delay(2000);
  lcd.limpiar();

  // Texto largo con autoscroll
  lcd.imprimirScroll("Este es un mensaje muy largo que no cabe en la pantalla", 0, 500);
}

void loop() {
  // nada por ahora
}
