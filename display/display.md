# BOARD Repository!

## Introduction

The display layout is designed to adapt an LCD Display (e.g. Displaytech 162A/B) to an STK500/STK600 or Basys3 development board. It also support different input voltages. If the STK500/STK600 connector is used, it is necessary that the board gets 4.5V - 5.5V, otherwise it would not work. If the Basys3 connector is used the input voltage can be 1.5V to 3.3V, the board needs an external power supply (5V) through the DC Jack!

## Connection

### JPW

| PIN | Function   | Description                            |
|:---:|:-----------|:---------------------------------------|
| 1-2 | R/W        | Read/Write mode setup through PIN5     |
| 2-3 | W (always) | Write mode only (PIN5 has no function) |

### J5V

| PIN | Function | Description                              |
|:---:|:---------|:-----------------------------------------|
| 1   | DB4      | Databit 4                                |
| 2   | DB5      | Databit 5                                |
| 3   | DB6      | Databit 6                                |
| 4   | DB7      | Databit 7                                |
| 5   | RW       | Read/Write mode (R=HIGH/W=LOW) (JPW=1/2) |
| 6   | E        | Enable data transfer                     |
| 7   | RS       | Instruction/Data mode                    |
| 8   | -        | Not Used                                 |
| 9   | VCC      | 4.5V - 5.5V, DC Jack not connected       |
| 10  | GND      | Ground connection                        |

### J3V3

| PIN | Function | Description                              |
|:---:|:---------|:-----------------------------------------|
| 1   | DB4      | Databit 4                                |
| 2   | DB5      | Databit 5                                |
| 3   | DB6      | Databit 6                                |
| 4   | DB7      | Databit 7                                |
| 5   | RW       | Read/Write mode (R=HIGH/W=LOW) (JPW=1/2) |
| 6   | RS       | Instruction/Data mode                    |
| 7   | E        | Enable data transfer                     |
| 8   | OE       | Level Shifter output enable              |
| 9   | GND      | Ground connection                        |
| 10  | GND      | Ground connection                        |
| 11  | VCC      | 1.5V - 3.3V, DC Jack connected (5V)      |
| 12  | VCC      | 1.5V - 3.3V, DC Jack connected (5V)      |

## Schematic

![Schematic Description](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_SCH.png "Schematic Description")

[Schematic PDF](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_SCH.pdf)

## Board

### TOP Layer

![TOP Layer Description](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_TOP.png "TOP Layer Description")

[TOP Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_TOP.pdf)

### BOTTOM Layer

![BOTTOM Layer Description](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_BOT.png "BOTTOM Layer Description")

[BOTTOM Layer PDF](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_BOT.pdf)

### COMPONENT Layer

![COMPONENT Layer Description](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_COM.png "COMPONENT Layer Description")

[COMPONENT PDF](https://raw.githubusercontent.com/sunriax/board/master/display/doc/adapter_COM.pdf)
