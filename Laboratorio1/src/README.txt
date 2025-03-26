# IE0624 | Laboratorio 1: Dado Electrónico con PIC en SimulIDE
# Alejandro Castillo Sequeira - B81787

Este proyecto simula un dado electrónico utilizando un microcontrolador PIC y SimulIDE. 

## Descripción

El proyecto consiste en un circuito electrónico simulado en SimulIDE que utiliza un microcontrolador PIC para generar números aleatorios (del 1 al 6), simulando el lanzamiento de un dado. Los resultados se visualizan mediante un conjunto de LEDs.

## Descripción de los principales archivos incluidos

* **dado.asm**: Código fuente en lenguaje ensamblador para el microcontrolador PIC.
* **dado.c**: Código fuente en lenguaje C para el microcontrolador PIC.
* **dado.simu**: Archivo de simulación de SimulIDE que contiene el circuito completo.
* **dado\_backup.simu**: Copia de seguridad del archivo de simulación.
* **Makefile**: Archivo de configuración para la compilación/ensamblaje.


## Requisitos

* SimulIDE instalado en su sistema.

## Instrucciones de Uso
1.  Correr make en terminal para generar .hex
2.  Abrir el archivo `dado.simu` en SimulIDE.  
3.  Cargar el firmware.
2.  Inicia la simulación.
3.  Observa el funcionamiento del dado electrónico simulado.

