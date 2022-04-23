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
 * @file      driver_mcp4725_basic.c
 * @brief     driver mcp4725 basic source file
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

#include "driver_mcp4725_basic.h"

static mcp4725_handle_t gs_handle;        /**< mcp4725 handle */

/**
 * @brief     basic example init
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mcp4725_basic_init(mcp4725_address_t addr_pin)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_MCP4725_LINK_INIT(&gs_handle, mcp4725_handle_t);
    DRIVER_MCP4725_LINK_IIC_INIT(&gs_handle, mcp4725_interface_iic_init);
    DRIVER_MCP4725_LINK_IIC_DEINIT(&gs_handle, mcp4725_interface_iic_deinit);
    DRIVER_MCP4725_LINK_IIC_READ_COMMAND(&gs_handle, mcp4725_interface_iic_read_cmd);
    DRIVER_MCP4725_LINK_IIC_WRITE_COMMAND(&gs_handle, mcp4725_interface_iic_write_cmd);
    DRIVER_MCP4725_LINK_DELAY_MS(&gs_handle, mcp4725_interface_delay_ms);
    DRIVER_MCP4725_LINK_DEBUG_PRINT(&gs_handle, mcp4725_interface_debug_print);
    
    /* set iic addr pin */
    res = mcp4725_set_addr_pin(&gs_handle, addr_pin);
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
    
    /* set power mode */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_BASIC_DEFAULT_POWER_DOWN_MODE);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set mode */
    res = mcp4725_set_mode(&gs_handle, MCP4725_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set reference voltage */
    res = mcp4725_set_reference_voltage(&gs_handle, MCP4725_BASIC_DEFAULT_REFERENCE_VOLTAGE);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set reference voltage failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write
 * @param[in] voltage_v is the dac value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t mcp4725_basic_write(float voltage_v)
{
    uint16_t value;
    uint8_t res; 
    
    /* convert voltage to register */
    res = mcp4725_convert_to_register(&gs_handle, voltage_v, (uint16_t *)&value);
    if (res != 0)
    {
        return 1;
    }
    
    /* write voltage */
    if (mcp4725_write(&gs_handle, (uint16_t)value) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mcp4725_basic_deinit(void)
{
    /* close mcp4725 */
    if (mcp4725_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
