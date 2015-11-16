### **Arduino DMX 512 Tester and Controller**

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.3/media/IMG_9399.JPG)
[![Arduino DMX-512 Tester and Controller](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.0/media/youtube.JPG)](https://www.youtube.com/watch?v=TxBHMpAWDSY)

***

[Spanish version](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/README.md)

More information on [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

***

Control tool for testing and light show by the [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex) protocol, ideal for quick tests on fixed or temporary installations of lighting.
This project arises from the need to have a portable system for rapid testing in lighting installations, without the need to install lighting consoles, interfaces or computers in environments outside, hostile or difficult to access.

Based on:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Arduino library four universes DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Library LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* [Arduino from Proteus Simulation - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)

***
### Hardware v0.4
[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/Hardware%20-%20Notas%20Sobre%20la%20Version.md)
* Supports Firmware v0.9 - v1.3
* 4x20 LCD with backlight and contrast controlled by software
* Power from USB, batteries or external power supply
* Navigation keypad
* 4x4 keypad
* Analog control potentiometer
* Switch on / off (not applicable to USB power)
* DMX output from terminal block, XLR 3-pin and 5-pin XLR
* Output status LEDs DMX
* Simulation in Proteus V7.7 SP2
* Schematic and PCB in Proteus v8.0 SP1

***

### Firmware v1.2
[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/Documentacion/Firmware%20-%20Notas%20Sobre%20la%20Version.md)
* Supports Hardware v0.3 - v0.4
* Navigation from cursor easily accessible and intuitive
* Fast Inserting values ​​from the keypad
* Insert values ​​from analog potentiometer
* Memory Banks store 8 DMX universes
* Reading from the EEPROM to start DMX universe preselected
* Selection of memory options to start
* DMX Control Unitary, selects a specific channel, and shows the values ​​of the previous channels and next
* Matrix Control DMX shows a 3 x 5 matrix with the values ​​of the channels shown
* Chaser DMX Control allows sequence selected channels, with a selected time
* DMX Sequencer allows sequencing between universes stored in the EEPROM memory with a selected time
* Multiply DMX Control allows multiplying values ​​fill the selected channels
* Function to locate luminaire from the selected channel
* Quick access to memory options
* Memory options Save, Load, Clear, Clear All (for banks and empty RAM memory
* Memory options for the 8 DMX universes banks
* Function Black Out
* Control of LCD back light illumination
* LCD Contrast Control
* Keyboard Shortcuts from the LCD back light
* compiled by [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
* Arduino library four universes DMX v0.3 - [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* Library LCD v1.2.1 - [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

## Repository
[Firmware](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Firmware)
* Firmware versions are numbered consecutively
* The folder "Documentacion" contains the information of the libraries used
* The folder "Documentacion / Hardware" contains information of specific hardware
* The "Firmware - Notas Sobre la Version.md" file contains the historical changes in the different versions of Firmware

[Hardware](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Hardware)
* Hardware versions are numbered consecutively
* The folder "Documentacion / Components" contains information of specific components
* The "Hardware - Notas Sobre la Version.md" file contains the historical changes in the different versions of Hardware

[Simulador](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Simulador)
* Simulator versions are numbered consecutively

[Social](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Social)
* The "Publicados.txt" file contains the information about the activity on Websites, Blogs and Social Networks

[Software](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Software)
* Contains software used for the project

[Licencias](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Licencias)
* It contains information about licensing the project

***

## Licence
* [GNU General Public Licence Version 3](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Firmware.md)
* [Open Source Hardware (OSHW) v1.0](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Hardware.md)

## Autor
- Copyright (C) 2015
- [Daniel Roberto Becerril Angeles](https://www.facebook.com/daniel.3514)

[![Email](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/email%2050x50.jpg)](mailto:daniel3514@gmail.com)
[![Facebook](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Facebook%2050x50.png)](https://www.facebook.com/daniel.3514)
[![Facebook](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Facebook%20Pages%2050x50.jpg)](https://www.facebook.com/ArduinoDMX512TesterController)
[![Twitter](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Twitter%2050x50.png)](https://twitter.com/daniel3514)
[![Instructables](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Instructables%2050x50.jpg)](http://www.instructables.com/id/Arduino-DMX-512-Tester-and-Controller/)
[![Hack a Day](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/hackaday%2050x50.jpg)](https://hackaday.io/project/5342-arduino-dmx-512-tester-and-controller)
[![Youtube](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/Youtube%2050x50.png)](https://www.youtube.com/watch?v=TxBHMpAWDSY)
[![Tech Inside](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/techinside%2045x45.png)](https://techinsideblog.wordpress.com/)
[![GitHub](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/github%2050x50.png)](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller)
***
