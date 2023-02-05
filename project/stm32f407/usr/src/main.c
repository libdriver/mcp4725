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
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     mcp4725 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t mcp4725(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"dac", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    float vol = 0.0f;
    uint8_t vol_flag = 0;
    mcp4725_address_t addr = MCP4725_ADDR_A0_GND;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr */
                if (strcmp("0", optarg) == 0)
                {
                    addr = MCP4725_ADDR_A0_GND;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = MCP4725_ADDR_A0_VCC;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* dac */
            case 2 :
            {
                /* set the dac value */
                vol = atof(optarg);
                vol_flag = 1;
                
                break;
            } 
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
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
    else if (strcmp("t_write", type) == 0)
    {
        /* run write test */
        if (mcp4725_write_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if (vol_flag != 1)
        {
            return 5;
        }
        
        /* basic init */
        res = mcp4725_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        mcp4725_interface_debug_print("mcp4725: write %0.3f.\n", vol);
        
        /* write dac */
        res = mcp4725_basic_write(vol);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: write failed.\n");
            (void)mcp4725_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)mcp4725_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        mcp4725_interface_debug_print("Usage:\n");
        mcp4725_interface_debug_print("  mcp4725 (-i | --information)\n");
        mcp4725_interface_debug_print("  mcp4725 (-h | --help)\n");
        mcp4725_interface_debug_print("  mcp4725 (-p | --port)\n");
        mcp4725_interface_debug_print("  mcp4725 (-t reg | --test=reg) [--addr=<0 | 1>]\n");
        mcp4725_interface_debug_print("  mcp4725 (-t write | --test=write) [--addr=<0 | 1>] [--times=<num>]\n");
        mcp4725_interface_debug_print("  mcp4725 (-e write | --example=write) [--addr=<0 | 1>] --dac=<voltage>\n");
        mcp4725_interface_debug_print("\n");
        mcp4725_interface_debug_print("Options:\n");
        mcp4725_interface_debug_print("      --addr=<0 | 1>               Set the addr pin.([default: 0])\n");
        mcp4725_interface_debug_print("      --dac=<voltage>              Set the dac output in voltage.\n");
        mcp4725_interface_debug_print("  -e <write>, --example=<write>    Run the driver example.\n");
        mcp4725_interface_debug_print("  -h, --help                       Show the help.\n");
        mcp4725_interface_debug_print("  -i, --information                Show the chip information.\n");
        mcp4725_interface_debug_print("  -p, --port                       Display the pin connections of the current board.\n");
        mcp4725_interface_debug_print("  -t <reg | write>, --test=<reg | write>\n");
        mcp4725_interface_debug_print("                                   Run the driver test.\n");
        mcp4725_interface_debug_print("      --times=<num>                Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        mcp4725_info_t info;
        
        /* print mcp4725 info */
        mcp4725_info(&info);
        mcp4725_interface_debug_print("mcp4725: chip is %s.\n", info.chip_name);
        mcp4725_interface_debug_print("mcp4725: manufacturer is %s.\n", info.manufacturer_name);
        mcp4725_interface_debug_print("mcp4725: interface is %s.\n", info.interface);
        mcp4725_interface_debug_print("mcp4725: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mcp4725_interface_debug_print("mcp4725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mcp4725_interface_debug_print("mcp4725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mcp4725_interface_debug_print("mcp4725: max current is %0.2fmA.\n", info.max_current_ma);
        mcp4725_interface_debug_print("mcp4725: max temperature is %0.1fC.\n", info.temperature_max);
        mcp4725_interface_debug_print("mcp4725: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        mcp4725_interface_debug_print("mcp4725: SCL connected to GPIOB PIN8.\n");
        mcp4725_interface_debug_print("mcp4725: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
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
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register mcp4725 function */
    shell_init();
    shell_register("mcp4725", mcp4725);
    uart_print("mcp4725: welcome to libdriver mcp4725.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("mcp4725: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("mcp4725: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("mcp4725: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("mcp4725: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("mcp4725: param is invalid.\n");
            }
            else
            {
                uart_print("mcp4725: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
