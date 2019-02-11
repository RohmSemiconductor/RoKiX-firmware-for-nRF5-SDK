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


#ifndef _SENSOR_NODE_INITIALIZE_H
#define _SENSOR_NODE_INITIALIZE_H
#include "nrf.h"
#include "nrf_peripherals.h"
#include "nrf_gpio.h"
#include "sensor_node.h"


/**
 * @brief Battary level measurement control pins init.
 */
__STATIC_INLINE void battery_control_pins_init(void);


/**
 * @brief Set sensor interrupt pins to default position.
 */
__STATIC_INLINE void sensor_int_pins_init(void);


/**
 * @brief Power control init.
 */
__STATIC_INLINE void power_control_init(void);


/**
 * @brief External radio power control init.
 */
__STATIC_INLINE void external_radio_power_control_pins_init(void);


/**
 * @brief Nfc antenna connections.
 */
__STATIC_INLINE void nfc_pins_init(void);


/**
 * @brief Optional debug interface init.
 */
__STATIC_INLINE void swd_signal_init(void);


/**
 * @brief General IO pins init.
 */
__STATIC_INLINE void general_io_pins_init(void);


/**
 * @brief I2C and SPI module pins init.
 */
__STATIC_INLINE void twi_spi_pins_init(void);
    

/**
 * @brief ADC pins init.
 */
__STATIC_INLINE void analog_input_pins_init(void);
    

/**
 * @brief UART pins init.
 */
__STATIC_INLINE void uarte_input_pins_init(void);



__STATIC_INLINE void battery_control_pins_init(void)
{    
    nrf_gpio_cfg_output(K2_VBAT_SW_0_30_PIN);
    nrf_gpio_pin_clear(K2_VBAT_SW_0_30_PIN);
}


__STATIC_INLINE void sensor_int_pins_init(void)
{
    nrf_gpio_cfg_input(K2_S1_INT1_1_02_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S1_INT2_1_11_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S2_INT1_1_14_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S2_INT1_1_14_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S2_INT2_1_07_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S3_INT1_1_15_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S3_INT2_1_06_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S4_INT1_1_13_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S5_INT1_1_10_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S6_INT1_1_12_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_S6_INT2_1_01_PIN, NRF_GPIO_PIN_NOPULL);
}


__STATIC_INLINE void power_control_init(void) {
    
    nrf_gpio_cfg_output(K2_P_ON_0_02_PIN);
    nrf_gpio_pin_set(K2_P_ON_0_02_PIN);
    
    nrf_gpio_cfg_output(K2_PWE_S_1_00_PIN);
    nrf_gpio_pin_set(K2_PWE_S_1_00_PIN);
    
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_pin_set(LED_1);
    
    nrf_gpio_cfg_output(LED_2);
    nrf_gpio_pin_set(LED_2);
    
    nrf_gpio_cfg_output(LED_3);
    nrf_gpio_pin_set(LED_3);
}

   
__STATIC_INLINE void external_radio_power_control_pins_init(void) {
    nrf_gpio_cfg_output(K2_PWE_R_0_28_PIN);
}


__STATIC_INLINE void nfc_pins_init(void) {

    nrf_gpio_pin_pull_t pull_config = NRF_GPIO_PIN_NOPULL;
    
    nrf_gpio_cfg_input(K2_NFC1_0_09_PIN, pull_config);
    nrf_gpio_input_disconnect(K2_NFC1_0_09_PIN);
    
    nrf_gpio_cfg_input(K2_NFC2_0_10_PIN, pull_config);
    nrf_gpio_input_disconnect(K2_NFC2_0_10_PIN);
}


__STATIC_INLINE void swd_signal_init(void)
{        
    nrf_gpio_cfg_input(K2_SWD_0_31_PIN, NRF_GPIO_PIN_NOPULL);
}


__STATIC_INLINE void general_io_pins_init(void)
{    
    nrf_gpio_cfg_input(K2_INT_R_0_16_PIN, NRF_GPIO_PIN_NOPULL);
}


__STATIC_INLINE void twi_spi_pins_init(void)
{  
    nrf_gpio_cfg_output(K2_SPIM0_SCLK_0_27_PIN);
    nrf_gpio_pin_set(K2_SPIM0_SCLK_0_27_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM0_MOSI_0_11_PIN);
    nrf_gpio_pin_set(K2_SPIM0_MOSI_0_11_PIN);
 
    nrf_gpio_cfg_input(K2_TWIM0_ADDR_0_04_PIN, NRF_GPIO_PIN_PULLUP);
    
    nrf_gpio_cfg_output(K2_SPIM0_SS1_0_13_PIN);
    nrf_gpio_pin_set(K2_SPIM0_SS1_0_13_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM0_SS2_0_26_PIN);
    nrf_gpio_pin_set(K2_SPIM0_SS2_0_26_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM0_SS3_0_05_PIN);
    nrf_gpio_pin_set(K2_SPIM0_SS3_0_05_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM1_SCLK_0_24_PIN);
    nrf_gpio_pin_set(K2_SPIM1_SCLK_0_24_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM1_MOSI_0_19_PIN);
    nrf_gpio_pin_set(K2_SPIM1_MOSI_0_19_PIN);
    
    nrf_gpio_cfg_input(K2_TWIM1_ADDR_0_15_PIN, NRF_GPIO_PIN_PULLUP);    
    
    nrf_gpio_cfg_output(K2_SPIM1_SS1_0_12_PIN);
    nrf_gpio_pin_set(K2_SPIM1_SS1_0_12_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM1_SS2_0_14_PIN);
    nrf_gpio_pin_set(K2_SPIM1_SS2_0_14_PIN);
        
    nrf_gpio_cfg_output(K2_SPIM2_SCLK_0_08_PIN);
    nrf_gpio_pin_set(K2_SPIM2_SCLK_0_08_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM2_MOSI_0_06_PIN);
    nrf_gpio_pin_set(K2_SPIM2_MOSI_0_06_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM2_MISO_0_07_PIN);
    nrf_gpio_pin_set(K2_SPIM2_MISO_0_07_PIN);
    
    nrf_gpio_cfg_output(K2_SPIM2_SS_0_17_PIN);
    nrf_gpio_pin_set(K2_SPIM2_SS_0_17_PIN);
        
    nrf_gpio_cfg_output(K2_TWIM0_PULLUP_RES_1_09_PIN);
    nrf_gpio_pin_set(K2_TWIM0_PULLUP_RES_1_09_PIN);   

    nrf_gpio_cfg_output(K2_TWIM1_PULLUP_RES_1_08_PIN);
    nrf_gpio_pin_set(K2_TWIM1_PULLUP_RES_1_08_PIN);    
}


__STATIC_INLINE void analog_input_pins_init(void)
{            
    nrf_gpio_cfg_input(K2_AIN_COMMON_0_29_PIN, NRF_GPIO_PIN_NOPULL);    
    nrf_gpio_cfg_input(K2_AIN_VBAT_0_03_PIN, NRF_GPIO_PIN_NOPULL);     
}


__STATIC_INLINE void uarte_input_pins_init(void)
{            
    nrf_gpio_cfg_input(K2_CTS_0_22_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(K2_RX_0_21_PIN, NRF_GPIO_PIN_NOPULL);
        
    nrf_gpio_cfg_output(K2_TX_0_20_PIN);
    nrf_gpio_cfg_output(K2_RTS_0_23_PIN);
}

#endif

