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
#include "BM1422GMV_drv.h"
#include "bm1422gmv_registers.h"


/* Driver data struct */
struct BM1422GMV_drv {
    uint8_t sad;
};

static struct BM1422GMV_drv drv_data;

/* Platform functions passed to driver */
static struct platform_functions *platform_funcs;


/* Set platfrom functions */
uint8_t BM1422GMV_set_platform_functions(struct platform_functions *functions)
{
    if (functions == NULL ||
            functions->twi_read == NULL ||
            functions->twi_write == NULL) {
        return RC_FAIL;
    }
    platform_funcs = functions;
    return RC_OK;
}


/* Wrapper to platform functions */
uint8_t BM1422GMV_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

    if (platform_funcs && platform_funcs->twi_read) {
        rc = platform_funcs->twi_read(sad, reg, data, size);
    }
    return rc;
}


uint8_t BM1422GMV_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

    if (platform_funcs && platform_funcs->twi_write) {
        rc = platform_funcs->twi_write(sad, reg, data, size);
    }

    return rc;
}


uint8_t BM1422GMV_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

    if (platform_funcs && platform_funcs->delay_ms) {
        rc = platform_funcs->delay_ms(ms);
    }

    return rc;
}


uint8_t BM1422GMV_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

    if (platform_funcs && platform_funcs->debug_println && str != NULL) {
        rc = platform_funcs->debug_println(str);
    }

    return rc;
}


/* BM1422GMV reg read/write and reg bits handling */
uint8_t BM1422GMV_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return BM1422GMV_plat_func_i2c_read(drv_data.sad, reg, data, size);
}


uint8_t BM1422GMV_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return BM1422GMV_plat_func_i2c_write(drv_data.sad, reg, data, size);
}


uint8_t BM1422GMV_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = BM1422GMV_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }

    reg_val &= ~mask;
    reg_val |= bit_pattern;

    rc = BM1422GMV_reg_write(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }
    return RC_OK;
}


uint8_t BM1422GMV_reg_set_bit(uint8_t reg, uint8_t bits)
{
    return BM1422GMV_reg_set_bit_pattern(reg, bits, 0x00);
}


uint8_t BM1422GMV_reg_reset_bit(uint8_t reg, uint8_t bits)
{
    return BM1422GMV_reg_set_bit_pattern(reg, 0x00, bits);
}


/* Debug prints */
uint8_t BM1422GMV_debug_print_line(char *str)
{
    return BM1422GMV_plat_func_debug_print_line(str);
}


void BM1422GMV_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
    char buffer[40];
    sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
    BM1422GMV_debug_print_line(buffer);
}


void BM1422GMV_debug_dump_reg(uint8_t reg)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = BM1422GMV_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return;
    }

    BM1422GMV_debug_print_reg_and_val(reg, reg_val);
}


/* BM1422GMV delay */
void BM1422GMV_delay_ms(uint16_t ms)
{
    BM1422GMV_plat_func_delay_ms(ms);
}


/* Apply power-on settings to the sensor. */
uint8_t BM1422GMV_power_on()
{
    BM1422GMV_delay_ms(1);

    uint8_t rc = BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        BM1422GMV_CNTL1_PC1_ON, BM1422GMV_CNTL1_PC1_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    rc = BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        BM1422GMV_CNTL1_RST_LV_RELEASE, BM1422GMV_CNTL1_RST_LV_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    BM1422GMV_delay_ms(2);

    uint8_t reg_addrs[] = {BM1422GMV_CNTL4_LSB, BM1422GMV_CNTL4_MSB};
    for (int i = 0; i < sizeof(reg_addrs); ++i) {
        uint8_t reg_val = 0x00;
        BM1422GMV_reg_write(reg_addrs[i], &reg_val, sizeof(reg_val));
        if (rc != RC_OK) {
            return rc;
        }
    }

    return RC_OK;
}


uint8_t BM1422GMV_power_off()
{
    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        BM1422GMV_CNTL1_FS1_SINGLE, BM1422GMV_CNTL1_FS1_MASK);
}


uint8_t BM1422GMV_shutdown()
{
    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        BM1422GMV_CNTL1_PC1_OFF, BM1422GMV_CNTL1_PC1_MASK);
}


/* Set sensor ODR.
 *
 * Valid ODRs: 10, 20, 100, 1000 Hz.
 */
uint8_t BM1422GMV_set_odr(int odr)
{
    uint8_t odr_reg_val;
    switch (odr) {
    case 10:
        odr_reg_val = BM1422GMV_CNTL1_ODR_10;
        break;
    case 20:
        odr_reg_val = BM1422GMV_CNTL1_ODR_20;
        break;
    case 100:
        odr_reg_val = BM1422GMV_CNTL1_ODR_100;
        break;
    case 1000:
        odr_reg_val = BM1422GMV_CNTL1_ODR_1000;
        break;
    default:
        return RC_FAIL;
    }

    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        odr_reg_val, BM1422GMV_CNTL1_ODR_MASK);
}


