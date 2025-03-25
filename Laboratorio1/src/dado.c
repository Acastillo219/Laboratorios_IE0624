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
