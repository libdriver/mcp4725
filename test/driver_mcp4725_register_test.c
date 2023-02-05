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
 * @file      driver_mcp4725_register_test.c
 * @brief     driver mcp4725 register test source file
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

#include "driver_mcp4725_register_test.h"
#include <math.h>

static mcp4725_handle_t gs_handle;        /**< mcp4725 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mcp4725_register_test(mcp4725_address_t addr)
{
    uint8_t res;
    float ref_voltage;
    mcp4725_mode_t mode;
    mcp4725_power_down_mode_t power_down_mode;
    mcp4725_info_t info;
    mcp4725_address_t addr_pin;
   
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
    
    /* start register */
    mcp4725_interface_debug_print("mcp4725: start register test.\n");
    
    /* mcp4725_set_addr_pin/mcp4725_get_addr_pin test */
    mcp4725_interface_debug_print("mcp4725: mcp4725_set_addr_pin/mcp4725_get_addr_pin test.\n");
    
    /* set A0_GND */
    res = mcp4725_set_addr_pin(&gs_handle, MCP4725_ADDR_A0_GND);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set addr pin failed.\n");
       
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set addr pin A0_GND.\n");
    res = mcp4725_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get addr pin failed.\n");
       
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check addr pin %s.\n", addr_pin==MCP4725_ADDR_A0_GND?"ok":"error");
    
    /* set A0_VCC */
    res = mcp4725_set_addr_pin(&gs_handle, MCP4725_ADDR_A0_VCC);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set addr pin failed.\n");
       
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set addr pin A0_VCC.\n");
    res = mcp4725_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get addr pin failed.\n");
       
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check addr pin %s.\n", addr_pin==MCP4725_ADDR_A0_VCC?"ok":"error");
    
    /* set addr pin */
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
    
    /* mcp4725_set_reference_voltage/mcp4725_get_reference_voltage */
    mcp4725_interface_debug_print("mcp4725: mcp4725_set_reference_voltage/mcp4725_get_reference_voltage test.\n");
    res = mcp4725_set_reference_voltage(&gs_handle, 3.3f);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set reference voltage failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set reference voltage 3.3v.\n");
    res = mcp4725_get_reference_voltage(&gs_handle, (float *)&ref_voltage);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get reference voltage failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check reference voltage %s.\n", fabsf(3.3f - ref_voltage) < 1e-6f ? "ok " :"error");
    
    /* mcp4725_set_mode/mcp4725_get_mode test */
    mcp4725_interface_debug_print("mcp4725: mcp4725_set_mode/mcp4725_get_mode test.\n");
    
    /* set DAC mode */
    res = mcp4725_set_mode(&gs_handle, MCP4725_MODE_DAC);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set dac mode.\n");
    res = mcp4725_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check mode %s.\n", mode==MCP4725_MODE_DAC?"ok":"error");
    
    /* set EEPROM mode */
    res = mcp4725_set_mode(&gs_handle, MCP4725_MODE_EEPROM);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set eeprom mode.\n");
    res = mcp4725_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check mode %s.\n", mode==MCP4725_MODE_EEPROM?"ok":"error");
    
    /* mcp4725_set_power_mode/mcp4725_get_power_mode */
    mcp4725_interface_debug_print("mcp4725: mcp4725_set_power_mode/mcp4725_get_power_mode test.\n");
    
    /* set power down normal */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_POWER_DOWN_MODE_NORMAL);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set normal power down.\n");
    res = mcp4725_get_power_mode(&gs_handle, &power_down_mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check power mode %s.\n", power_down_mode==MCP4725_POWER_DOWN_MODE_NORMAL?"ok":"error");
    
    /* set power down 1K */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_POWER_DOWN_MODE_1K_GND);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set 1K power down.\n");
    res = mcp4725_get_power_mode(&gs_handle, &power_down_mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check power mode %s.\n", power_down_mode==MCP4725_POWER_DOWN_MODE_1K_GND?"ok":"error");
    
    /* set power down 100K */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_POWER_DOWN_MODE_100K_GND);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set 100K power down.\n");
    res = mcp4725_get_power_mode(&gs_handle, &power_down_mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check power mode %s.\n", power_down_mode==MCP4725_POWER_DOWN_MODE_100K_GND?"ok":"error");
    
    /* set power down 500K */
    res = mcp4725_set_power_mode(&gs_handle, MCP4725_POWER_DOWN_MODE_500K_GND);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: set power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: set 500K power down.\n");
    res = mcp4725_get_power_mode(&gs_handle, &power_down_mode);
    if (res != 0)
    {
        mcp4725_interface_debug_print("mcp4725: get power mode failed.\n");
        (void)mcp4725_deinit(&gs_handle);
        
        return 1;
    }
    mcp4725_interface_debug_print("mcp4725: check power mode %s.\n", power_down_mode==MCP4725_POWER_DOWN_MODE_500K_GND?"ok":"error");
   
    /* finish register test */
    mcp4725_interface_debug_print("mcp4725: finish register test.\n");
    (void)mcp4725_deinit(&gs_handle);
    
    return 0;
}
