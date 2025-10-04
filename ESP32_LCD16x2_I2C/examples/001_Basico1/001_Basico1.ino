#include <Arduino.h>
#include "ESP32_LCD16x2_I2C.h"

// Crear objeto LCD en la dirección I2C 0x27, usando I2C_NUM_1
ESP32_LCD16x2_I2C lcd(0x27, I2C_NUM_1);

void setup() {
  // Inicializar LCD con SDA=22, SCL=21
  lcd.begin(22, 21);

  // Encender retroiluminación
  lcd.encenderLuzFondo();

  // Mostrar mensaje de bienvenida
  lcd.setCursor(0, 0);
  lcd.imprimir("Hola Mundo!");

  // Mostrar número
  lcd.setCursor(1, 0);
  lcd.imprimirNum(12345);

  // Mostrar número con decimales
  lcd.setCursor(1, 7);
  lcd.imprimirFloat(3.1416, 2);

  // Activar cursor visible y parpadeo
  lcd.cursorVisible(true);
  lcd.parpadeoCursor(true);
  
  delay(2000); // Espera 2 segundos
  lcd.limpiar(); // Limpiar pantalla
}

void loop() {
  // Mostrar texto desplazándose hacia la derecha
  lcd.setCursor(0, 0);
  lcd.imprimir("Desplazando -->");
  lcd.desplazarPantalla(true);
  delay(500);

  // Limpiar pantalla
  lcd.limpiar();

  // Mostrar texto desplazándose hacia la izquierda
  lcd.setCursor(1, 0);
  lcd.imprimir("<-- Desplazando");
  lcd.desplazarPantalla(false);
  delay(500);

  // Limpiar pantalla y repetir
  lcd.limpiar();
}
