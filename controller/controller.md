# BOARD Repository!

## Introduction

The controller layout is designed to adapt an LCD Display (e.g. Displaytech 162A/B) and control Text and other stuff through USB (UART). It can be powered through the mini USB jack. If the controller is used the first time, it it necessary to throw the bootloader on the chip. Later there will be a hex file or a link to it in this repository. Actually the design isn´t complete. So it may take a while until it gets finished.


## Connection

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
