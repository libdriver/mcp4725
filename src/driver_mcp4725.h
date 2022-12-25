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
 * @file      driver_mcp4725.h
 * @brief     driver mcp4725 header file
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

#ifndef DRIVER_MCP4725_H
#define DRIVER_MCP4725_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mcp4725_driver mcp4725 driver function
 * @brief    mcp4725 driver modules
 * @{
 */

/**
 * @addtogroup mcp4725_base_driver
 * @{
 */

/**
 * @brief mcp4725 address enumeration definition
 */
typedef enum
{
    MCP4725_ADDR_A0_GND = 0x00,        /**< A0 pin connected to GND */
    MCP4725_ADDR_A0_VCC = 0x01,        /**< A0 pin connected to VCC */
} mcp4725_address_t;

/**
 * @brief mcp4725 mode enumeration definition
 */
typedef enum
{
    MCP4725_MODE_DAC    = 0x00,        /**< DAC mode */
    MCP4725_MODE_EEPROM = 0x03,        /**< EEPROM mode */
} mcp4725_mode_t;

/**
 * @brief mcp4725 power down enumeration definition
 */
typedef enum
{
    MCP4725_POWER_DOWN_MODE_NORMAL   = 0x00,        /**< power down normal mode */
    MCP4725_POWER_DOWN_MODE_1K_GND   = 0x01,        /**< power down 1K GND */
    MCP4725_POWER_DOWN_MODE_100K_GND = 0x02,        /**< power down 100K GND */
    MCP4725_POWER_DOWN_MODE_500K_GND = 0x03,        /**< power down 500K GND */
} mcp4725_power_down_mode_t;

/**
 * @brief mcp4725 handle structure definition
 */
typedef struct mcp4725_handle_s
{
    uint8_t iic_addr;                                                          /**< iic device address */
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
    uint8_t mode;                                                              /**< chip mode */
    uint8_t power_mode;                                                        /**< power mode */
    float ref_voltage;                                                         /**< reference voltage */
} mcp4725_handle_t;

/**
 * @brief mcp4725 information structure definition
 */
typedef struct mcp4725_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} mcp4725_info_t;

/**
 * @}
 */

/**
 * @defgroup mcp4725_link_driver mcp4725 link driver function
 * @brief    mcp4725 link driver modules
 * @ingroup  mcp4725_driver
 * @{
 */

/**
 * @brief     initialize mcp4725_handle_t structure
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] STRUCTURE is mcp4725_handle_t
 * @note      none
 */
#define DRIVER_MCP4725_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_IIC_READ_COMMAND(HANDLE, FUC)    (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an mcp4725 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_MCP4725_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup mcp4725_base_driver mcp4725 base driver function
 * @brief    mcp4725 base driver modules
 * @ingroup  mcp4725_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an mcp4725 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp4725_info(mcp4725_info_t *info);

/**
 * @brief     set the chip address pin
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] addr_pin is the A0 address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t mcp4725_set_addr_pin(mcp4725_handle_t *handle, mcp4725_address_t addr_pin);

/**
 * @brief      get the chip address pin
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *addr_pin points to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp4725_get_addr_pin(mcp4725_handle_t *handle, mcp4725_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an mcp4725 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t mcp4725_init(mcp4725_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an mcp4725 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_deinit(mcp4725_handle_t *handle);

/**
 * @brief     write the dac value
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] value is the dac value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_write(mcp4725_handle_t *handle, uint16_t value);

/**
 * @brief      read the dac value
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *value points to a dac buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_read(mcp4725_handle_t *handle, uint16_t *value);

/**
 * @brief      convert the dac value to the register data
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[in]  s is the converted dac value
 * @param[out] *reg points to a register data buffer
 * @return     status code
 *             - 0 success
 *             - 1 convert to register failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_convert_to_register(mcp4725_handle_t *handle, float s, uint16_t *reg);

/**
 * @brief      convert the register data to the dac value
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[in]  reg is the register data
 * @param[out] *s points to a converted dac value buffer
 * @return     status code
 *             - 0 success
 *             - 1 convert to data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_convert_to_data(mcp4725_handle_t *handle, uint16_t reg, float *s);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_set_mode(mcp4725_handle_t *handle, mcp4725_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_get_mode(mcp4725_handle_t *handle, mcp4725_mode_t *mode);

/**
 * @brief     set the chip power mode
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] mode is the chip power down mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_set_power_mode(mcp4725_handle_t *handle, mcp4725_power_down_mode_t mode);

/**
 * @brief      get the chip power mode
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *mode points to a chip power down mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_get_power_mode(mcp4725_handle_t *handle, mcp4725_power_down_mode_t *mode);

/**
 * @brief     set the chip reference voltage
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] ref_voltage is the chip reference voltage
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_set_reference_voltage(mcp4725_handle_t *handle, float ref_voltage);

/**
 * @brief      get the chip reference voltage
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *ref_voltage points to a chip reference voltage buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_get_reference_voltage(mcp4725_handle_t *handle, float *ref_voltage);

/**
 * @}
 */

/**
 * @defgroup mcp4725_extern_driver mcp4725 extern driver function
 * @brief    mcp4725 extern driver modules
 * @ingroup  mcp4725_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mcp4725_set_reg(mcp4725_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mcp4725_get_reg(mcp4725_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
