/*
The MIT License (MIT)
Copyright (c) 2020 Rohm Semiconductor

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
#include "kxg08_drv.h"
#include "kxg08_registers.h"


/* Driver data struct */
struct KXG08_drv {
    uint8_t sad;
};

static struct KXG08_drv drv_data;

/* Platform functions passed to driver */
static struct platform_functions *platform_funcs;


/* Set platform functions */
uint8_t KXG08_set_platform_functions(struct platform_functions *functions)
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
uint8_t KXG08_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

    if (platform_funcs && platform_funcs->twi_read) {
        rc = platform_funcs->twi_read(sad, reg, data, size);
    }
    return rc;
}


uint8_t KXG08_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

    if (platform_funcs && platform_funcs->twi_write) {
        rc = platform_funcs->twi_write(sad, reg, data, size);
    }

    return rc;
}


uint8_t KXG08_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

    if (platform_funcs && platform_funcs->delay_ms) {
        rc = platform_funcs->delay_ms(ms);
    }

    return rc;
}


uint8_t KXG08_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

    if (platform_funcs && platform_funcs->debug_println && str != NULL) {
        rc = platform_funcs->debug_println(str);
    }

    return rc;
}


/* KXG08 reg read/write and reg bits handling */
uint8_t KXG08_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KXG08_plat_func_i2c_read(drv_data.sad, reg, data, size);
}


uint8_t KXG08_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KXG08_plat_func_i2c_write(drv_data.sad, reg, data, size);
}


uint8_t KXG08_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KXG08_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }

    reg_val &= ~mask;
    reg_val |= bit_pattern;

    rc = KXG08_reg_write(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return rc;
    }
    return RC_OK;
}


uint8_t KXG08_reg_set_bit(uint8_t reg, uint8_t bits)
{
    return KXG08_reg_set_bit_pattern(reg, bits, 0x00);
}


uint8_t KXG08_reg_reset_bit(uint8_t reg, uint8_t bits)
{
    return KXG08_reg_set_bit_pattern(reg, 0x00, bits);
}


/* Debug prints */
uint8_t KXG08_debug_print_line(char *str)
{
    return KXG08_plat_func_debug_print_line(str);
}


void KXG08_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
    char buffer[40];
    sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
    KXG08_debug_print_line(buffer);
}


void KXG08_debug_dump_reg(uint8_t reg)
{
    uint8_t rc;
    uint8_t reg_val;

    rc = KXG08_reg_read(reg, &reg_val, sizeof(reg_val));
    if (rc != RC_OK) {
        return;
    }

    KXG08_debug_print_reg_and_val(reg, reg_val);
}


/* KXG08 delay */
void KXG08_delay_ms(uint16_t ms)
{
    KXG08_plat_func_delay_ms(ms);
}


