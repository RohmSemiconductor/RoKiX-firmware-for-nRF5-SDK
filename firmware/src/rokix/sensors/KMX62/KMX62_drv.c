/*
The MIT License (MIT)
Copyright (c) 2019 Kionix Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <stdio.h> 
#include <stddef.h>
#include <stdint.h>

#include "sensors.h"
#include "KMX62_drv.h"
// KMX62_registers -> kmx62_registers.h
#include "kmx62_registers.h"


/* Driver data struct */
struct KMX62_drv {
    uint8_t sad;
};

static struct KMX62_drv drv_data;

/* Platform functions passed to driver */
static struct platform_functions *platform_funcs;


/* Set platform functions */
uint8_t KMX62_set_platform_functions(struct platform_functions *functions)
{
    if (functions == NULL ||
          functions->twi_read == NULL ||
            functions->twi_write == NULL ) {
        return RC_FAIL;
    }
    platform_funcs = functions;
    return RC_OK;
}


/* Wrapper to platform functions */
uint8_t KMX62_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

    if (platform_funcs && platform_funcs->twi_read) {
        rc = platform_funcs->twi_read(sad, reg, data, size);
    }
    return rc;
}


uint8_t KMX62_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

    if (platform_funcs && platform_funcs->twi_write) {
        rc = platform_funcs->twi_write(sad, reg, data, size);
    }

    return rc;
}


uint8_t KMX62_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

    if (platform_funcs && platform_funcs->delay_ms) {
        rc = platform_funcs->delay_ms(ms);
    }

    return rc;
}


uint8_t KMX62_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

    if (platform_funcs && platform_funcs->debug_println && str != NULL) {
        rc = platform_funcs->debug_println(str);
    }

    return rc;
}


/* KMX62 reg read/write and reg bits handling */
uint8_t KMX62_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KMX62_plat_func_i2c_read(drv_data.sad, reg, data, size);
}


uint8_t KMX62_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KMX62_plat_func_i2c_write(drv_data.sad, reg, data, size);
}


uint8_t KMX62_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KMX62_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }

    reg_val &= ~mask;
    reg_val |= bit_pattern;

    rc = KMX62_reg_write(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }
    return RC_OK;
}


uint8_t KMX62_reg_set_bit(uint8_t reg, uint8_t bits)
{
    return KMX62_reg_set_bit_pattern(reg, bits, 0x00);
}


uint8_t KMX62_reg_reset_bit(uint8_t reg, uint8_t bits)
{
    return KMX62_reg_set_bit_pattern(reg, 0x00, bits);
}


/* Debug prints */
uint8_t KMX62_debug_print_line(char *str)
{
    return KMX62_plat_func_debug_print_line(str);
}


void KMX62_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
    char buffer[40];
    sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
    KMX62_debug_print_line(buffer);
}


void KMX62_debug_dump_reg(uint8_t reg)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KMX62_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return;
    }

    KMX62_debug_print_reg_and_val(reg, reg_val);
}


/* KMX62 delay */
void KMX62_delay_ms(uint16_t ms)
{
    KMX62_plat_func_delay_ms(ms);
}


