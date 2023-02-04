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
 * @file      driver_mcp4725.c
 * @brief     driver mcp4725 source file
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

#include "driver_mcp4725.h"
#include <math.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Microchip MCP4725"        /**< chip name */
#define MANUFACTURER_NAME         "Microchip"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                       /**< chip max supply voltage */
#define MAX_CURRENT               0.4f                       /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                     /**< chip max operating temperature */
#define DRIVER_VERSION            2000                       /**< driver version */

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
uint8_t mcp4725_init(mcp4725_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->iic_init == NULL)                                        /* check iic_init */
    {
        handle->debug_print("mcp4725: iic_init is null.\n");             /* iic_init is null */
        
        return 3;                                                        /* return error */
    }
    if (handle->iic_deinit == NULL)                                      /* check iic_deinit */
    {
        handle->debug_print("mcp4725: iic_deinit is null.\n");           /* iic_deinit is null */
        
        return 3;                                                        /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                    /* check iic_read_cmd */
    {
        handle->debug_print("mcp4725: iic_read_cmd is null.\n");         /* iic_read is null */
        
        return 3;                                                        /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                   /* check iic_write_cmd */
    {
        handle->debug_print("mcp4725: iic_write_cmd is null.\n");        /* iic_write_cmd is null */
        
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("mcp4725: delay_ms is null.\n");             /* delay_ms is null */
        
        return 3;                                                        /* return error */
    }
    
    if (handle->iic_init() != 0)                                         /* iic init */
    {
        handle->debug_print("mcp4725: iic init failed.\n");              /* iic init failed */
        
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t mcp4725_deinit(mcp4725_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                   /* iic deinit */
    {
        handle->debug_print("mcp4725: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                    /* return error */
    }   
    handle->inited = 0;                                              /* flag close */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set the chip address pin
 * @param[in] *handle points to an mcp4725 handle structure
 * @param[in] addr_pin is the A0 address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t mcp4725_set_addr_pin(mcp4725_handle_t *handle, mcp4725_address_t addr_pin)
{
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    
    handle->iic_addr = (uint8_t)((0x60 | addr_pin) << 1);        /* set iic address */
    
    return 0;                                                    /* success return 0 */
}

/**
 * @brief      get the chip address pin
 * @param[in]  *handle points to an mcp4725 handle structure
 * @param[out] *addr_pin points to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp4725_get_addr_pin(mcp4725_handle_t *handle, mcp4725_address_t *addr_pin)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    
    if (((handle->iic_addr >> 1) & ~0x60) != 0)
    {
        *addr_pin = (mcp4725_address_t)(0x01);        /* get iic address */
    }
    else
    {
        *addr_pin = (mcp4725_address_t)(0x00);        /* get iic address */
    }
    
    return 0;                                         /* success return 0 */
}

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
uint8_t mcp4725_set_mode(mcp4725_handle_t *handle, mcp4725_mode_t mode)
{
    if (handle == NULL)                  /* check handle */
    {
        return 2;                        /* return error */
    }
    if (handle->inited != 1)             /* check handle initialization */
    {
        return 3;                        /* return error */
    }
    
    handle->mode = (uint8_t)mode;        /* set mode */

    return 0;                            /* success return 0 */
}

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
uint8_t mcp4725_get_mode(mcp4725_handle_t *handle, mcp4725_mode_t *mode)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    *mode = (mcp4725_mode_t)(handle->mode);        /* get mode */
    
    return 0;                                      /* success return 0 */
}

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
uint8_t mcp4725_set_power_mode(mcp4725_handle_t *handle, mcp4725_power_down_mode_t mode)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    handle->power_mode = (uint8_t)mode;        /* set power mode */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t mcp4725_get_power_mode(mcp4725_handle_t *handle, mcp4725_power_down_mode_t *mode)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    *mode = (mcp4725_power_down_mode_t)(handle->power_mode);        /* get power mode */
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t mcp4725_set_reference_voltage(mcp4725_handle_t *handle, float ref_voltage)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->ref_voltage = ref_voltage;        /* set reference voltage */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t mcp4725_get_reference_voltage(mcp4725_handle_t *handle, float *ref_voltage)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    if (handle->inited != 1)                   /* check handle initialization */
    {
        return 3;                              /* return error */
    }
    
    *ref_voltage = handle->ref_voltage;        /* get reference voltage */
    
    return 0;                                  /* success return 0 */
}

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
uint8_t mcp4725_read(mcp4725_handle_t *handle, uint16_t *value)
{
    uint8_t buf[5];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    if (handle->iic_read_cmd(handle->iic_addr, (uint8_t *)buf, 5) != 0)   /* read data */
    {
        handle->debug_print("mcp4725: read failed.\n");                   /* read data failed */
        
        return 1;                                                         /* return error */
    }
    if (handle->mode == MCP4725_MODE_DAC)                                 /* if use dac mode */
    {
        *value = (uint16_t)(((uint16_t)buf[1]) << 8 | buf[2]);            /* get value */
        *value = (*value) >> 4;                                           /* right shift 4 */
        
        return 0;                                                         /* success return 0 */
    }
    else if (handle->mode == MCP4725_MODE_EEPROM)                         /* if use eeprom mode */
    {
        *value = (uint16_t)((uint16_t)(buf[3] & 0x0F) << 8 | buf[4]);     /* get value */
        
        return 0;                                                         /* success return 0 */
    }
    else
    {
        handle->debug_print("mcp4725: mode is invalid.\n");               /* mode is invalid */
        
        return 1;                                                         /* return error */
    }
} 

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
uint8_t mcp4725_write(mcp4725_handle_t *handle, uint16_t value)
{
    uint8_t buf[6];
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    value = value & 0xFFF;                                                        /* get valid part */
    if (handle->mode == MCP4725_MODE_DAC)                                         /* dac mode */
    {
        buf[0] = (uint8_t)((value >> 8) & 0xFF);                                  /* set msb */
        buf[0] = (uint8_t)(buf[0] | (handle->power_mode << 4));                   /* set power mode */
        buf[1] = (uint8_t)(value & 0xFF);                                         /* set lsb */
        buf[2] = (uint8_t)((value >> 8) & 0xFF);                                  /* set msb */
        buf[2] = (uint8_t)(buf[2] | (handle->power_mode << 4));                   /* set power mode */
        buf[3] = (uint8_t)(value & 0xFF);                                         /* set lsb */
        
        return handle->iic_write_cmd(handle->iic_addr, (uint8_t *)buf, 4);        /* write command */
    }
    else if (handle->mode == MCP4725_MODE_EEPROM)                                 /* eeprom mode */
    {
        buf[0] = (uint8_t)(0x03 << 5);                                            /* set mode */
        buf[0] = (uint8_t)(buf[0] | (handle->power_mode << 1));                   /* set power mode */
        value = value << 4;                                                       /* right shift 4 */
        buf[1] = (uint8_t)((value >> 8) & 0xFF);                                  /* set msb */
        buf[2] = (uint8_t)(value & 0xFF);                                         /* set lsb */
        buf[3] = (uint8_t)(0x03 << 5);                                            /* set mode */
        buf[3] = (uint8_t)(buf[3] | (handle->power_mode << 1));                   /* set power mode */
        value = value << 4;                                                       /* right shift 4 */
        buf[4] = (uint8_t)((value >> 8) & 0xFF);                                  /* set msb */
        buf[5] = (uint8_t)(value & 0xFF);                                         /* set lsb */
        
        return handle->iic_write_cmd(handle->iic_addr, (uint8_t *)buf, 6);        /* write command */
    }
    else
    {
        handle->debug_print("mcp4725: mode is invalid.\n");                       /* mode is invalid */
        
        return 1;                                                                 /* return error */
    }
}

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
uint8_t mcp4725_convert_to_register(mcp4725_handle_t *handle, float s, uint16_t *reg)
{
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    if (fabsf(handle->ref_voltage - 0.0f) < 1e-6f)                                 /* check reference voltage */ 
    {
        handle->debug_print("mcp4725: reference voltage can't be zero.\n");        /* reference voltage can't be zero */
        
        return 1;                                                                  /* return error */
    }
    *reg = (uint16_t)(s * 4096.0000000f / handle->ref_voltage);                    /* calculate register */
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t mcp4725_convert_to_data(mcp4725_handle_t *handle, uint16_t reg, float *s)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    *s = (float)(reg) * handle->ref_voltage / 4096.00000000f;        /* calculate data */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t mcp4725_set_reg(mcp4725_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    return handle->iic_write_cmd(handle->iic_addr, buf, len);        /* write data */
}

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
uint8_t mcp4725_get_reg(mcp4725_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    return handle->iic_read_cmd(handle->iic_addr, buf, len);        /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an mcp4725 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mcp4725_info(mcp4725_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(mcp4725_info_t));                        /* initialize mcp4725 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
