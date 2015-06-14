### **Arduino DMX 512 Tester and Controller**
***

English version

Mas informacion en la [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

***

Una herramienta para probar y controlar iluminación de espectáculos a travez del protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación.
Este proyecto surge por la necesidad de tener un sistema portátil para realizar pruebas rápidas en instalaciones de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes al intemperie, hostiles o de difícil acceso.

Basado en:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Librería Arduino cuatro universos DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Libreria LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* [Simulacion de Arduino desde Proteus - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)

***
### Hardware v0.4
[Notas sobre la version...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/Hardware%20-%20Notas%20Sobre%20la%20Version.md)
* Compatible con Firmware v0.9 - v1.2
* LCD de 4x20 con backlight y contraste controlado por software
* Alimentación desde USB, baterías o fuente de alimentación externa
* Teclado de navegación
* Teclado numérico 4x4
* Potenciometro para control analogo
* Interruptor de on/off (no aplica en alimentacion por USB)
* Salida DMX desde bornera, XLR de 3 pin y XLR de 5 pin
* Leds de estado de salida DMX
* Simulacion en Proteus v7.7 SP2
* Esquematico y PCB en Proteus v8.0 SP1

***

### Firmware v1.2

[Notas sobre la versión...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/Documentacion/Firmware%20-%20Notas%20Sobre%20la%20Version.md)
* Compatible con Hardware v0.3 - v0.4
* Navegación desde cursor de fácil acceso e intuitivo
* Inserción rápida de valores desde el teclado numérico
* Inserción de valores desde potenciometro análogo
* Bancos de memoria para almacenar 8 universos DMX
* Lectura desde la EEPROM al arranque de universo DMX preseleccionado
* Seleccion de opciones de memoria al arranque 
* 5 modos de control DMX: Unitary, Matrix, Chaser, Secuencer, Multiply
** test
* Función para ubicar luminaria desde el canal seleccionado
* Acceso rápido a opciones de memoria
* Función de [Black Out](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options) desde el menú "[Memory](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options)"

* Control de iluminación de LCD back light desde el menu "[Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#config)"
* Control de contraste de LCD desde desde el menu "[Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#config)"
* Acceso rápido desde el [teclado](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#entrada-del-usuario) al LCD back light
* Compilado en [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
* Librería Arduino cuatro universos DMX v0.3 - [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* Libreria LCD v1.2.1 - [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

## Licenciamiento
[GNU General Public Licence Version 3](/LICENSE)

## Autor
Daniel Roberto Becerril Angeles

- [daniel3514@gmail.com](mailto:daniel3514@gmail.com)
- [Tech Inside](http://www.techinside.com.mx)
- [Hack a Day](https://hackaday.io/daniel3514)
- [Instructables](http://www.instructables.com/member/daniel3514/)

***
