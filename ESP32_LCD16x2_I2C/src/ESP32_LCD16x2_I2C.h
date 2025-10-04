#pragma once
#include <stdint.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class ESP32_LCD16x2_I2C {
public:
    ESP32_LCD16x2_I2C(uint8_t direccion, i2c_port_t numI2C = I2C_NUM_1, bool luzFondo = true);

    void begin(uint8_t sda, uint8_t scl, uint32_t frecuencia = 100000);

    // Funciones básicas
    void imprimir(const char *str);
    void imprimirNum(int num);
    void imprimirFloat(float num, uint8_t decimales = 2);
    void setCursor(uint8_t fila, uint8_t col);
    void limpiar();
    void limpiarLinea(uint8_t fila);
    void desplazarPantalla(bool derecha);
    void scrollIzquierda();
    void scrollDerecha();
    void imprimirScroll(const char* str, uint8_t fila, uint16_t delayMs = 300);

    // Funciones de cursor
    void cursorVisible(bool visible);
    void parpadeoCursor(bool parpadeo);

    // Retroiluminación
    void encenderLuzFondo();
    void apagarLuzFondo();

    //Caracteres especiales
    void crearCaracter(uint8_t indice, const uint8_t mapa[8]);
    void imprimirCaracter(uint8_t indice);

private:
    uint8_t _direccion;
    i2c_port_t _numI2C;
    bool _luzFondo;

    static constexpr uint8_t P_RS = 0x01;
    static constexpr uint8_t P_RW = 0x02;
    static constexpr uint8_t P_EN = 0x04;
    static constexpr uint8_t P_BL = 0x08;

    void i2cEscribirByte(uint8_t dato);
    void enviarDato(uint8_t dato);
    void enviarComando(uint8_t comando);
    void pulsoEnable(uint8_t dato);
};
