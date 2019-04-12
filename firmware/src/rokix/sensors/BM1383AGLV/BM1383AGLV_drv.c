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
#include "BM1383AGLV_drv.h"
#include "bm1383aglv_registers.h"


/* Driver data struct */
struct BM1383AGLV_drv {
    uint8_t sad;
};

static struct BM1383AGLV_drv drv_data;

/* Platform functions passed to driver */
static struct platform_functions *platform_funcs;


/* Set plafrom functions */
uint8_t BM1383AGLV_set_platform_functions(struct platform_functions *functions)
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
uint8_t BM1383AGLV_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

    if (platform_funcs && platform_funcs->twi_read) {
        rc = platform_funcs->twi_read(sad, reg, data, size);
    }
    return rc;
}


uint8_t BM1383AGLV_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

    if (platform_funcs && platform_funcs->twi_write) {
        rc = platform_funcs->twi_write(sad, reg, data, size);
    }

    return rc;
}


uint8_t BM1383AGLV_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

    if (platform_funcs && platform_funcs->delay_ms) {
        rc = platform_funcs->delay_ms(ms);
    }

    return rc;
}


uint8_t BM1383AGLV_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

    if (platform_funcs && platform_funcs->debug_println && str != NULL) {
        rc = platform_funcs->debug_println(str);
    }

    return rc;
}


/* BM1383AGLV reg read/write and reg bits handling */
uint8_t BM1383AGLV_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return BM1383AGLV_plat_func_i2c_read(drv_data.sad, reg, data, size);
}


uint8_t BM1383AGLV_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return BM1383AGLV_plat_func_i2c_write(drv_data.sad, reg, data, size);
}


uint8_t BM1383AGLV_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = BM1383AGLV_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }

    reg_val &= ~mask;
    reg_val |= bit_pattern;

    rc = BM1383AGLV_reg_write(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }
    return RC_OK;
}


uint8_t BM1383AGLV_reg_set_bit(uint8_t reg, uint8_t bits)
{
    return BM1383AGLV_reg_set_bit_pattern(reg, bits, 0x00);
}


uint8_t BM1383AGLV_reg_reset_bit(uint8_t reg, uint8_t bits)
{
    return BM1383AGLV_reg_set_bit_pattern(reg, 0x00, bits);
}


/* Debug prints */
uint8_t BM1383AGLV_debug_print_line(char *str)
{
    return BM1383AGLV_plat_func_debug_print_line(str);
}


void BM1383AGLV_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
    char buffer[40];
    sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
    BM1383AGLV_debug_print_line(buffer);
}


void BM1383AGLV_debug_dump_reg(uint8_t reg)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = BM1383AGLV_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return;
    }

    BM1383AGLV_debug_print_reg_and_val(reg, reg_val);
}


/* BM1383AGLV delay */
void BM1383AGLV_delay_ms(uint16_t ms)
{
    BM1383AGLV_plat_func_delay_ms(ms);
}


