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


#include <stdint.h>
#include <string.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "sensors.h"
#include "KX122_drv.h"
#include "KXG08_drv.h"
#include "KMX62_drv.h"
#include "BM1383AGLV_drv.h"
#include "BM1422GMV_drv.h"

void KX122_driver_init(struct platform_functions * p_functions) {

    ret_code_t ret;
    
    /* assign platform dedicated functions to driver. */
    KX122_set_platform_functions(p_functions);
    
    /* init KX122 sensor. */
    ret = KX122_init(KX122_DEVICE_ADDRESS_1F);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KX122_init fail=%d", ret);
        return;
    }

    /* enable sensor interrupt */
    ret = KX122_start(KX122_INT1, GPIO_POLARITY_HITOLO);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KX122_enable_interrupt fail=%d", ret);
        return;
    }

    /* configure platform interrupt */
    nrf52_enable_interrupt(KX122_INT1_PIN, GPIO_POLARITY_HITOLO, GPIO_NOPULL);
}
    

void KXG08_driver_init(struct platform_functions * p_functions) {

    ret_code_t ret;
    
    /* assign platform dedicated functions to driver. */
    KXG08_set_platform_functions(p_functions);
    
    /* init KX122 sensor. */
    ret = KXG08_init(KXG08_DEVICE_ADDRESS_4F);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KXG08_init fail=%d", ret);
        return;
    }

    /* set high resolution mode. */
    ret = KXG08_start(KXG08_INT1, GPIO_POLARITY_HITOLO);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KXG08_start fail=%d", ret);
        return;
    }
    
    /* configure platform interrupt */
    nrf52_enable_interrupt(KXG08_INT1_PIN, GPIO_POLARITY_HITOLO, GPIO_NOPULL);
}


void KMX62_driver_init(struct platform_functions * p_functions) {

    ret_code_t ret;
    
    /* assign platform dedicated functions to driver. */
    KMX62_set_platform_functions(p_functions);
    
    /* init KMX62 sensor. */
    ret = KMX62_init(KMX62_DEVICE_ADDRESS_0F);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KMX62_init fail=%d", ret);
        return;
    }

    /* set high resolution mode. */
    ret = KMX62_start(KMX62_INT1, GPIO_POLARITY_HITOLO);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("KMX62_start fail=%d", ret);
        return;
    }
    
    /* configure platform interrupt */
    nrf52_enable_interrupt(KMX62_INT1_PIN, GPIO_POLARITY_HITOLO, GPIO_NOPULL);
}


void BM1383AGLV_driver_init(struct platform_functions * p_functions) {

    ret_code_t ret;
    
    /* assign platform dedicated functions to driver. */
    BM1383AGLV_set_platform_functions(p_functions);
    
    /* init BM1383AGLV sensor. */
    ret = BM1383AGLV_init(BM1383AGLV_DEVICE_ADDRESS_5D);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("BM1383AGLV_init fail=%d", ret);
        return;
    }
    
    ret = BM1383AGLV_start(BM1383AGLV_INT1, GPIO_POLARITY_HITOLO);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("BM1383AGLV_start fail=%d", ret);
        return;
    }
    
    /* configure platform interrupt */
    nrf52_enable_interrupt(BM1383AGLV_INT1_PIN, GPIO_POLARITY_HITOLO, GPIO_PULLUP);
}

void BM1422GMV_driver_init(struct platform_functions * p_functions) {
    /* assign platform dedicated functions to driver. */
    BM1422GMV_set_platform_functions(p_functions);

    /* init BM1422GMV sensor. */
    ret_code_t ret = BM1422GMV_init(BM1422GMV_DEVICE_ADDRESS_0E);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("BM1422GMV_init fail=%d", ret);
        return;
    }

    gpio_pin_polarity_t interrupt_polarity = GPIO_POLARITY_HITOLO;
    ret = BM1422GMV_start(BM1422GMV_INT1, interrupt_polarity);
    if (ret != NRF_SUCCESS) {
        NRF_LOG_INFO("BM1422GMV_start fail=%d", ret);
        return;
    }

    /* configure platform interrupt */
    nrf52_enable_interrupt(BM1422GMV_INT1_PIN, interrupt_polarity, GPIO_PULLUP);
}

/**@brief Init sensor drivers.*/
void sensors_init(struct platform_functions * p_functions) {
    
    /* Add new sensor init here. 
       By default all the sensors are started. */
    KX122_driver_init(p_functions);
    KXG08_driver_init(p_functions);
    KMX62_driver_init(p_functions);
    BM1383AGLV_driver_init(p_functions);
    BM1422GMV_driver_init(p_functions);
}