uint8_t BM1422GMV_enable_drdy_pin(void)
{
    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL2,
        BM1422GMV_CNTL2_DREN_ENABLED, BM1422GMV_CNTL2_DREN_MASK);
}


uint8_t BM1422GMV_set_drdy_polarity(gpio_pin_polarity_t polarity)
{
    uint8_t reg_val;
    switch (polarity) {
    case GPIO_POLARITY_LOTOHI:
        reg_val = BM1422GMV_CNTL2_DRP_HIGHACTIVE;
        break;
    case GPIO_POLARITY_HITOLO:
        reg_val = BM1422GMV_CNTL2_DRP_LOWACTIVE;
        break;
    default:
        return RC_FAIL;
    }

    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL2,
        reg_val, BM1422GMV_CNTL2_DRP_MASK);
}


uint8_t BM1422GMV_start_continuous_measurement()
{
    uint8_t rc = BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL1,
        BM1422GMV_CNTL1_FS1_CONT, BM1422GMV_CNTL1_FS1_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return BM1422GMV_reg_set_bit_pattern(BM1422GMV_CNTL3,
        BM1422GMV_CNTL3_FORCE_START, BM1422GMV_CNTL3_FORCE_MASK);
}


uint8_t BM1422GMV_sensor_reset()
{
    uint8_t rc = BM1422GMV_shutdown();
    if (rc != RC_OK) {
        return rc;
    }

    return BM1422GMV_power_on();
}


uint8_t BM1422GMV_int1_configure(gpio_pin_polarity_t polarity)
{
    uint8_t rc = BM1422GMV_enable_drdy_pin();
    if (rc != RC_OK) {
        return rc;
    }

    rc = BM1422GMV_set_drdy_polarity(polarity);
    if (rc != RC_OK) {
        return rc;
    }

    /* Clear any asserted DRDY interrupt. */
    uint8_t reg;
    rc = BM1422GMV_reg_read(BM1422GMV_STA1, &reg, sizeof(reg));
    if (rc != RC_OK) {
        BM1422GMV_debug_print_line("First relase fail");
        return rc;
    }

    return RC_OK;
}


uint8_t BM1422GMV_start(uint8_t int_pin, gpio_pin_polarity_t polarity)
{
    uint8_t rc = BM1422GMV_power_on();
    if (rc != RC_OK) {
        return rc;
    }

    rc = BM1422GMV_set_odr(20);
    if (rc != RC_OK) {
        return rc;
    }

    /* configure averaging */
    rc = BM1422GMV_reg_set_bit_pattern(BM1422GMV_AVER,
        BM1422GMV_AVER_AVG_1TIMES, BM1422GMV_AVER_AVG_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    /* enable interrupt 1. */
    if (int_pin == BM1422GMV_INT1) {
        rc = BM1422GMV_int1_configure(polarity);
        if (rc != RC_OK) {
            return rc;
        }
    }

    /* start measurement */
    rc = BM1422GMV_start_continuous_measurement();
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t BM1422GMV_init(uint8_t sad)
{
    /* platform_funcs needs to be set, or overwrite local read/write/print functions. */
    if (platform_funcs == NULL) {
        return RC_FAIL;
    }

    drv_data.sad = sad;

    uint8_t whoami;
    uint8_t rc = BM1422GMV_reg_read(BM1422GMV_WHO_AM_I, &whoami, 1);
    if (rc != RC_OK) {
        return rc;
    }
    if (whoami != BM1422GMV_WHO_AM_I_WIA_ID) {
        BM1422GMV_debug_print_line("Incorrect WAI");
        return RC_FAIL;
    }

    return BM1422GMV_sensor_reset();
}


/* Read raw temperature (2 bytes) and magnetometer data (6 bytes). */
uint8_t BM1422GMV_get_raw(uint8_t *data, uint8_t *size)
{
    int temp_size = 2;
    uint8_t rc = BM1422GMV_reg_read(BM1422GMV_TEMP, data, temp_size);
    if (rc != RC_OK) {
        return rc;
    }

    int mag_size = 6;
    rc = BM1422GMV_reg_read(BM1422GMV_DATAX, data + temp_size, mag_size);
    if (rc != RC_OK) {
        return rc;
    }

    *size = temp_size + mag_size;
    return RC_OK;
}


uint8_t BM1422GMV_debug_dump_regs()
{
    uint8_t dump_regs[] = {
        BM1422GMV_CNTL1,
        BM1422GMV_CNTL2,
        BM1422GMV_CNTL3,
    };

    uint8_t n = sizeof(dump_regs) / sizeof(dump_regs[0]);
    BM1422GMV_debug_print_line("BM1422GMV_debug_dump_regs:");
    for (uint8_t i = 0; i < n; i++) {
        BM1422GMV_debug_dump_reg(dump_regs[i]);
    }
    return RC_OK;
}
