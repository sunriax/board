# BOARD Repository!

## Introduction

The controller layout is designed to adapt an LCD Display (e.g. Displaytech 162A/B) and control Text and other stuff through USB (UART). It can be powered through the mini USB jack. If the controller is used the first time, it it necessary to throw the [Bootloader](./Firmware/firmware.md) on the chip.

## Firmware

In [Firmware](./Firmware/firmware.md) repository the additional software to control the display is stored.

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

![Schematic Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_schematic.png "Schematic Description")

[Schematic PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_schematic.pdf)

## Board

### Bill of material

Necessary parts to build the board are documented in the THT and SMD bill of material list. We recommend to buy the parts at [RS-Components](https://at.rs-online.com/). The related numbers are deposited at the bill of material lists.

* [Bill of material THT](./partlist.csv)
* [Bill of material SMD](./partlist_SMD.csv)

### All Layers

![BOARD Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board.png "BOARD Layer Description")

[BOARD PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board.pdf)


### TOP Layer

![TOP Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_top.png "TOP Layer Description")

[TOP Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_top.pdf)

![TOP Layer Place](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_tplace.png "TOP Layer Place")

[TOP Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_tplace.pdf)

### BOTTOM Layer

![BOTTOM Layer Description](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_bot.png "BOTTOM Layer Description")

[BOTTOM Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_bot.pdf)

![BOTTOM Layer Place](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_bplace.png "BOTTOM Layer Place")

[BOTTOM Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/controller/doc/board_bplace.pdf)
