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


#ifndef _SENSOR_NODE_H
#define _SENSOR_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"


#define LEDS_NUMBER                     3

#define LED_1                           NRF_GPIO_PIN_MAP(1,3)
#define LED_2                           NRF_GPIO_PIN_MAP(1,4)
#define LED_3                           NRF_GPIO_PIN_MAP(1,5)
    
#define LEDS_ACTIVE_STATE               1
#define LEDS_LIST                       {LED_1, LED_2, LED_3}

#define LEDS_INV_MASK                   LEDS_MASK

#define BSP_LED_0                       LED_1
#define BSP_LED_1                       LED_2
#define BSP_LED_2                       LED_3

#define BUTTONS_NUMBER                  0

#define BUTTON_1                        NRF_GPIO_PIN_MAP(0,25)

#define BUTTON_PULL                     NRF_GPIO_PIN_PULLUP
#define BUTTONS_ACTIVE_STATE            0

#define BUTTONS_LIST                    {BUTTON_1}
#define BSP_BUTTON_0                     BUTTON_1

#define K2_AIN_COMMON_0_29_PIN          NRF_GPIO_PIN_MAP(0,29)
#define K2_AIN_VBAT_0_03_PIN            NRF_GPIO_PIN_MAP(0,3)

#define K2_RX_0_21_PIN                  NRF_GPIO_PIN_MAP(0,21)
#define K2_TX_0_20_PIN                  NRF_GPIO_PIN_MAP(0,20)
#define K2_CTS_0_22_PIN                 NRF_GPIO_PIN_MAP(0,22)
#define K2_RTS_0_23_PIN                 NRF_GPIO_PIN_MAP(0,23)
// Flow control on
#define HWFC true

#define K2_TWIM0_ADDR_0_04_PIN          NRF_GPIO_PIN_MAP(0,4)
#define K2_TWIM0_SDA_0_11_PIN           NRF_GPIO_PIN_MAP(0,11)
#define K2_TWIM0_SCL_0_27_PIN           NRF_GPIO_PIN_MAP(0,27)
#define K2_TWIM0_PULLUP_RES_1_09_PIN    NRF_GPIO_PIN_MAP(1,9)

#define K2_SPIM0_MISO_0_04_PIN          NRF_GPIO_PIN_MAP(0,4)
#define K2_SPIM0_MOSI_0_11_PIN          NRF_GPIO_PIN_MAP(0,11)
#define K2_SPIM0_SCLK_0_27_PIN          NRF_GPIO_PIN_MAP(0,27)
#define K2_SPIM0_SS1_0_13_PIN           NRF_GPIO_PIN_MAP(0,13)
#define K2_SPIM0_SS2_0_26_PIN           NRF_GPIO_PIN_MAP(0,26)
#define K2_SPIM0_SS3_0_05_PIN           NRF_GPIO_PIN_MAP(0,5)

#define K2_TWIM1_ADDR_0_15_PIN          NRF_GPIO_PIN_MAP(0,15)
#define K2_TWIM1_SDA_0_19_PIN           NRF_GPIO_PIN_MAP(0,19)
#define K2_TWIM1_SCL_0_24_PIN           NRF_GPIO_PIN_MAP(0,24)
#define K2_TWIM1_PULLUP_RES_1_08_PIN    NRF_GPIO_PIN_MAP(1,8)

#define K2_SPIM1_MISO_0_15_PIN          NRF_GPIO_PIN_MAP(0,15)
#define K2_SPIM1_MOSI_0_19_PIN          NRF_GPIO_PIN_MAP(0,19)
#define K2_SPIM1_SCLK_0_24_PIN          NRF_GPIO_PIN_MAP(0,24)
#define K2_SPIM1_SS1_0_12_PIN           NRF_GPIO_PIN_MAP(0,12)
#define K2_SPIM1_SS2_0_14_PIN           NRF_GPIO_PIN_MAP(0,14)

#define K2_P_ON_0_02_PIN                NRF_GPIO_PIN_MAP(0,2)
#define K2_INT_R_0_16_PIN               NRF_GPIO_PIN_MAP(0,16)

#define K2_SWD_0_31_PIN                 NRF_GPIO_PIN_MAP(0,31)

#define K2_NFC1_0_09_PIN                NRF_GPIO_PIN_MAP(0,9)
#define K2_NFC2_0_10_PIN                NRF_GPIO_PIN_MAP(0,10)

#define K2_PWE_R_0_28_PIN               NRF_GPIO_PIN_MAP(0,28)
#define K2_PWE_S_1_00_PIN               NRF_GPIO_PIN_MAP(1,00)

#define K2_S1_INT1_1_02_PIN             NRF_GPIO_PIN_MAP(1,2)
#define K2_S1_INT2_1_11_PIN             NRF_GPIO_PIN_MAP(1,11)
#define K2_S2_INT1_1_14_PIN             NRF_GPIO_PIN_MAP(1,14)
#define K2_S2_INT2_1_07_PIN             NRF_GPIO_PIN_MAP(1,7)
#define K2_S3_INT1_1_15_PIN             NRF_GPIO_PIN_MAP(1,15)
#define K2_S3_INT2_1_06_PIN             NRF_GPIO_PIN_MAP(1,6)
#define K2_S4_INT1_1_13_PIN             NRF_GPIO_PIN_MAP(1,13)
#define K2_S5_INT1_1_10_PIN             NRF_GPIO_PIN_MAP(1,10)
#define K2_S6_INT1_1_12_PIN             NRF_GPIO_PIN_MAP(1,12)
#define K2_S6_INT2_1_01_PIN             NRF_GPIO_PIN_MAP(1,1)

#define K2_SPIM2_MISO_0_07_PIN          NRF_GPIO_PIN_MAP(0,7)
#define K2_SPIM2_MOSI_0_06_PIN          NRF_GPIO_PIN_MAP(0,6)
#define K2_SPIM2_SCLK_0_08_PIN          NRF_GPIO_PIN_MAP(0,8)
#define K2_SPIM2_SS_0_17_PIN            NRF_GPIO_PIN_MAP(0,17)

#define K2_VBAT_SW_0_30_PIN            NRF_GPIO_PIN_MAP(0,30)


#ifdef __cplusplus
}
#endif

#endif // _SENSOR_NODE_H

