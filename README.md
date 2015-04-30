# Arduino DMX-512 Tester and Controller

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hardware v00.JPG?raw=true "Hard v00")

## Descripción
Herramienta para controlar y probar iluminación de espectáculos controladas por el protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), basado en [Arduino Mega 2560 R3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación.

## Antecedentes
La necesidad de tener un sistema portátil para realizar pruebas rápidas en instalaciones de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes a la intemperie, hostiles o de difícil acceso.

## Características

### Hardware v0.2
- [Notas sobre la version...](/Hardware/Documentacion/notas sobre la version.txt)
- En construccion...
- LCD de 4x20 con back light y contraste controlado por software
- Alimentación desde USB, baterías o fuente de alimentación externa
- Teclado de navegación
- Teclado numérico 4x4
- Potenciometro para control analogo
- Interruptor de on/off
- Salida DMX desde bornera, XLR de 3 pin y XLR de 5 pin
- Leds de estado de salida DMX
- La simulacion en Proteus de Arduino [Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)
- Simulacion en Proteus v7.7 SP2
- Esquematico y PCB en Proteus v8.0 SP1
- [Arduino Mega 2560 R3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)

### Hardware v0.0
- [Notas sobre la version...](/Hardware/Documentacion/notas sobre la version.txt)
- LCD de 4x20
- Alimentación desde USB o directamente al Arduino
- Teclado de navegación entre las opciones
- Teclado numérico 4x4
- Salida DMX desde bornera y XLR de 3 pin
- Leds de estado de salida DMX
- La simulacion en Proteus de Arduino [Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)
- Simulacion en Proteus v7.7 SP2
- Esquematico y PCB en Proteus v8.0 SP1
- [Arduino Mega 2560 R3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
- Aclarar que para este proyecto se utilizó un Arduino Mega hecho en China

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 1.JPG?raw=true "Hard v00")

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 2.JPG?raw=true "Hard v00")

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 3.JPG?raw=true "Hard v00")

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 4.JPG?raw=true "Hard v00")

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 5.JPG?raw=true "Hard v00")

![Alt text](/Hardware/v0.0 - stable - Firm v0.0 to v0.6/media/Hard v00 - 6.JPG?raw=true "Hard v00")

### Firmware v0.6
- [Notas sobre la version...](/Firmware/Documentacion/notas sobre la version.txt)
- Compatible con Hardware v0.0
- Navegación desde cursor de fácil acceso e intuitivo
- Inserción rápida de valores desde el teclado numérico
- Insercion de valores desde potenciometro analogo
- Funcion para ubicar luminaria desde el canal seleccionado
- Acceso rapido a opciones de memoria
- Funcion Black Out desde la memoria
- 4 modos de control DMX
- Control de iluminacion de LCD back light desde la configuracion
- Control de contraste de LCD desde la configuracion
- Acceso rapido desde el teclado al LCD back light
- Compilado en [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
- Libreria Arduino cuatro universos DMX v0.3 [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
- Libreria LCD v1.2.1 [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/About.JPG?raw=true "About")

### Entrada del Usuario
- El símbolo ">" indica el lugar donde se está posicionado en el menú
- El símbolo “+” indica que se espera la entrada numérica del usuario
- La navegación entre los menús, se hace a partir de las teclas del cursor arriba, abajo, derecha, izquierda y centro que aplica como "enter"
- Cuando se da "enter" en un menú que requiere entrada del usuario aparece "+___" y el cursor parpadeante indicando la entrada del usuario, para este caso se utiliza el teclado numérico, si el numero escrito es menor de 3 dígitos presionar "#" que funciona como un "enter" del teclado numérico
- Si se trata de una entrada de usuario en donde se indica el valor de un canal DMX, se puede presionar (después de dar “enter”) la tecla "A" que escribe directamente "255" (el valor máximo de un canal) o la tecla "B" que escribe directamente "0" (el valor mínimo de un canal)
- La tecla "C" funciona como un medio para ubicar una luminaria o un canal en específico, solo basta con seleccionar un canal, posicionarse en el valor, dar "enter" y presionar "C", el valor del canal secuenciara entre "000" y "255", para detenerlo volver a presionar "C"
- Las tecla "*" enciende o apaga el back light
- Las tecla "D" activa solo para los valores el potenciometro analogo
- La opcion Ctrl regresa al menu de Control Options
- El potenciometro analogo permite cambiar los valores

![Alt text](/Firmware/v0.6 Stable - Hard 0.0/Teclado.JPG?raw=true "Teclado")

#### Menu al arranque para acceso a EEPROM:
- Empty (dejar la EEPROM intacta sin modificar, los canales están vacios)
- Load  (cargar los valores guardados del universo DMX desde la EEPROM)
- Clear (borrar los valores guardados de la EEPROM y dejar los canales en cero)

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Initial Memory.JPG?raw=true "Initial Memory")

#### Modos de control:
- Unitary  (acceso rápido a un canal en específico)
- Matrix   (visualizar una matriz de 3 x 5 con los valores actuales de los diferentes canales)
- Chaser   (hacer una secuencia entre canales específicos)
- Multiply (asignar un valor a un número de canales específico, con un salto numérico especifico)

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Control Options.JPG?raw=true "Control Options")

#### Modo de control Unitary:
- Permite el acceso rápido a un canal en específico
- Acceso rápido a las opciones de la memoria EEPROM
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Control Unitary.JPG?raw=true "Control Unitary")

#### Modo de control Matrix: 
- Permite visualizar una matriz de 3 x 5 con los valores actuales de los diferentes canales
- Acceso rápido y visualización de espacio actual de la matriz mostrada
- Acceso rápido a las opciones de la memoria EEPROM
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control
- Visualización del canal actual en la navegación

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Control Matrix.JPG?raw=true "Control Matrix")

#### Modo de control Chaser:
- Permite hacer una secuencia entre canales específicos
- Control de tiempo en mS del paso entre canales
- Visualización del canal actual secuenciado
- Control de inicio y paro de secuencia
- Acceso rápido al menú de “Control Options” para cambiar el tipo de control

![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Control Chaser.JPG?raw=true "Control chaser")

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
  
![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Control Multiply.JPG?raw=true "Control Multiply")

#### Menu de Acceso a memoria:
- Acceso fácil a las opciones de la memoria EEPROM:
  - Save   (guarda el universo DMX con los valores actuales)
  - Load   (carga desde la memoria los valores del universo DMX guardado)
  - Empty  (Borrar la memoria RAM con los valores DMX actuales sin afectar la EEPROM)
  - Clear  (Borrar el universo DMX guardado en la EEPROM)
  - Cancel (regresar al menú anterior sin cambios)
  
![Alt text](/Firmware/v0.1 Stable - Hard 0.0/media/Memory Options.JPG?raw=true "Memory Options")

## Bibliografia
- Simulacion de Arduino desde Proteus [Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)
- Compilador [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
- Libreria Arduino cuatro universos DMX v0.3 [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
- Libreria LCD v1.2.1 [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
- [Arduino Mega 2560 R3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)

## Licenciamiento
[GNU General Public Licence Version 3](/LICENSE)

## Autor
Daniel Roberto Becerril Angeles

- [daniel3514@gmail.com](mailto:daniel3514@gmail.com)
- [Hack a Day](https://hackaday.io/daniel3514)
- [Instructables](http://www.instructables.com/member/daniel3514/)

## Enlaces del proyecto
- [Instructables](http://www.instructables.com/id/Arduino-DMX-512-Tester-and-Controller/)
- [Hack a Day](https://hackaday.io/project/5342-arduino-dmx-512-tester-and-controller)
