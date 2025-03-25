#include <pic14/pic12f683.h>
#include <stdint.h>

// Desactiva el Watchdog Timer (evita reinicios automáticos)
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF);

// Función que introduce una pausa para hacer visibles los cambios en los LEDs
void esperar(unsigned int t) {
    while (t--) for (unsigned int i = 0; i < 2000; i++);
}
