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


#ifndef _PLATFORM_FUNCTIONS_H
#define _PLATFORM_FUNCTIONS_H

#include <stdint.h>
#include <string.h>

/**
 * @brief Sensor Identification
 *
 */
typedef enum
{
    NONE_ID,
    KX122_ID, 
    KXG08_ID,
    KMX62_ID,
    BM1383AGLV_ID,
    BM1422GMV_ID
} sensor_id_t;

/**
 * @brief Application events codes.
 *
 */
typedef enum
{
    EVENT_NONE, 
    EVENT_READ_TWI,
    EVENT_BATTERY_MEASUREMENT
} app_event_type_t;


/**
 * @brief Sensor event struct.
 *
 */
typedef struct
{
    sensor_id_t sensor_id;
    uint8_t (*sensor_read)(uint8_t *data, uint8_t *size);      
} app_sensor_evt_t;


/**
 * @brief ADC event struct.
 *
 */
typedef struct
{
    int16_t value;
} app_adc_evt_t;


/**
 * @brief Application event structure.
 *
 * All the data required by the events that comes from the application level.
 */
typedef struct
{
    app_event_type_t type;    
    union {
      app_sensor_evt_t sensor_evt;
      app_adc_evt_t adc_evt;
    } app_events;      
} app_internal_evt_t;


/**
 * @brief Interrupt polarity.
 */
typedef enum
{
    GPIO_POLARITY_NONE,
    GPIO_POLARITY_LOTOHI,
    GPIO_POLARITY_HITOLO
} gpio_pin_polarity_t;

/**
 * @brief Pull-up resistor.
 */
typedef enum
{
    GPIO_NOPULL,
    GPIO_PULLDOWN,
    GPIO_PULLUP
} gpio_pin_pullup_t;


/* @brief Platform functions used by sensor driver(s) */
struct platform_functions
{
    uint8_t (*twi_write)(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);
    uint8_t (*twi_read)(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);
    uint8_t (*delay_ms)(uint16_t ms);
    uint8_t (*debug_println)(char *str);
};

/* @brief Init twi module. */
void nrf52_twi_init (void);

/* @brief TWI write. */
uint8_t nrf52_twi_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);

/* @brief TWI read. */
uint8_t nrf52_twi_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);

/* @brief Init GPIO module. */
void nrf52_gpiote_init(void);

/* @brief Enable GPIO interrupt. */
uint8_t nrf52_enable_interrupt(uint8_t gpio, gpio_pin_polarity_t polarity, gpio_pin_pullup_t pull);

/* @brief nrf52 delay. */
uint8_t nrf52_delay_ms(uint16_t ms);

/* @brief nrf52 debug print. */
uint8_t nrf52_debug_println(char *str);

#endif
