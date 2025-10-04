# ESP32_LCD16x2_I2C Library

## Description / Descripción
A lightweight library to control 16x2 LCD displays using I2C on the ESP32 platform.  
Librería liviana para controlar pantallas LCD 16x2 mediante I2C en plataformas ESP32.

This library supports:  
- Text printing (`imprimir`)  
- Number and float printing (`imprimirNum`, `imprimirFloat`)  
- Cursor positioning (`setCursor`)  
- Screen clearing and line clearing (`limpiar`, `limpiarLinea`)  
- Text scrolling (`imprimirScroll`)  
- Backlight control (`encenderLuzFondo`, `apagarLuzFondo`)  
- Custom characters creation (`crearCaracter`)  
- Cursor visibility and blinking (`cursorVisible`, `parpadeoCursor`)

## Installation / Instalación
1. Download or clone this repository into your Arduino libraries folder:  
   **Documents/Arduino/libraries/ESP32_LCD16x2_I2C**
2. Restart Arduino IDE.
3. Open the example:  
   `File → Examples → ESP32_LCD16x2_I2C → ESP32_LCD16x2_I2C_Test`

## Usage / Uso
```cpp
#include <Arduino.h>
#include "ESP32_LCD16x2_I2C.h"

// Create LCD object / Crear objeto LCD
ESP32_LCD16x2_I2C lcd(0x27, I2C_NUM_1);

void setup() {
    // Initialize LCD / Inicializar LCD
    lcd.begin(22, 21);

    // Set cursor and print / Establecer cursor e imprimir
    lcd.setCursor(0,0);
    lcd.imprimir("Hello ESP32!");

    delay(2000);
    lcd.limpiar();

    // Scroll long message / Desplazar texto largo
    lcd.imprimirScroll("Scrolling text example / Ejemplo de texto desplazable", 0, 300);
}

void loop() {
    // Nothing here / Nada aquí por ahora
}
```

## Online Simulation / Simulación en línea

You can try the **ESP32_LCD16x2_I2C** library in a Wokwi simulation: 

https://wokwi.com/projects/442740334267204609


## Pinout Example / Ejemplo de conexión

LCD Pin| ESP32 GPIO| Description / Descripción
-------|-----------|-----------------------------
  SDA  |     22    | Data line / Línea de datos
  SCL  |     21    | Clock line / Línea de reloj
  VCC  | 3.3V o 5V |    Power / Alimentación
  GND  |     GND   |       Ground / Tierra

## License / Licencia

This project is released under the MIT License.  
Developed by **Eduardo Balderrama - sidkebo**  

Este proyecto se publica bajo la licencia MIT.  
Desarrollado por **Eduardo Balderrama - sidkebo**