/* KMX62 drv_data code  */
uint8_t KMX62_power_on()
{
    uint8_t rc;

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_ACCEL_EN_OPERATING_MODE, 
                                   KMX62_CNTL2_ACCEL_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    KMX62_delay_ms(100);

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_MAG_EN_OPERATING_MODE, 
                                   KMX62_CNTL2_MAG_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_TEMP_EN_OPERATING_MODE, 
                                   KMX62_CNTL2_TEMP_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KMX62_power_off()
{
    uint8_t rc;

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_ACCEL_EN_STANDBY_MODE, 
                                   KMX62_CNTL2_ACCEL_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_MAG_EN_STANDBY_MODE, 
                                   KMX62_CNTL2_MAG_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2, 
                                   KMX62_CNTL2_TEMP_EN_STANDBY_MODE, 
                                   KMX62_CNTL2_TEMP_EN_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    
    return RC_OK;
}

/* sets odr to both acc and mag.*/
uint8_t KMX62_set_odr()
{
    uint8_t rc;

    rc = KMX62_reg_set_bit_pattern(KMX62_ODCNTL, 
                                   KMX62_ODCNTL_OSA_6P25, 
                                   KMX62_ODCNTL_OSA_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KMX62_reg_set_bit_pattern(KMX62_ODCNTL, 
                                   KMX62_ODCNTL_OSM_6P25, 
                                   KMX62_ODCNTL_OSM_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    
    return RC_OK;
}


uint8_t KMX62_set_grange()
{
    uint8_t rc;

    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2,
                                   KMX62_CNTL2_GSEL_2G,
                                   KMX62_CNTL2_GSEL_MASK);
    if (rc != RC_OK) {
         return rc;
    }

    return RC_OK;
}


uint8_t KMX62_set_high_resolution_mode()
{    
    uint8_t rc;
    rc = KMX62_reg_set_bit_pattern(KMX62_CNTL2,
                                   KMX62_CNTL2_RES_MAX2,
                                   KMX62_CNTL2_RES_MASK);
    if (rc != RC_OK) {
         return rc;
    }

    return RC_OK;
}


uint8_t KMX62_sensor_soft_reset()
{
    uint8_t rc;

    rc = KMX62_reg_set_bit(KMX62_CNTL1, KMX62_CNTL1_SRST);
    if (rc != RC_OK) {
      return rc;
    }

    KMX62_delay_ms(500);

    return RC_OK;
}


uint8_t KMX62_int1_configure(gpio_pin_polarity_t polarity) {

    uint8_t rc;
    uint8_t regval;
    rc = KMX62_reg_set_bit(KMX62_INC1, KMX62_INC1_DRDY_A1);
    if (rc != RC_OK) {
        return rc;
    }
  
    if(polarity == GPIO_POLARITY_HITOLO) {
        regval = KMX62_INC3_IEL1_LATCHED | KMX62_INC3_IEA1_LOW;
        rc = KMX62_reg_write(KMX62_INC3,&regval, 1);
    } else {
        regval = KMX62_INC3_IEL1_LATCHED | KMX62_INC3_IEA1_HIGH;
        rc = KMX62_reg_write(KMX62_INC3,&regval, 1);
    }

    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KMX62_start(uint8_t int_pin, gpio_pin_polarity_t polarity) {

    uint8_t rc;
    
    /* Sensor must be in standby mode before configs are changed.*/
    rc = KMX62_power_off();
    if (rc != RC_OK) {
        return rc;
    }

    /* set sensor odr.*/
    rc = KMX62_set_odr();
    if (rc != RC_OK) {
        return rc;
    }

    /* set sensor grange.*/
    rc = KMX62_set_grange();
    if (rc != RC_OK) {
        return rc;
    }

    /* set high resolution mode.*/
    rc = KMX62_set_high_resolution_mode();
    if (rc != RC_OK) {
        return rc;
    }

    /*enable interrupt 1.*/
    if(int_pin == KMX62_INT1) {
        rc = KMX62_int1_configure(polarity);
        if (rc != RC_OK) {
          return rc;
        }
    }

    /*enable high resolution power mode.*/
    rc = KMX62_power_on();
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KMX62_init(uint8_t sad)
{
    uint8_t rc;
    uint8_t reg;

    /*platform_funcs needs to be set, or overwrite local read/write/print functions.*/
    if (platform_funcs == NULL) {
        return RC_FAIL;
    }

    drv_data.sad = sad;

    rc = KMX62_reg_read(KMX62_WHO_AM_I, &reg, sizeof(reg));
    if (rc != RC_OK) {
        KMX62_debug_print_line("KMX62_reg_read WHO_AM_I fail");
        return rc;
    }

    /*verify that we got correct wai value.*/
    if (reg != KMX62_WHO_AM_I_WIA_ID) {
        KMX62_debug_print_line("Incorrect WAI");
        return RC_FAIL;
    }

    /*do sensor soft reset.*/
    rc = KMX62_sensor_soft_reset();
    if (rc != RC_OK) {
        KMX62_debug_print_line("KMX62_sensor_soft_reset fail");
        return rc;
    }

    return RC_OK;
}


uint8_t KMX62_get_raw_xyz(uint8_t *xyz, uint8_t *size)
{
    uint8_t rc;

    rc = KMX62_reg_read(KMX62_ACCEL_XOUT_L, xyz, 14);
    if (rc != RC_OK) {
        KMX62_debug_print_line("KMX62_get_rawval fail");
        return rc;
    }
    *size = 14;
    return RC_OK;
}


uint8_t KMX62_debug_dump_regs()
{
/*
    uint8_t dump_regs[] = {
        KMX62_CNTL2,
    };

    uint8_t i = 0;
    uint8_t n = sizeof(dump_regs)/sizeof(dump_regs[0]);

    KMX62_debug_print_line("KMX62_debug_dump_regs :");
    for(i=0; i < n ; i++) {
      KMX62_debug_dump_reg(dump_regs[i]);
    }
*/
    return RC_OK;
}
