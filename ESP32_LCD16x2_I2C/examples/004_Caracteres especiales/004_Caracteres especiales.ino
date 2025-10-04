#include <Arduino.h>
#include "ESP32_LCD16x2_I2C.h"

// Dirección del LCD y puerto I2C
ESP32_LCD16x2_I2C lcd(0x27, I2C_NUM_1);

// Mapas de caracteres personalizados (8x5)
const uint8_t simboloGrado[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

const uint8_t flechaDerecha[8] = {
  0b00100,
  0b00010,
  0b11111,
  0b00010,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  lcd.begin(22, 21); // SDA=22, SCL=21

  // Crear los caracteres en el LCD
  lcd.crearCaracter(0, simboloGrado);   // índice 0 -> °
  lcd.crearCaracter(1, flechaDerecha);  // índice 1 -> flecha

  // Mostrar texto normal y caracteres personalizados
  lcd.setCursor(0, 0);
  lcd.imprimir("Temp: 25");
  lcd.imprimirCaracter(0); // °

  lcd.setCursor(1, 0);
  lcd.imprimir("Siguiente ");
  lcd.imprimirCaracter(1); // flecha
}

void loop() {
  // Puedes hacer scroll o desplazamiento
  lcd.desplazarPantalla(true);
  delay(500);
}
