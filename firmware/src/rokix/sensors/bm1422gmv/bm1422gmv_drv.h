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

#ifndef BM1422GMV_DRV_H_
#define BM1422GMV_DRV_H_

#include "platform_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BM1422GMV_DEVICE_ADDRESS_0E (0x0e) // 7bit Address

/* function return codes */
#define RC_OK 0
#define RC_FAIL 1

/* Set platform functions to driver */
uint8_t BM1422GMV_set_platform_functions(struct platform_functions *functions);

/* BM1422GMV driver functions */
uint8_t BM1422GMV_init(uint8_t sad);
uint8_t BM1422GMV_start(uint8_t int_pin, gpio_pin_polarity_t polarity);
uint8_t BM1422GMV_get_raw(uint8_t *data, uint8_t *size);
uint8_t BM1422GMV_debug_dump_regs(void);

#ifdef __cplusplus
}
#endif

#endif // BM1422GMV_DRV_H_
