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
 * @file      driver_mcp4725_write_test.c
 * @brief     driver mcp4725 write test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-09
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/09  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_mcp4725_write_test.h"
#include <stdlib.h>

static mcp4725_handle_t gs_handle;        /**< mcp4725 handle */

/**
 * @brief     write test
 * @param[in] addr is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mcp4725_write_test(mcp4725_address_t addr, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    float input;
    uint16_t reg, value;
    mcp4725_info_t info;
    
    /* link interface function */
    DRIVER_MCP4725_LINK_INIT(&gs_handle, mcp4725_handle_t);
    DRIVER_MCP4725_LINK_IIC_INIT(&gs_handle, mcp4725_interface_iic_init);
    DRIVER_MCP4725_LINK_IIC_DEINIT(&gs_handle, mcp4725_interface_iic_deinit);
    DRIVER_MCP4725_LINK_IIC_READ_COMMAND(&gs_handle, mcp4725_interface_iic_read_cmd);
    DRIVER_MCP4725_LINK_IIC_WRITE_COMMAND(&gs_handle, mcp4725_interface_iic_write_cmd);
    DRIVER_MCP4725_LINK_DELAY_MS(&gs_handle, mcp4725_interface_delay_ms);
    DRIVER_MCP4725_LINK_DEBUG_PRINT(&gs_handle, mcp4725_interface_debug_print);

    /* get mcp4725 information */
    res = mcp4725_info(&info);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        mcp4725_interface_debug_print("mcp4725: chip is %s.\n", info.chip_name);
        mcp4725_interface_debug_print("mcp4725: manufacturer is %s.\n", info.manufacturer_name);
        mcp4725_interface_debug_print("mcp4725: interface is %s.\n", info.interface);
        mcp4725_interface_debug_print("mcp4725: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mcp4725_interface_debug_print("mcp4725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mcp4725_interface_debug_print("mcp4725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mcp4725_interface_debug_print("mcp4725: max current is %0.2fmA.\n", info.max_current_ma);
        mcp4725_interface_debug_print("mcp4725: max temperature is %0.1fC.\n", info.temperature_max);
        mcp4725_interface_debug_print("mcp4725: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start write test */
    mcp4725_interface_debug_print("mcp4725: start write test.\n");
    
    /* set iic addr */
    res = mcp4725_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set addr pin failed.\n");
       
        return 1;
    }
    
    /* mcp4725 init */
    res = mcp4725_init(&gs_handle);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: init failed.\n");
       
        return 1;
    }
    
    /* set power down normal mode */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_POWER_DOWN_MODE_NORMAL);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set reference voltage 3.3V */
    res = mcp4725_set_reference_voltage(&gs_handle, 3.3f);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set reference voltage failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set dac mode */
    res = mcp4725_set_mode(&gs_handle, MCP4725_MODE_DAC);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set dac mode.\n"); 
    for (i=0; i<times; i++)
    {
        input = (float)(rand()%65536)/65536.0f*3.3f; 
    
        /* convert to register */
        res = mcp4725_convert_to_register(&gs_handle, input, (uint16_t *)&reg);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: convert to register failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }

        /* write dac */
        res = mcp4725_write(&gs_handle, (uint16_t)reg);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: write data failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }
        mcp4725_interface_delay_ms(1000);
        res = mcp4725_read(&gs_handle, (uint16_t *)&value);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: read data failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }
        mcp4725_interface_debug_print("mcp4725: dac read check %s write %0.4fv\n", reg==value?"ok":"error", input);
        mcp4725_interface_delay_ms(1000);
    }

    /* set mode eeprom mode */
    mcp4725_interface_debug_print("mcp4725: set eeprom mode.\n"); 
    res = mcp4725_set_mode(&gs_handle, MCP4725_MODE_EEPROM);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    for (i=0; i<times; i++)
    {
        input = (float)(rand()%65536)/65536.0f*3.3f;

        /* convert to register */
        res = mcp4725_convert_to_register(&gs_handle, input, (uint16_t *)&reg);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: convert to register failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }

        /* write dac */
        res = mcp4725_write(&gs_handle, (uint16_t)reg);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: write data failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }
        mcp4725_interface_delay_ms(1000);
        res = mcp4725_read(&gs_handle, (uint16_t *)&value);
        if (res != 0)
        {
            mcp4725_interface_debug_print("mcp4725: read data failed.\n");
            (void)mcp4725_deinit(&gs_handle);
            
            return 1;
        }
        mcp4725_interface_debug_print("mcp4725: eeprom read check %s write %0.4fv\n", reg==value?"ok":"error", input);
        mcp4725_interface_delay_ms(1000);
    }

    /* finish write test */
    mcp4725_interface_debug_print("mcp4725: finish write test.\n");
    (void)mcp4725_deinit(&gs_handle);
    
    return 0;
}
