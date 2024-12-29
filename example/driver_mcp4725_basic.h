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
 * @file      driver_mcp4725_basic.h
 * @brief     driver mcp4725 basic header file
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

#ifndef DRIVER_MCP4725_BASIC_H
#define DRIVER_MCP4725_BASIC_H

#include "driver_mcp4725_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief mcp4725 basic example default definition
 */
#define MCP4725_BASIC_DEFAULT_POWER_DOWN_MODE     MCP4725_POWER_DOWN_MODE_NORMAL        /**< normal power down */
#define MCP4725_BASIC_DEFAULT_MODE                MCP4725_MODE_DAC                      /**< normal mode */
#define MCP4725_BASIC_DEFAULT_REFERENCE_VOLTAGE   3.3f                                  /**< 3.3v reference voltage */

/**
 * @defgroup mcp4725_example_driver mcp4725 example driver function
 * @brief    mcp4725 example driver modules
 * @ingroup  mcp4725_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mcp4725_basic_init(mcp4725_address_t addr_pin);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mcp4725_basic_deinit(void);

/**
 * @brief     basic example write
 * @param[in] voltage_v dac value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t mcp4725_basic_write(float voltage_v);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
