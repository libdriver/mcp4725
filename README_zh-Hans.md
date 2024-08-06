[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP4725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp4725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MCP4725是一款低功耗、高精度、单通道，12位的DAC。DAC输入和配置数据可以通过IIC接口编程到非易失性存储器（EEPROM）。非易失性存储器使DAC设备掉电时能够保持DAC数值，DAC通电后立即输出存储数值。该芯片包括一个上电复位（POR）电路，用于确保可靠的通电和车载充电EEPROM编程电压泵。芯片以VDD作为DAC输出参考电压。断电模式下，输出放大器可配置为低、中或高电阻输出负载。MCP4725具有外部A0地址选择位。A0引脚可连接到用户设备的VDD或VSS应用程序板。MCP4725具有两线IIC兼容串行标准（100 kHz）、快速（400 kHz）或高速接口速度（3.4 MHz）模式，MCP4725是一个理想的DAC器件。MCP4725被用于传感器校准、闭环伺服控制、低功耗便携仪器、PC外围设备和数据采集系统。

LibDriver MCP4725是LibDriver推出的MCP4725全功能驱动，该驱动提供DAC输出和DAC输出值读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MCP4725的源文件。

/interface目录包含了LibDriver MCP4725与平台无关的IIC模板。

/test目录包含了LibDriver MCP4725驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MCP4725编程范例。

/doc目录包含了LibDriver MCP4725离线文档。

/datasheet目录包含了MCP4725数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC模板，完成指定平台的IIC驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/mcp4725/index.html](https://www.libdriver.com/docs/mcp4725/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。