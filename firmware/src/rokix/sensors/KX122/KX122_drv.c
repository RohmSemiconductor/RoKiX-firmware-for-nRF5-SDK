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
#include "KX122_drv.h"
#include "kx122_registers.h"

/* Driver data struct */
struct KX122_drv {
    uint8_t sad;   
};

static struct KX122_drv drv_data;

/* Platform functions passed to driver */
static struct platform_functions *platform_funcs;


/* Set platform functions */
uint8_t KX122_set_platform_functions(struct platform_functions *functions)
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
uint8_t KX122_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

    if (platform_funcs && platform_funcs->twi_read) {
        rc = platform_funcs->twi_read(sad, reg, data, size);
    }
    return rc;
}


uint8_t KX122_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

    if (platform_funcs && platform_funcs->twi_write) {
        rc = platform_funcs->twi_write(sad, reg, data, size);
    }

    return rc;
}


uint8_t KX122_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

    if (platform_funcs && platform_funcs->delay_ms) {
        rc = platform_funcs->delay_ms(ms);
    }

    return rc;
}


uint8_t KX122_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

    if (platform_funcs && platform_funcs->debug_println && str != NULL) {
        rc = platform_funcs->debug_println(str);
    }

    return rc;
}


/* KX122 reg read/write and reg bits handling */
uint8_t KX122_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KX122_plat_func_i2c_read(drv_data.sad, reg, data, size);
}


uint8_t KX122_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KX122_plat_func_i2c_write(drv_data.sad, reg, data, size);
}


uint8_t KX122_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KX122_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }

    reg_val &= ~mask;
    reg_val |= bit_pattern;

    rc = KX122_reg_write(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }
    return RC_OK;
}


uint8_t KX122_reg_set_bit(uint8_t reg, uint8_t bits)
{
    return KX122_reg_set_bit_pattern(reg, bits, 0x00);
}


uint8_t KX122_reg_reset_bit(uint8_t reg, uint8_t bits)
{
    return KX122_reg_set_bit_pattern(reg, 0x00, bits);
}


/* Debug prints */
uint8_t KX122_debug_print_line(char *str)
{
    return KX122_plat_func_debug_print_line(str);
}


void KX122_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
    char buffer[40];
    sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
    KX122_debug_print_line(buffer);
}


void KX122_debug_dump_reg(uint8_t reg)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KX122_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return;
    }

    KX122_debug_print_reg_and_val(reg, reg_val);
}


/* KX122 delay */
void KX122_delay_ms(uint16_t ms)
{
    KX122_plat_func_delay_ms(ms);
}


/* KX122 drv_data code  */
uint8_t KX122_set_CNTL1_PC1_on()
{
    uint8_t rc;
    rc = KX122_reg_set_bit(KX122_CNTL1, KX122_CNTL1_PC1);
    return rc;
}


uint8_t KX122_set_CNTL1_PC1_off()
{
    uint8_t rc;
    rc = KX122_reg_reset_bit(KX122_CNTL1, KX122_CNTL1_PC1);
    // wait at least 0.1 seconds
    KX122_delay_ms(100);
    return rc;
}


uint8_t KX122_set_odr(uint8_t ord)
{
    uint8_t rc;
    rc = KX122_reg_set_bit_pattern(KX122_ODCNTL, ord, KX122_ODCNTL_OSA_MASK);
    return rc;
}


uint8_t KX122_set_grange(uint8_t grange)
{
    uint8_t rc;

    rc = KX122_reg_set_bit_pattern(KX122_CNTL1, grange, KX122_CNTL1_GSEL_MASK);
    return rc;
}


uint8_t KX122_set_high_resolution_mode()
{    
	uint8_t rc;
	/*enable high resolution mode.*/
	rc = KX122_reg_set_bit(KX122_CNTL1, KX122_CNTL1_RES);
    return rc;
}


uint8_t KX122_sensor_soft_reset()
{
    uint8_t rc;

    rc = KX122_reg_set_bit(KX122_CNTL2, KX122_CNTL2_SRST);
    if (rc != RC_OK) {
      return rc;
    }

    KX122_delay_ms(500);

    return RC_OK;
}


