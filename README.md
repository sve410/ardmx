### **Arduino DMX 512 Tester and Controller**

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.3/media/IMG_9399.JPG)
[![Arduino DMX-512 Tester and Controller](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.0/media/youtube.JPG)](https://www.youtube.com/watch?v=TxBHMpAWDSY)

***

[English version](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/README%20ENG.md)

Mas informacion en la [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

***

Herramienta para pruebas y control de iluminación de espectáculos a travez del protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación.
Este proyecto surge por la necesidad de tener un sistema portátil para realizar pruebas rápidas en instalaciones de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes al intemperie, hostiles o de difícil acceso.

Basado en:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Librería Arduino cuatro universos DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Libreria LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* [Simulacion de Arduino desde Proteus - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)

***
### Hardware v0.4
[Notas sobre la version...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/Hardware%20-%20Notas%20Sobre%20la%20Version.md)
* Compatible con Firmware v0.9 - v1.3
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
* Control DMX Unitary, permite seleccionar un canal especifico, ademas de mostrar los valores de los canales anterior y siguiente
* Control DMX Matrix, muestra una matriz de 3 x 5 con los valores de los canales mostrados
* Control DMX Chaser, permite secuenciar canales seleccionados, con un tiempo seleccionado
* Control DMX Secuencer, permite secuenciar entre los universos guardados en la memoria EEPROM con un tiempo seleccionado
* Control DMX Multiply, permite llenar valores multiplicando los canales seleccionados
* Función para ubicar luminaria desde el canal seleccionado
* Acceso rápido a opciones de memoria
* Opciones de memoria Save, Load, Clear, Clear All (para los bancos de memoria y empty RAM
* Opciones de memoria para los 8 bancos de universos DMX
* Función de Black Out
* Control de iluminación de LCD back light
* Control de contraste de LCD
* Acceso rápido desde el teclado LCD back light
* Compilado en [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
* Librería Arduino cuatro universos DMX v0.3 - [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* Libreria LCD v1.2.1 - [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

## Repositorio
[Firmware](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Firmware)
* Las versiones del Firmware estan numeradas de manera consecutiva
* La carpeta de "Documentacion" contiene la informacion de las librerias utilizadas
* La carpeta de "Documentacion/Hardware" contiene la informacion del hardware especifico
* El archivo "Firmware - Notas Sobre la Version.md" contiene el historico de cambios en las diferentes versiones del Firmware

[Hardware](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Hardware)
* Las versiones del Hardware estan numeradas de manera consecutiva
* La carpeta de "Documentacion/Componentes" contiene la informacion de los componentes especificos
* El archivo "Hardware - Notas Sobre la Version.md" contiene el historico de cambios en las diferentes versiones del Hardware

[Simulador](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Simulador)
* Las versiones del Simulador estan numeradas de manera consecutiva

[Social](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Social)
* El archivo "Publicados.txt" contiene la informacion de la actividad en Webs, Blogs y Redes Sociales

[Software](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Software)
* Contiene el software utilizado para el proyecto

[Licencias](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Licencias)
* Contiene la informacion sobre el licenciamiento del proyecto

***

## Licenciamiento
* [GNU General Public Licence Version 3](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Firmware.md)
* [Open Source Hardware (OSHW) v1.0](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Hardware.md)

## Autor
- Copyright (C) 2015
- [Daniel Roberto Becerril Angeles](https://www.facebook.com/daniel.3514)
- [daniel3514@gmail.com](mailto:daniel3514@gmail.com)
- [Tech Inside](http://www.techinside.com.mx)
- [Hack a Day](https://hackaday.io/daniel3514)

***

[![Facebook](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Facebook%2050x50.png)](https://www.facebook.com/ArduinoDMX512TesterController)
[![Twitter](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Twitter%2050x50.png)](https://twitter.com/daniel3514)
[![Instructables](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Instructables%2050x50.jpg)](http://www.instructables.com/id/Arduino-DMX-512-Tester-and-Controller/)
[![Hack a Day](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/hackaday%2050x50.jpg)](https://hackaday.io/project/5342-arduino-dmx-512-tester-and-controller)
