# Arduino DMX-512 Tester and Controller

## Descripción
Herramienta para controlar y probar iluminación de espectáculos controladas por el protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), basado en [Arduino Mega 2560 R3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación.

## Antecedentes
La necesidad de tener un sistema portátil para realizar pruebas rápidas en instalaciones de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes a la intemperie, hostiles o de difícil acceso.

## Características

### Hardware v0.1
- LCD de 4x20 con back light controlado por software
- Alimentación desde USB, baterías o fuente de alimentación externa
- Teclado de navegación entre las opciones
- Teclado numérico 4x4
- Salida DMX desde bornera, XLR de 3 pin y XLR de 5 pin
- Leds de estado de salida DMX

### Firmware v0.8
- Navegación desde cursor de fácil acceso e intuitivo
- Inserción rápida de valores desde el teclado numérico

#### Menu al arranque para acceso a EEPROM:
- Empty (dejar la EEPROM intacta sin modificar, los canales están vacios)
- Load (cargar los valores guardados del universo DMX desde la EEPROM)
- Clear (borrar los valores guardados de la EEPROM y dejar los canales en cero)

#### Modo de control Unitary:
- Permite el acceso rápido a un canal en específico
- Acceso rápido a las opciones de la memoria EEPROM
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control

#### Modo de control Matrix: 
- Permite visualizar una matriz de 3 x 5 con los valores actuales de los diferentes canales
- Acceso rápido y visualización de espacio actual de la matriz mostrada
- Acceso rápido a las opciones de la memoria EEPROM
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control
- Visualización del canal actual en la navegación

#### Modo de control Chaser:
- Permite hacer una secuencia entre canales específicos
- Control de tiempo en mS del paso entre canales
- Visualización del canal actual secuenciado
- Control de inicio y paro de secuencia
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control

#### Modo de Control Multiply:
- Permite asignar un valor a un número de canales específico, con un salto numérico especifico
- Valores editables:
  - Value (valor a escribir en los cananles)
  - First Channel (el primer canal donde inicia la multiplicación)
  - Multiply (número de canales a multiplicar)
  - Quantity (cantidad de veces a multiplicar) 
  - Acceso rápido a las opciones de la memoria EEPROM
  - Evaluación del número de multiplicaciones para evitar desbordamientos
  - Visualización del último canal multiplicado

#### Menu de Acceso a memoria
- Acceso fácil a las opciones de la memoria EEPROM:
  - Save (guarda el universo DMX con los valores actuales)
  - Load (carga desde la memoria los valores del universo DMX guardado)
  - Empty (Borrar la memoria RAM con los valores DMX actuales sin afectar la EEPROM)
  - Clear (Borrar el universo DMX guardado en la EEPROM)
  - Cancel (regresar al menú anterior sin cambios)

## Licenciamiento
[GNU General Pubic Licence Version 3](/LICENSE)

## Autor
Daniel Roberto Becerril Angeles

[daniel3514@gmail.com](mailto:daniel3514@gmail.com)

[Facebook](https://www.facebook.com/daniel.3514)