uint8_t KX122_int1_configure(gpio_pin_polarity_t polarity) {

    uint8_t rc;
    rc = KX122_reg_set_bit(KX122_CNTL1, KX122_CNTL1_DRDYE);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KX122_reg_set_bit(KX122_INC4, KX122_INC4_DRDYI1);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KX122_reg_reset_bit(KX122_CNTL1, KX122_INC1_IEL1);
    if (rc != RC_OK) {
        return rc;
    }
  
    if(polarity == GPIO_POLARITY_HITOLO)
        rc = KX122_reg_reset_bit(KX122_INC1, KX122_INC1_IEA1);
    else 
        rc = KX122_reg_set_bit(KX122_INC1, KX122_INC1_IEA1);

    if (rc != RC_OK) {
        return rc;
    }

    rc = KX122_reg_set_bit(KX122_INC1, KX122_INC1_IEN1);
    if (rc != RC_OK) {
        return rc;
    }
    
    return RC_OK;
}


uint8_t KX122_start(uint8_t int_pin, gpio_pin_polarity_t polarity) {

    uint8_t rc;
    uint8_t grange = KX122_CNTL1_GSEL_2G;
    uint8_t odr = KX122_ODCNTL_OSA_6P25;

    /* Sensor must be in standby mode before configs are changed.*/
    rc = KX122_set_CNTL1_PC1_off();
    if (rc != RC_OK) {
        return rc;
    }

    /* set sensor odr.*/
    rc = KX122_set_odr(odr);
    if (rc != RC_OK) {
        return rc;
    }

    /* set sensor grange.*/
    rc = KX122_set_grange(grange);
    if (rc != RC_OK) {
        return rc;
    }

    /* set high resolution mode.*/
    rc = KX122_set_high_resolution_mode();
    if (rc != RC_OK) {
        return rc;
    }

    /*enable interrupt 1.*/
    if(int_pin == KX122_INT1) {
        rc = KX122_int1_configure(polarity);
        if (rc != RC_OK) {
          return rc;
        }
    }

    /*enable high resolution power mode.*/
    rc = KX122_set_CNTL1_PC1_on();
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KX122_init(uint8_t sad)
{
    uint8_t rc;
    uint8_t reg;

    /*platform_funcs needs to be set, or overwrite local read/write/print functions.*/
    if (platform_funcs == NULL) {
        return RC_FAIL;
    }

    drv_data.sad = sad;

    rc = KX122_reg_read(KX122_WHO_AM_I, &reg, sizeof(reg));
    if (rc != RC_OK) {
        KX122_debug_print_line("KX122_reg_read WHO_AM_I fail");
        return rc;
    }

    /*verify that we got correct wai value.*/
    if (reg != KX122_WHO_AM_I_WAI_ID) {
        KX122_debug_print_line("Incorrect WAI");
        return RC_FAIL;
    }

    /*do sensor soft reset.*/
    rc = KX122_sensor_soft_reset();
    if (rc != RC_OK) {
        KX122_debug_print_line("KX122_sensor_soft_reset fail");
        return rc;
    }

    return RC_OK;
}


uint8_t KX122_get_raw_xyz(uint8_t *xyz, uint8_t *size)
{
    uint8_t rc;

    rc = KX122_reg_read(KX122_XOUT_L, xyz, 6);
    if (rc != RC_OK) {
        KX122_debug_print_line("KX122_get_rawval fail");
        return rc;
    }
    *size = 6;
    return RC_OK;
}


uint8_t KX122_debug_dump_regs()
{

    uint8_t dump_regs[] = {
        KX122_STATUS_REG,
        KX122_CNTL2,
        KX122_ODCNTL,
    };

      uint8_t i = 0;
      uint8_t n = sizeof(dump_regs)/sizeof(dump_regs[0]);

      KX122_debug_print_line("KX122_debug_dump_regs :");
      for(i=0; i < n ; i++) {
          KX122_debug_dump_reg(dump_regs[i]);
      }

    return RC_OK;
}
