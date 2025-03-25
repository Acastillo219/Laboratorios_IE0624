#include <pic14/pic12f683.h>
#include <stdint.h>

// Desactiva el Watchdog Timer (evita reinicios automáticos)
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF);

// Función que introduce una pausa para hacer visibles los cambios en los LEDs
void esperar(unsigned int t) {
    while (t--) for (unsigned int i = 0; i < 2000; i++);
}

// Rotación de bits a la izquierda, usada por el generador de números aleatorios
uint8_t rotar_izq(uint8_t v, int k) {
    return (v << k) | (v >> (8 - k));
}
// Estado interno para el generador de números aleatorios
uint8_t estado[2] = { 0, 0xA3 };

// Algoritmo Xorshift modificado para generar números pseudoaleatorios
uint8_t siguiente(void) {
    uint8_t r = estado[0] + estado[1];
    estado[1] ^= estado[0];
    estado[0] = rotar_izq(estado[0], 6) ^ estado[1] ^ (estado[1] << 1);
    estado[1] = rotar_izq(estado[1], 3);
    return r;
}

// Devuelve un número aleatorio entre 1 y 6, simulando el lanzamiento de un dado
int dado_virtual(void) {
    int n = siguiente() & 0x07; // Limita el rango a 0–7
    return (n == 0 || n > 6) ? dado_virtual() : n; // Reintenta si está fuera del rango 1–6
}

void main(void) {
    // Configura GP5 como entrada (botón), el resto como salidas (LEDs)
    TRISIO = 0b00100000;
    GPIO = 0x00; // Apaga todos los LEDs al inicio
    const unsigned int retardo = 200; // Tiempo base de espera

    while (1) {
        if (GP5) { // Si se presiona el botón (GP5 en alto)
            switch (dado_virtual()) {
                case 1: GP1 = 1; esperar(retardo); GP1 = 0; break;             // Enciende LED en GP1
                case 2: GP0 = 1; esperar(retardo); GP0 = 0; break;             // Enciende LED en GP0
                case 3: GPIO = 0b00000011; break;                              // Enciende GP0 y GP1
                case 4: GPIO = 0b00000101; break;                              // Enciende GP0 y GP2
                case 5: GPIO = 0b00000111; break;                              // Enciende GP0, GP1 y GP2
                case 6: GPIO = 0b00010101; break;                              // Enciende GP0, GP2 y GP4
            }
            // Apaga todos los LEDs luego del retardo, para los casos con varios LEDs
            if (GP5 != 1 || GPIO) { esperar(retardo); GPIO = 0; }
        } else {
            GPIO = 0; // Apaga los LEDs si el botón no está presionado
        }
    }
}