/* BM1383AGLV drv_data code  */
uint8_t BM1383AGLV_power_on()
{
    uint8_t rc;
    uint8_t reg;

    BM1383AGLV_delay_ms(100);

    reg = BM1383AGLV_POWER_REG_POWER_UP;
    rc = BM1383AGLV_reg_write(BM1383AGLV_POWER_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        return rc;
    }
    
    BM1383AGLV_delay_ms(2);

    reg = BM1383AGLV_RESET_REG_MODE_STANDBY;
    rc = BM1383AGLV_reg_write(BM1383AGLV_RESET_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t BM1383AGLV_power_off()
{
    uint8_t rc;

    rc = BM1383AGLV_reg_set_bit_pattern(BM1383AGLV_MODE_CONTROL_REG,
                                   BM1383AGLV_MODE_CONTROL_REG_MODE_STANDBY,
                                   BM1383AGLV_MODE_CONTROL_REG_MODE_MASK);
    if (rc != RC_OK) {
        return rc;
    }
        
    return RC_OK;
}

uint8_t BM1383AGLV_shutdown()
{
    uint8_t rc;
    uint8_t reg;

    reg = BM1383AGLV_RESET_REG_MODE_RESET;
    rc = BM1383AGLV_reg_write(BM1383AGLV_ID1_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("Read BM1383AGLV_ID1_REG fail");
        return rc;
    }

    reg = BM1383AGLV_POWER_REG_POWER_DOWN;
    rc = BM1383AGLV_reg_write(BM1383AGLV_POWER_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("Read BM1383AGLV_ID1_REG fail");
        return rc;
    }        
    return RC_OK;
}

uint8_t BM1383AGLV_set_odr()
{
    uint8_t rc;
    
    rc = BM1383AGLV_reg_set_bit_pattern(BM1383AGLV_MODE_CONTROL_REG,
                                        BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_16_50MS,
                                        BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_MASK);
    if (rc != RC_OK) {
        return rc;
    }
        
    return RC_OK;
}

uint8_t BM1383AGLV_start_continuous_measurement()
{
    uint8_t rc;
    
    rc = BM1383AGLV_reg_set_bit_pattern(BM1383AGLV_MODE_CONTROL_REG,
                                        BM1383AGLV_MODE_CONTROL_REG_MODE_CONTINUOUS,
                                        BM1383AGLV_MODE_CONTROL_REG_MODE_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t BM1383AGLV_sensor_reset()
{
    uint8_t rc;

    rc = BM1383AGLV_shutdown();
    if (rc != RC_OK) {
        return rc;
    }

    rc = BM1383AGLV_power_on();
    if (rc != RC_OK) {
        return rc;
    }
        
    return RC_OK;
}


/*Only one interrupt pin supported with active low polarity.*/
uint8_t BM1383AGLV_int1_configure(gpio_pin_polarity_t polarity) {

    uint8_t rc;
    uint8_t reg;

    rc = BM1383AGLV_reg_set_bit_pattern(BM1383AGLV_MODE_CONTROL_REG,
                                        BM1383AGLV_MODE_CONTROL_REG_DRDY_ENABLED,
                                        BM1383AGLV_MODE_CONTROL_REG_DRDY_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = BM1383AGLV_reg_read(BM1383AGLV_STATUS_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("First release fail");
        return rc;
    }

    return RC_OK;
}


uint8_t BM1383AGLV_start(uint8_t int_pin, gpio_pin_polarity_t polarity) {

    uint8_t rc;
        
    rc = BM1383AGLV_power_on();
    if (rc != RC_OK) {
        return rc;
    }

    /* set sensor odr.*/
    rc = BM1383AGLV_set_odr();
    if (rc != RC_OK) {
        return rc;
    }

    /*enable interrupt 1.*/
    if(int_pin == BM1383AGLV_INT1) {
        rc = BM1383AGLV_int1_configure(polarity);
        if (rc != RC_OK) {
          return rc;
        }
    }

    /*start measurement*/
    rc = BM1383AGLV_start_continuous_measurement();
    if (rc != RC_OK) {
          return rc;
    }

    return RC_OK;
}


uint8_t BM1383AGLV_init(uint8_t sad)
{
    uint8_t rc;
    uint8_t reg;

    /*platform_funcs needs to be set, or overwrite local read/write/print functions.*/
    if (platform_funcs == NULL) {
        return RC_FAIL;
    }

    drv_data.sad = sad;
    rc = BM1383AGLV_reg_read(BM1383AGLV_ID1_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("Read BM1383AGLV_ID1_REG fail");
        return rc;
    }
  
    if(reg != BM1383AGLV_ID1_REG_MANUFACTURER_ID1) {
        BM1383AGLV_debug_print_line("BM1383AGLV MANUFACTURER ID1 fail");
        return rc;
    }

    rc = BM1383AGLV_reg_read(BM1383AGLV_ID2_REG, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("BM1383AGLV_ID2_REG fail");
        return rc;
    }
  
    if(reg != BM1383AGLV_ID2_REG_MANUFACTURER_ID2) {
        BM1383AGLV_debug_print_line("BM1383AGLV MANUFACTURER ID2 fail");
        return rc;
    }
    
    return RC_OK;
}


uint8_t BM1383AGLV_get_raw(uint8_t *data, uint8_t *size)
{
    uint8_t rc;

    rc = BM1383AGLV_reg_read(BM1383AGLV_STATUS_REG, data, 6);
    if (rc != RC_OK) {
        BM1383AGLV_debug_print_line("BM1383AGLV_get_rawval fail");
        return rc;
    }
    *size = 6;
    return RC_OK;
}


uint8_t BM1383AGLV_debug_dump_regs()
{
/*
    uint8_t dump_regs[] = {
        BM1383AGLV_STATUS_REG,
    };

    uint8_t i = 0;
    uint8_t n = sizeof(dump_regs)/sizeof(dump_regs[0]);

    BM1383AGLV_debug_print_line("BM1383AGLV_debug_dump_regs :");
    for(i=0; i < n ; i++) {
      BM1383AGLV_debug_dump_reg(dump_regs[i]);
    }
*/
    return RC_OK;
}
