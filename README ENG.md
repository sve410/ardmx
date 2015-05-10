### **Arduino DMX 512 Tester and Controller**
***

More information in the [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

![Arduino DMX-512 Tester and Controller](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.0%20-%20stable%20-%20Firm%20v0.0%20to%20v0.6/media/Hardware%20v00.JPG)

[![YouTube](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v0.6%20Stable%20-%20Hard%200.0/Media/youtube.JPG)](https://www.youtube.com/watch?v=TxBHMpAWDSY)

***

A tool to control and test light show controlled by the protocol [DMX-512] (http://es.wikipedia.org/wiki/Digital_Multiplex), ideal for quick tests on fixed or temporary installations of lighting.
This project arises from the need to have a portable system for rapid testing in lighting installations, without the need to install lighting consoles, interfaces or computers in environments outside, hostile or difficult to access.

Based on:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Arduino library four universes DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Library LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* [Arduino from Proteus Simulation - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)

***

### Hardware v0.3
[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/notas%20sobre%20la%20version.txt)
* Under construction...
* 4x20 LCD with backlight and contrast controlled by software
* Power supply from USB, batteries or external power supply
* Keyboard navigation
* Keypad 4x4
* Control potentiometer for analogue
* Switch on / off
* DMX output from terminal block, XLR 3-pin and 5-pin XLR
* Output status LEDs DMX
* Simulation in Proteus V7.7 SP2
* Schematic and PCB in Proteus v8.0 SP1

***

### [Firmware v0.6](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6)

[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/Documentacion/notas%20sobre%20la%20version.txt)
* Compatible with [Hardware v0.0](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Hardware-v0.0)
* Cursor navigation from easily accessible and intuitive
* Fast Inserting values from the keypad
* Insert values from analog potentiometer
* Function to locate luminaire from the selected channel
* Quick access to memory options
* Feature [Black Out](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options) desde el menú "[Memory](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#memory-options)"
* Control 4 modes DMX "[Control Options](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#control-options)": [Unitary](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#unitary-control), [Matrix](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#matrix-control), [Multiply](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#multiply-control), [Chaser](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#chaser-control) y [Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#Config)
* Lighting control LCD backlight from the menu "[Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#config)"
* LCD contrast control from from the menu "[Config](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#config)"
* Quick access from the [keyboard](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki/Firmware-v0.6#entrada-del-usuario) al LCD back light
* Compiled by [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
* Arduino library four universes DMX v0.3 - [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* Library LCD v1.2.1 - [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

## License
[GNU General Public Licence Version 3](/LICENSE)

## Author
Daniel Roberto Becerril Angeles

- [daniel3514@gmail.com](mailto:daniel3514@gmail.com)
- [Tech Inside](http://www.techinside.com.mx)
- [Hack a Day](https://hackaday.io/daniel3514)
- [Instructables](http://www.instructables.com/member/daniel3514/)

***
