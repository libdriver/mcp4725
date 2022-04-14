/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-09
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/09  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_mcp4725_register_test.h"
#include "driver_mcp4725_write_test.h" 
#include "driver_mcp4725_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     mcp4725 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t mcp4725(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            mcp4725_info_t info;
            
            /* print mcp4725 info */
            mcp4725_info(&info);
            mcp4725_interface_debug_print("mcp4725: chip is %s.\n", info.chip_name);
            mcp4725_interface_debug_print("mcp4725: manufacturer is %s.\n", info.manufacturer_name);
            mcp4725_interface_debug_print("mcp4725: interface is %s.\n", info.interface);
            mcp4725_interface_debug_print("mcp4725: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            mcp4725_interface_debug_print("mcp4725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            mcp4725_interface_debug_print("mcp4725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            mcp4725_interface_debug_print("mcp4725: max current is %0.2fmA.\n", info.max_current_ma);
            mcp4725_interface_debug_print("mcp4725: max temperature is %0.1fC.\n", info.temperature_max);
            mcp4725_interface_debug_print("mcp4725: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            mcp4725_interface_debug_print("mcp4725: SCL connected to GPIOB PIN8.\n");
            mcp4725_interface_debug_print("mcp4725: SDA connected to GPIOB PIN9.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show mcp4725 help */

            help:
            
            mcp4725_interface_debug_print("mcp4725 -i\n\tshow mcp4725 chip and driver information.\n");
            mcp4725_interface_debug_print("mcp4725 -h\n\tshow mcp4725 help.\n");
            mcp4725_interface_debug_print("mcp4725 -p\n\tshow mcp4725 pin connections of the current board.\n");
            mcp4725_interface_debug_print("mcp4725 -t reg -a (VCC | GND)\n\trun mcp4725 register test.\n");
            mcp4725_interface_debug_print("mcp4725 -t write <dac> -a (VCC | GND)\n\trun mcp4725 write test.dac means dac value.\n");
            mcp4725_interface_debug_print("mcp4725 -c write <dac> -a (VCC | GND)\n\trun mcp4725 write function.dac means dac value.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                mcp4725_address_t addr;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("VCC", argv[4]) == 0)
                {
                    addr = MCP4725_ADDR_A0_VCC;
                }
                else if (strcmp("GND", argv[4]) == 0)
                {
                    addr = MCP4725_ADDR_A0_GND;
                }
                else
                {
                    return 5;
                }
                /* run reg test */
                if (mcp4725_register_test(addr) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* write test */
            if (strcmp("write", argv[2]) == 0)
            {
                mcp4725_address_t addr;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = MCP4725_ADDR_A0_VCC;
                }
                else if (strcmp("GND", argv[5]) == 0)
                {
                    addr = MCP4725_ADDR_A0_GND;
                }
                else
                {
                    return 5;
                }
                /* run write test */
                if (mcp4725_write_test(addr, atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* write function */
            if (strcmp("write", argv[2]) == 0)
            {
                uint8_t res;
                mcp4725_address_t addr;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = MCP4725_ADDR_A0_VCC;
                }
                else if (strcmp("GND", argv[5]) == 0)
                {
                    addr = MCP4725_ADDR_A0_GND;
                }
                else
                {
                    return 5;
                }
                
                res = mcp4725_basic_init(addr);
                if (res != 0)
                {
                    return 1;
                }
                mcp4725_interface_debug_print("mcp4725: write %0.3f.\n", (float)(atof(argv[3])));
                res = mcp4725_basic_write((float)(atof(argv[3])));
                if (res != 0)
                {
                    mcp4725_interface_debug_print("mcp4725: write failed.\n");
                    (void)mcp4725_basic_deinit();
                    
                    return 1;
                }
                (void)mcp4725_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register mcp4725 fuction */
    shell_init();
    shell_register("mcp4725", mcp4725);
    uart1_print("mcp4725: welcome to libdriver mcp4725.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("mcp4725: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("mcp4725: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("mcp4725: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("mcp4725: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("mcp4725: param is invalid.\n");
            }
            else
            {
                uart1_print("mcp4725: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