/* KXG08 drv_data code  */
uint8_t KXG08_power_on()
{   
    uint8_t rc;
    uint8_t reg_val;
    int timeout;

    /*Power on accelerometer */
    rc = KXG08_reg_set_bit_pattern(KXG08_STDBY,
                                   KXG08_STDBY_ACC_STDBY_ENABLED,
                                   KXG08_STDBY_ACC_STDBY_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    
    /*Power on gyro*/
    rc = KXG08_reg_set_bit_pattern(KXG08_STDBY,
                                   KXG08_STDBY_GYRO_STDBY_ENABLED | 
                                   KXG08_STDBY_GYRO_FSTART_DISABLED,
                                   KXG08_STDBY_GYRO_STDBY_MASK |
                                   KXG08_STDBY_GYRO_FSTART_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    KXG08_debug_print_line("wait gyro start");
    timeout = 200;
    while(timeout > 0) {    
        rc = KXG08_reg_read(KXG08_STATUS1, &reg_val, sizeof(reg_val));
        KXG08_delay_ms(5);
        timeout = timeout - 1;
        
        if(reg_val & KXG08_STATUS1_GYRO_RUN) {
            KXG08_debug_print_line("gyro running");
            break;
        }
    }

    if(timeout == 0) {
        KXG08_debug_print_line("gyro start failure");
        return RC_FAIL;
    }

   
    /* Power on temp.*/
    rc = KXG08_reg_reset_bit(KXG08_STDBY, KXG08_STDBY_TEMP_STDBY_DISABLED);
    if (rc != RC_OK) {
        return rc;
    }
        
    KXG08_delay_ms(2);    
 
    return RC_OK;
}


uint8_t KXG08_power_off()
{
    uint8_t rc;
    
    /* Power off accelerometer.*/
    rc = KXG08_reg_set_bit(KXG08_STDBY, KXG08_STDBY_ACC_STDBY_DISABLED);
    if (rc != RC_OK) {
        return rc;
    }

    /* Power off gyro.*/
    rc = KXG08_reg_reset_bit(KXG08_STDBY, KXG08_STDBY_GYRO_FSTART_ENABLED);
    if (rc != RC_OK) {
        return rc;
    }

    /* Power off temperature.*/
    rc = KXG08_reg_set_bit(KXG08_STDBY, KXG08_STDBY_TEMP_STDBY_DISABLED);
    if (rc != RC_OK) {
        return rc;
    }

    /*Wait power off*/
    KXG08_delay_ms(2);
    
    return RC_OK;
}


uint8_t KXG08_set_odr()
{
    uint8_t rc;
    uint8_t acc_odr = KXG08_ACCEL_ODR_ODRA_6P25;
    uint8_t gyro_odr = KXG08_GYRO_ODR_ODRG_6P25;

    rc = KXG08_reg_set_bit_pattern(KXG08_ACCEL_ODR,
                                   acc_odr, 
                                   KXG08_ACCEL_ODR_ODRA_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KXG08_reg_set_bit_pattern(KXG08_GYRO_ODR,
                                   gyro_odr,
                                   KXG08_GYRO_ODR_ODRG_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KXG08_set_range()
{
    uint8_t rc;

    rc = KXG08_reg_set_bit_pattern(KXG08_ACCEL_CTL, 
                                   KXG08_ACCEL_CTL_ACC_FS_2G, 
                                   KXG08_ACCEL_CTL_ACC_FS_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KXG08_reg_set_bit_pattern(KXG08_GYRO_CTL, 
                                   KXG08_GYRO_CTL_GYRO_FS_1024, 
                                   KXG08_GYRO_CTL_GYRO_FS_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KXG08_wake()
{
    uint8_t rc;
    uint8_t loop = 100;
    uint8_t reg_val;

    rc = KXG08_reg_set_bit(KXG08_WAKE_SLEEP_CTL2, KXG08_WAKE_SLEEP_CTL2_MAN_WAKE);
    if (rc != RC_OK) {
        return rc;
    }
    
    // Force mode requested. Wait self clearing bit to go zero    
    while(loop) {
        if ((rc = KXG08_reg_read(KXG08_WAKE_SLEEP_CTL2,
                                 &reg_val,
                                 sizeof(reg_val))) != RC_OK)
        {
            return rc;
        }

        if(reg_val & KXG08_WAKE_SLEEP_CTL2_MAN_WAKE){
            loop--;
            KXG08_delay_ms(2);                        
        } else {
            KXG08_debug_print_line("Gyro is wake");
            break;       
        }
    }
    
    if(loop == 0) {
        KXG08_debug_print_line("Gyro is not wake");
        return RC_FAIL;
    }
    
    loop = 100;
    // Force mode requested. Wait self clearing bit to go zero    
    while(loop) {
        if ((rc = KXG08_reg_read(KXG08_STATUS1,
                                 &reg_val,
                                 sizeof(reg_val))) != RC_OK)
        {
            return rc;
        }

        if(!(reg_val & KXG08_STATUS1_WAKE_SLEEP_WAKE_MODE)){
            loop--;
            KXG08_delay_ms(2);                        
        } else {
            KXG08_debug_print_line("Gyro is in wake mode");
            break;       
        }
    }
    
    if(loop == 0) {
        KXG08_debug_print_line("Gyro is not in wake mode");
        return RC_FAIL;
    }
    
    return RC_OK;
}


uint8_t KXG08_set_high_resolution_mode()
{    
    uint8_t rc;
    rc = KXG08_reg_reset_bit(KXG08_ACCEL_ODR, KXG08_ACCEL_ODR_LPMODEA);
    if (rc != RC_OK) {
        return rc;
    }
      
    rc = KXG08_reg_reset_bit(KXG08_GYRO_ODR, KXG08_GYRO_ODR_LPMODEG);
    if (rc != RC_OK) {
        return rc;
    }
      
    rc = KXG08_reg_set_bit_pattern(KXG08_ACCEL_CTL, 
                                   KXG08_ACCEL_CTL_ACC_BW_ODR_8,
                                   KXG08_ACCEL_CTL_ACC_BW_MASK);
    if (rc != RC_OK) {
        return rc;
    }
    
    rc = KXG08_reg_set_bit_pattern(KXG08_GYRO_CTL, 
                                   KXG08_GYRO_CTL_GYRO_BW_ODR_8,
                                   KXG08_GYRO_CTL_GYRO_BW_MASK);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KXG08_sensor_soft_reset()
{
    uint8_t rc;
    uint8_t reg_val;
    int timeout = 200;
    rc = KXG08_reg_set_bit(KXG08_CTL_REG_1, KXG08_CTL_REG_1_SRST);
    if (rc != RC_OK) {
        KXG08_debug_print_line("SRST fail");
        return rc;
    }

    while (timeout > 0) {
        KXG08_delay_ms(5);
        timeout = timeout - 1;

        rc = KXG08_reg_read(KXG08_STATUS1, &reg_val, sizeof(reg_val));
        if(rc == RC_OK && reg_val & KXG08_STATUS1_POR) {
            if(reg_val & KXG08_STATUS1_POR) {
                KXG08_debug_print_line("POR done");
                break;
            }
        }
    }
    
    if(timeout == 0) {
      KXG08_debug_print_line("POR timeout");
      return RC_FAIL;      
    }
    
    return RC_OK;
}


uint8_t KXG08_int1_configure(gpio_pin_polarity_t polarity) {

    uint8_t rc;

    rc = KXG08_reg_set_bit_pattern(KXG08_INT_PIN_CTL, 
                                   KXG08_INT_PIN_CTL_IEL1_LATCHED | KXG08_INT_PIN_CTL_IEN1,
                                   KXG08_INT_PIN_CTL_IEL1_MASK | KXG08_INT_PIN_CTL_IEN1);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KXG08_reg_set_bit_pattern(KXG08_INT_PIN_CTL, 
                                   KXG08_INT_PIN_CTL_IEL1_LATCHED | KXG08_INT_PIN_CTL_IEN1,
                                   KXG08_INT_PIN_CTL_IEL1_MASK | KXG08_INT_PIN_CTL_IEN1);
    if (rc != RC_OK) {
        return rc;
    }

    if(polarity == GPIO_POLARITY_HITOLO) {
        rc = KXG08_reg_set_bit_pattern(KXG08_INT_PIN_CTL,
                                       KXG08_INT_PIN_CTL_IEA1_ACTIVE_LOW,
                                       KXG08_INT_PIN_CTL_IEA1_MASK);
           
    } else {
        rc = KXG08_reg_set_bit_pattern(KXG08_INT_PIN_CTL,
                                       KXG08_INT_PIN_CTL_IEA1_ACTIVE_HIGH,
                                       KXG08_INT_PIN_CTL_IEA1_MASK);
    }

    if (rc != RC_OK) {
        return rc;
    }

    rc = KXG08_reg_set_bit(KXG08_INT_MASK1, KXG08_INT_MASK1_DRDY_ACC);
    if (rc != RC_OK) {
        return rc;
    }

    rc = KXG08_reg_set_bit(KXG08_INT_PIN_SEL1, KXG08_INT_PIN_SEL1_DRDY_ACC_P1);
    if (rc != RC_OK) {
        return rc;
    }

    return RC_OK;
}


uint8_t KXG08_start(uint8_t int_pin, gpio_pin_polarity_t polarity) {

    uint8_t rc;

    /*Set sensor to stand-by to enable setup change.*/
    rc = KXG08_power_off();
    if (rc != RC_OK) {
        return rc;
    }

    /*set sensor odr.*/
    rc = KXG08_set_odr();
    if (rc != RC_OK) {
        return rc;
    }

    /*set sensor range.*/
    rc = KXG08_set_range();
    if (rc != RC_OK) {
        return rc;
    }

    /*set high resolution mode.*/
    rc = KXG08_set_high_resolution_mode();
    if (rc != RC_OK) {
        return rc;
    }

    /*enable interrupt 1.*/
    if(int_pin == KXG08_INT1) {
        rc = KXG08_int1_configure(polarity);
        if (rc != RC_OK) {
          return rc;
        }
    }

    /*enable wake mode.*/
    rc = KXG08_wake();
    if (rc != RC_OK) {
        return rc;
    }

    /*power on.*/
    rc = KXG08_power_on();
    if (rc != RC_OK) {
        return rc;
    }

    uint8_t xyz[14];
    //Latch one time by reading.
    rc = KXG08_reg_read(KXG08_TEMP_OUT_L, xyz, 14);
    if (rc != RC_OK) {
        KXG08_debug_print_line("Latch fail");
        return rc;
    }
   
    return RC_OK;
}


uint8_t KXG08_init(uint8_t sad)
{
    uint8_t rc;
    uint8_t reg;

    /* platform_funcs needs to be set, or overwrite local read/write/print functions */
    if (platform_funcs == NULL) {
        return RC_FAIL;
    }

    drv_data.sad = sad;

    rc = KXG08_reg_read(KXG08_WHO_AM_I, &reg, sizeof(reg));
    if (rc != RC_OK) {
        KXG08_debug_print_line("KXG08_reg_read WHO_AM_I fail");
        return rc;
    }
        
    /* verify that we got correct wai value */
    if (reg != KXG08_WHO_AM_I_WIA_ID && reg != KXG08_2080_WHO_AM_I_WIA_ID) {
        KXG08_debug_print_line("Incorrect WAI");
        return RC_FAIL;
    }

    /* do sensor soft reset */
    rc = KXG08_sensor_soft_reset();
    if (rc != RC_OK) {
        KXG08_debug_print_line("KXG08_sensor_soft_reset fail");
        return rc;
    }

    return RC_OK;
}


uint8_t KXG08_get_raw_xyz(uint8_t *xyz, uint8_t *size)
{
    uint8_t rc;

    rc = KXG08_reg_read(KXG08_TEMP_OUT_L, xyz, 14);
    if (rc != RC_OK) {
        KXG08_debug_print_line("KXG08_get_rawval fail");
        return rc;
    }
    *size = 14;
    return RC_OK;
}


uint8_t KXG08_debug_dump_regs()
{

    /*uint8_t dump_regs[] = {
        KXG08_STATUS1,
    };

    uint8_t i = 0;
    uint8_t n = sizeof(dump_regs)/sizeof(dump_regs[0]);

    KXG08_debug_print_line("KXG08_debug_dump_regs :");
    for(i=0; i < n ; i++) {
        KXG08_debug_dump_reg(dump_regs[i]);
    }
    */

    return RC_OK;
}


