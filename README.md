# OpenZ3Gateway
An open source Zstack3 gateway powered by ESP8266 and CC2652P modules. One costs less than 60 CNY in China.

![image](https://github.com/cyijun/OpenZ3Gateway/blob/main/images/Board.jpg)
![image](https://github.com/cyijun/OpenZ3Gateway/blob/main/images/Flashing.jpg)
![image](https://github.com/cyijun/OpenZ3Gateway/blob/main/images/Running.jpg)

## This repository includes 
1. Altium Designer schematic and PCB files
2. Schematic and PCB in PDF
3. Gerber files
4. A lite Arduino Ser2Net project for ESP8266 based on <https://github.com/dparnell/esp8266-ser2net>

## Usage
1. Send the Gerber file to PCB factory for production
2. Buy the components you need
3. Solder them
4. Flash the CC2652P with [the latest "CC1352P2_CC2652P_launchpad_coordinator" coordinator zstack firmware](https://github.com/Koenkk/Z-Stack-firmware/blob/master/coordinator/Z-Stack_3.x.0/bin/)
5. Compile and upload the Ser2Net project to ESP8266.

Note: Jumper caps are needed to choose the function of the board. 

## About The 2.54 Ports
* The 2x7 IDC port will be used to connect to my MT7621 OpenWrt Gateway project. 
* The 2x10 IDC port can be directly connected to the XDS110 port, this board can be a cheap CC2652 multi protocol development board too.
* The two 1x6 XH2.54 port are used to connect my CH340C auto-upload circuit board, which will be opened too.

## Why Not USB?
* Of course this board can be used as a USB "stick"! You can connect my CH340C auto-upload circuit board project to the XH2.54 port of CC2652 module and adjust the jumper caps. Then you can use it as a "stick" like ZZH.
* The other reason is you need powerful ZigBee routers if your house is too large. An ESP8266 will help you manage the routers easier, you can reset the nodes by ESP8266 easily.

## Boo
I'm too lazy to list a BOM, please check the schematic for components list.
