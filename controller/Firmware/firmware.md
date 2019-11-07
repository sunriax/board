# Display Controller Firmware!

[![Version: 0.9 Alpha](https://img.shields.io/badge/Version-0.9%20Release-green.svg)](https://github.com/sunriax) [![Build Status](https://travis-ci.org/sunriax/board.svg?branch=master)](https://travis-ci.org/sunriax/board) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Slack: Join](https://img.shields.io/badge/Slack-Join-blue.svg)](https://join.slack.com/t/sunriax-technology/shared_invite/enQtMjg3OTE2MjIyMTE2LTU1MmEwNmY5Y2Y3MTNjNzFhYzE5NTFkYWY4NzE0YmQzNzA5NjBkMWQ3ODkyNDI1NjJmMGIwYzMwOGI5ZjA2MDg)

## Description

The Firmware repository includes the Bootloader to serve the desired software to the controller over the integrated usb/uart converter (FT232). If the bootloader is burnt to the ATmega8 out of the board, it is not necessary to mount the ISP header. The FLASH and the EEPROM section can be loaded through the bootloader. To start the Bootloader it is necessary to hold the push-button S1 and S2 during reset. To quit the bootloader without writing data to the flash or the eeprom section press q.

1. Supported Controller
   * Atmel ATmega8
1. Development Hardware
   * STK500 ([Atmel](http://www.microchip.com/webdoc/stk500/index.html))
   * Display Controller
1. Additional Hardware
   * LCD Module ([Displaytech 162B](https://cdn.displaytech-us.com/sites/default/files/display-data-sheet/162B%20series-v21.pdf))
1. Development Software
   * Atmel Studio (uC C/C++)

## Getting Started

To load the demo application (controller) the bootloader has to be on the target (for direct access use an ISP programmer). Run the Bootloader over a console software (e.g. TeraTerm) and setup serial settings to 8 bits, no parity, 1 stopbit and flow control xon/xoff. After that hold the push buttons S1 and S2 and reset the controller. Now the content of controller.hex and the controller.eep can directly be pasted into the console. After loading the demo application should start.

## Important Notice

This files are valid for all repositories at the SUNriaX Github!
* [Readme](https://github.com/sunriax/manual/blob/master/README.md)
* [License](https://github.com/sunriax/manual/blob/master/LICENSE.md)
* [Warranty](https://github.com/sunriax/manual/blob/master/WARRANTY.md)

## Additional Information

You can find more additional information in the [manual](https://github.com/sunriax/manual/tree/master/docs) repository and/or visit the [WIKI](https://wiki.sunriax.at/) for further information (currently under construction).

If there are any further questions feel free to start an issue or contact us, we try to react as quick as possible.

---
**R. GÄCHTER, Rankweil Dec/2019**
