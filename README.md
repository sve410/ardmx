### **Arduino DMX 512 Tester and Controller**
***

Mas informacion en la [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

![Arduino DMX-512 Tester and Controller](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.0%20-%20stable%20-%20Firm%20v0.0%20to%20v0.6/media/Hardware%20v00.JPG)
***

Una herramienta para controlar y probar iluminación de espectáculos controlada por el protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación.
Este proyecto surge por la necesidad de tener un sistema portátil para realizar pruebas rápidas en instalaciones de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes al intemperie, hostiles o de difícil acceso.

Basado en:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Librería Arduino cuatro universos DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Libreria LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* [Simulacion de Arduino desde Proteus - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)

***
### Hardware v0.3
[Notas sobre la version](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/notas%20sobre%20la%20version.txt)
* En construccion...
* LCD de 4x20 con back light y contraste controlado por software
* Alimentación desde USB, baterías o fuente de alimentación externa
* Teclado de navegación
* Teclado numérico 4x4
* Potenciometro para control analogo
* Interruptor de on/off
* Salida DMX desde bornera, XLR de 3 pin y XLR de 5 pin
* Leds de estado de salida DMX
* Simulacion en Proteus v7.7 SP2
* Esquematico y PCB en Proteus v8.0 SP1

***

### [Firmware v0.6](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6)

[Notas sobre la versión...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/Documentacion/notas%20sobre%20la%20version.txt)
* Compatible con [Hardware v0.0](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Hardware-v0.0)
* Navegación desde cursor de fácil acceso e intuitivo
* Inserción rápida de valores desde el teclado numérico
* Inserción de valores desde potenciometro análogo
* Función para ubicar luminaria desde el canal seleccionado
* Acceso rápido a opciones de memoria
* Función de [Black Out](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options) desde el menú "[Memory](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options)"
* 4 modos de control DMX "[Control Options](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#control-options)": [Unitary](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#unitary-control), [Matrix](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#matrix-control), [Multiply](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#multiply-control), [Chaser](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#chaser-control) y [Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#Config)
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
