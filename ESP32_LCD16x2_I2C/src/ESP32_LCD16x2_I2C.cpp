#include "ESP32_LCD16x2_I2C.h"
#include "rom/ets_sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

ESP32_LCD16x2_I2C::ESP32_LCD16x2_I2C(uint8_t direccion, i2c_port_t numI2C, bool luzFondo)
    : _direccion(direccion), _numI2C(numI2C), _luzFondo(luzFondo) {}

void ESP32_LCD16x2_I2C::begin(uint8_t sda, uint8_t scl, uint32_t frecuencia) {
    i2c_config_t conf = {};
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sda;
    conf.scl_io_num = scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = frecuencia;
    i2c_param_config(_numI2C, &conf);
    i2c_driver_install(_numI2C, I2C_MODE_MASTER, 0, 0, 0);

    vTaskDelay(50 / portTICK_PERIOD_MS); // espera inicial

    enviarComando(0x33);
    enviarComando(0x32);
    enviarComando(0x28); // 4-bit, 2 líneas, 5x8 dots
    enviarComando(0x0C); // Display ON, cursor OFF
    enviarComando(0x06); // Incrementa cursor
    limpiar();
    if(_luzFondo) encenderLuzFondo();
}

// Comunicación I2C
void ESP32_LCD16x2_I2C::i2cEscribirByte(uint8_t dato) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (_direccion << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, dato, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(_numI2C, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void ESP32_LCD16x2_I2C::pulsoEnable(uint8_t dato) {
    i2cEscribirByte(dato | P_EN);
    ets_delay_us(1);
    i2cEscribirByte(dato & ~P_EN);
    ets_delay_us(50);
}

void ESP32_LCD16x2_I2C::enviarDato(uint8_t dato) {
    uint8_t hi = (dato & 0xF0) | P_RS | (_luzFondo ? P_BL : 0x00);
    uint8_t lo = ((dato << 4) & 0xF0) | P_RS | (_luzFondo ? P_BL : 0x00);
    pulsoEnable(hi);
    pulsoEnable(lo);
}

void ESP32_LCD16x2_I2C::enviarComando(uint8_t comando) {
    uint8_t hi = (comando & 0xF0) | (_luzFondo ? P_BL : 0x00);
    uint8_t lo = ((comando << 4) & 0xF0) | (_luzFondo ? P_BL : 0x00);
    pulsoEnable(hi);
    pulsoEnable(lo);
}

// Funciones de usuario
void ESP32_LCD16x2_I2C::imprimir(const char *str) {
    while(*str) enviarDato(*str++);
}

void ESP32_LCD16x2_I2C::imprimirNum(int num) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d", num);
    imprimir(buffer);
}

void ESP32_LCD16x2_I2C::imprimirFloat(float num, uint8_t decimales) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.*f", decimales, num);
    imprimir(buffer);
}

void ESP32_LCD16x2_I2C::setCursor(uint8_t fila, uint8_t col) {
    uint8_t addr = col + (fila ? 0x40 : 0x00);
    enviarComando(0x80 | addr);
}

void ESP32_LCD16x2_I2C::limpiar() {
    enviarComando(0x01);
    vTaskDelay(2 / portTICK_PERIOD_MS);
}

void ESP32_LCD16x2_I2C::limpiarLinea(uint8_t fila) {
    setCursor(fila, 0);
    for(uint8_t i = 0; i < 16; i++) enviarDato(' ');
    setCursor(fila, 0);
}

void ESP32_LCD16x2_I2C::desplazarPantalla(bool derecha) {
    enviarComando(derecha ? 0x1C : 0x18);
}

void ESP32_LCD16x2_I2C::scrollIzquierda() {
    enviarComando(0x18);
}

void ESP32_LCD16x2_I2C::scrollDerecha() {
    enviarComando(0x1C);
}

void ESP32_LCD16x2_I2C::imprimirScroll(const char* str, uint8_t fila, uint16_t delayMs) {
    size_t len = strlen(str);
    if (len <= 16) {
        setCursor(fila, 0);
        imprimir(str);
        return;
    }

    // Mostrar los primeros 16 caracteres
    setCursor(fila, 0);
    for (int i = 0; i < 16; i++) {
        enviarDato(str[i]);
    }

    // Hacer scroll con el resto
    for (int pos = 0; pos < len - 16; pos++) {
        vTaskDelay(delayMs / portTICK_PERIOD_MS);
        setCursor(fila, 0);
        for (int i = 0; i < 16; i++) {
            enviarDato(str[pos + i + 1]);
        }
    }
}

void ESP32_LCD16x2_I2C::encenderLuzFondo() {
    _luzFondo = true;
    enviarComando(0x00);
}

void ESP32_LCD16x2_I2C::apagarLuzFondo() {
    _luzFondo = false;
    enviarComando(0x00);
}

void ESP32_LCD16x2_I2C::cursorVisible(bool visible) {
    enviarComando(visible ? 0x0E : 0x0C);
}

void ESP32_LCD16x2_I2C::parpadeoCursor(bool parpadeo) {
    enviarComando(parpadeo ? 0x0D : 0x0C);
}

//
// Caracteres especiales
//
void ESP32_LCD16x2_I2C::crearCaracter(uint8_t indice, const uint8_t mapa[8]) {
    if (indice > 7) return; // solo 8 caracteres posibles (0–7)
    enviarComando(0x40 | (indice << 3)); // dirección CGRAM
    for (uint8_t i = 0; i < 8; i++) {
        enviarDato(mapa[i]);
    }
}

void ESP32_LCD16x2_I2C::imprimirCaracter(uint8_t indice) {
    if (indice > 7) return;
    enviarDato(indice);
}
