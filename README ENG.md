### **Arduino DMX 512 Tester and Controller**

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.3/media/IMG_9399.JPG)
[![Arduino DMX-512 Tester and Controller](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/v0.0/media/youtube.JPG)](https://www.youtube.com/watch?v=TxBHMpAWDSY)

***

[Spanish version](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/README.md)

More information in the [Wiki...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/wiki)

***

Tool for testing and entertainment lighting control through protocol [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), ideal for quick tests on fixed or temporary lighting installations.
This project arises from the need to have a portable system for rapid testing in lighting installations, without the need to install lighting consoles, interfaces or computers in outdoor environments, hostile or difficult to access.

Based on:
* [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
* [Arduino library four universe DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* [Library LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***
### Hardware v0.4
[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Hardware/Documentacion/Hardware%20-%20Notas%20Sobre%20la%20Version.md)
* Compatible Firmware v0.9 - v1.3
* 4x20 LCD with backlight and contrast controlled by software
* Power supply from USB, batteries or external power supply
* Keyboard navigation
* Keypad 4x4
* Potentiometer for similar control
* Switch on / off (not applicable to USB power)
* DMX output from terminal block, XLR 3 pin and 5-pin XLR
* Output status LEDs DMX
* Simulation in Proteus V7.7 SP2
* Schematic and PCB in Proteus v8.0 SP1

***

### Firmware v1.9

[Release Notes...](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/Documentacion/Firmware%20-%20Notas%20Sobre%20la%20Version.md)

* Compatible Hardware v0.7

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Initial.PNG)

* Navigation from encoder easily accessible and intuitive
* Fast insertion of values from the keypad and encoder
* Function to locate luminaire from the selected channel
* Start with DMX universe preselected
* Selection of memory options to boot

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Initial%20Memory.PNG)

* Menu to select control modes, settings and tools

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Options.PNG)

* DMX Control Unitary allows select 8 specific channels in addition to display the current value

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Control%20Unitary.PNG)

* Matrix Control DMX shows a 3x5 matrix with values of the channels shown, initial and final selectable channel

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Control%20Matrix.PNG)

* Control DMX Chaser allows sequencing channels automatically, the initial channel, channel and end time are selectable, allows sequencing channels manually from the encoder

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Control%20Chaser.PNG)

* DMX Control Sequencer allows sequence between universes stored in the EEPROM memory with a selected time

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Control%20Secuencer.PNG)

* DMX Control Multiply, allows fill values ​​by multiplying the selected channels

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Control%20Multiply.PNG)

* Convert, convert between decimal and binary numbers representing the dip switch systems

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Convert.PNG)

* Memory options, EEPROM and RAM, accessible from any controls

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Memory.PNG)

* 8 banks of memory to store, load and delete the current values, accessible from the MEMU Memory

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Memory%20Bank.PNG)

* Config, to assign the value of Backlight, Key Light, Contrast and Bank Init

![](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Firmware/v1.9/LCD%20media/Config.PNG)

* Compiled in [Arduino IDE v1.0.6] (http://www.arduino.cc/en/Main/OldSoftwareReleases)
* Library v0.3 Arduino four DMX universes - [Deskontrol.net] (http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
* Libreria LCD v1.2.1 - [Francisco Malpartida] (https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

## Repository
[Firmware] (https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Firmware)
* Firmware versions are numbered consecutively
* The folder "Documentation" contains the information of the libraries used
* The folder "Documentation / Hardware" contains information on the specific hardware
* The "Firmware - Notes on Version.md" file contains the historical changes in the different versions of Firmware

[Hardware](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Hardware)
* Hardware versions are numbered consecutively
* The folder "Documentation / Components" contains information of specific components
* The "Hardware - Notas Sobre la Version.md" file contains the historical changes in the different versions of Hardware

[Simulador](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Simulador)
* Simulator versions are numbered consecutively

[Social](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Social)
* Contains information activity on Websites, Blogs and Social Networks

[Software](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Software)
* Contains the software used for the project

[Licencias](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/tree/master/Licencias)
It contains information about licensing the project

***

## Licence
* [GNU General Public Licence Version 3](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Firmware.md)
* [Open Source Hardware (OSHW) v1.0](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Licencias/Licence%20-%20Hardware.md)

## Author
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
[![Hackster](https://github.com/daniel3514/Arduino-DMX-512-Tester-Controller/blob/master/Social/logos/hackster%2050x50.png)](https://www.hackster.io/daniel3514/arduino-dmx-512-tester-controller-977c89)
***
