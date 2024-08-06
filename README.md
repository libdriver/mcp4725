[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP4725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp4725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MCP4725 is a low-power, high accuracy, single channel, 12-bit buffered voltage output Digital-to-Analog Convertor (DAC) with non-volatile memory (EEPROM). Its on-board precision output amplifier allows it to achieve rail-to-rail analog output swing.
The DAC input and configuration data can be programmed to the non-volatile memory (EEPROM) by the user using I2C interface command. The non-volatile memory feature enables the DAC device to hold the DAC input code during power-off time, and the DAC output is available immediately after power-up. This feature is very useful when the DAC device is used as a supporting device for other devices in the network. The device includes a Power-On-Reset (POR) circuit to ensure reliable power-up and an on-board charge pump for the EEPROM programming voltage. The DAC reference is driven from VDD directly. In powerdown
mode, the output amplifier can be configured to present a known low, medium, or high resistance output load.The MCP4725 has an external A0 address bit selection pin. This A0 pin can be tied to VDD or VSS of the user’s application board.The MCP4725 has a two-wire I2C. compatible serial interface for standard (100 kHz), fast (400 kHz), or high speed (3.4 MHz) mode. The MCP4725 is an ideal DAC device where design simplicity and small footprint is desired, and for applications requiring the DAC device settings to be saved during power-off time. The device is available in a small 6-pin SOT-23 package. MCP4725 is used in sensor calibration, closed-loop servo control, low-power portable instruments, PC peripherals and data acquisition system.

LibDriver MCP4725 is a full function MCP4725 driver launched by LibDriver.It provides DAC output and DAC output value reading function. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MCP4725 source files.

/interface includes LibDriver MCP4725 IIC platform independent template.

/test includes LibDriver MCP4725 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MCP4725 sample code.

/doc includes LibDriver MCP4725 offline document.

/datasheet includes MCP4725 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_mcp4725_basic.h"

uint8_t res;

res = mcp4725_basic_init(MCP4725_ADDR_A0_GND);
if (res != 0)
{
    return 1;
}

...

res = mcp4725_basic_write(1.2f);
if (res != 0)
{
    mcp4725_interface_debug_print("mcp4725: write failed.\n");
    (void)mcp4725_basic_deinit();

    ...
    
    return 1;
}

...

(void)mcp4725_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/mcp4725/index.html](https://www.libdriver.com/docs/mcp4725/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.