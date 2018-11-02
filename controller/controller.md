# BOARD Repository!

## Introduction

The controller layout is designed to adapt an LCD Display (e.g. Displaytech 162A/B) and control Text and other stuff through USB (UART). It can be powered through the mini USB jack. If the controller is used the first time, it it necessary to throw the bootloader on the chip. Later there will be a hex file or a link to it in this repository. The first version of the design is now available.

## Connection

### DISPLAY

| PIN | Function | Description                              |
|:---:|:---------|:-----------------------------------------|
| 1   | A        | Backlight anode                          |
| 2   | K        | Backlight cathode                        |
| 3   | VSS      | Ground (0V)                              |
| 4   | VDD      | Supply voltage (5V)                      |
| 5   | VO       | Contrast Voltage                         |
| 6   | RS       | HIGH=Data Signal/LOW=Instruction Signal  | 
| 7   | R/W      | Connected to ground (0V)                 |
| 8   | E        | Chip enable signal                       |
| 9   | DB0      | Data bit 0 (not connected)               |
| 10  | DB1      | Data bit 1 (not connected)               |
| 11  | DB2      | Data bit 2 (not connected)               |
| 12  | DB3      | Data bit 3 (not connected)               |
| 13  | DB4      | Data bit 4                               |
| 14  | DB5      | Data bit 5                               |
| 15  | DB6      | Data bit 6                               |
| 16  | DB7      | Data bit 7                               |

### ISP

| PIN | Function | Description                              |
|:---:|:---------|:-----------------------------------------|
| 1   | MISO     | Master In/Slave Out                      |
| 2   | VCC      | Power supply for ISP programming         |
| 3   | SCK      | Clock input                              |
| 4   | MOSI     | Master Out/Slave In                      |
| 5   | RESET    | System reset                             |
| 6   | GND      | Ground connection                        |

## Schematic

![Schematic Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_SCH.png "Schematic Description")

[Schematic PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_SCH.pdf)

## Board

### TOP Layer

![TOP Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_TOP.png "TOP Layer Description")

[TOP Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_TOP.pdf)

### BOTTOM Layer

![BOTTOM Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_BOT.png "BOTTOM Layer Description")

[BOTTOM Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_BOT.pdf)

### COMPONENT Layer

![COMPONENT Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_COM.png "COMPONENT Layer Description")

[COMPONENT PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/controller_COM.pdf)
