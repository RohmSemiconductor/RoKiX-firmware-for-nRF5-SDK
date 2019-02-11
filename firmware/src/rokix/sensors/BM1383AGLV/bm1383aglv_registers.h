/*
The MIT License (MIT)
Copyright (c) 2017 Rohm Semiconductor

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

#ifndef __BM1383AGLV_REGISTERS_H__
#define __BM1383AGLV_REGISTERS_H__
/* registers */
// [hPa]
#define BM1383AGLV_PRESSURE_MIN 0x12C
// [hPa]
#define BM1383AGLV_PRESSURE_MAX 0x44C
#define BM1383AGLV_REGISTER_DUMP_START 0x0F
#define BM1383AGLV_ID1_REG 0x0F
#define BM1383AGLV_ID2_REG 0x10
#define BM1383AGLV_POWER_REG 0x12
#define BM1383AGLV_RESET_REG 0x13
// This register can be accessed when power is up and measurement control block is not in reset.
#define BM1383AGLV_MODE_CONTROL_REG 0x14
// Reading this REG resets DRDY pin
#define BM1383AGLV_STATUS_REG 0x19
// PRESS_OUT[15:5] integer part of pressure value
#define BM1383AGLV_PRESSURE_OUT_MSB 0x1A
// PRESS_OUT[4:0] PRESS_OUT_XL[7:2] decimal part of pressure value
#define BM1383AGLV_PRESSURE_OUT_LSB 0x1B
#define BM1383AGLV_PRESSURE_OUT_DECIMAL 0x1C
// TEMP_OUT: [15] sign ; [14:5] integer ; [4:0] decimal (2's complement numbers)
#define BM1383AGLV_TEMPERATURE_OUT_MSB 0x1D
// Temperature value [C]= TEMP_OUT[15:0]/32
#define BM1383AGLV_TEMPERATURE_OUT_LSB 0x1E
#define BM1383AGLV_REGISTER_DUMP_END 0x1E
/* registers bits */
#define BM1383AGLV_ID1_REG_MANUFACTURER_ID1 (0xE0 << 0)
#define BM1383AGLV_ID2_REG_MANUFACTURER_ID2 (0x32 << 0)
// write 0
#define BM1383AGLV_POWER_REG_RESERVED_WRITE0 (0x00 << 1)
#define BM1383AGLV_POWER_REG_POWER_DOWN (0x00 << 0)
#define BM1383AGLV_POWER_REG_POWER_UP (0x01 << 0)
// write 0
#define BM1383AGLV_RESET_REG_RESERVED_WRITE0 (0x00 << 1)
// Measurement control block is reset
#define BM1383AGLV_RESET_REG_MODE_RESET (0x00 << 0)
// Measurement control block is active
#define BM1383AGLV_RESET_REG_MODE_STANDBY (0x01 << 0)
// Measurement time 3 [ms] ; interval 50 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_1_50MS (0x00 << 5)
// 5 [ms] ; 50 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_2_50MS (0x01 << 5)
// 10 [ms] ; 50 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_4_50MS (0x02 << 5)
// 19 [ms] ; 50 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_8_50MS (0x03 << 5)
// 37 [ms] ; 50 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_16_50MS (0x04 << 5)
// 74 [ms] ; 100 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_32_100MS (0x05 << 5)
// 147 [ms] ; 200 [ms]
#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_AVG_64_200MS (0x06 << 5)
#define BM1383AGLV_MODE_CONTROL_REG_DRDY_DISABLED (0x00 << 4)
#define BM1383AGLV_MODE_CONTROL_REG_DRDY_ENABLED (0x01 << 4)
// write 1
#define BM1383AGLV_MODE_CONTROL_REG_RESERVED3_WRITE_1 (0x01 << 3)
// write 0
#define BM1383AGLV_MODE_CONTROL_REG_RESERVED2_WRITE_0 (0x00 << 2)
#define BM1383AGLV_MODE_CONTROL_REG_MODE_STANDBY (0x00 << 0)
#define BM1383AGLV_MODE_CONTROL_REG_MODE_ONE_SHOT (0x01 << 0)
#define BM1383AGLV_MODE_CONTROL_REG_MODE_CONTINUOUS (0x02 << 0)
#define BM1383AGLV_MODE_CONTROL_REG_MODE_PROHIBITED (0x03 << 0)
// write 0
#define BM1383AGLV_STATUS_REG_RESERVED_WRITE0 (0x00 << 1)
#define BM1383AGLV_STATUS_REG_DRDY_NOT_READY (0x00 << 0)
#define BM1383AGLV_STATUS_REG_DRDY_READY (0x01 << 0)
 /*registers bit masks */
#define BM1383AGLV_ID1_REG_MANUFACTURER_MASK 0xFF
#define BM1383AGLV_ID2_REG_MANUFACTURER_MASK 0xFF
#define BM1383AGLV_POWER_REG_RESERVED_MASK 0xFE
// Named as PWR_DOWN in specification
#define BM1383AGLV_POWER_REG_POWER_MASK 0x01
#define BM1383AGLV_RESET_REG_RESERVED_MASK 0xFE
// Named as RESET in specification
#define BM1383AGLV_RESET_REG_MODE_MASK 0x01

#define BM1383AGLV_MODE_CONTROL_REG_AVE_NUM_MASK 0xE0
// Named as DREN in specification
#define BM1383AGLV_MODE_CONTROL_REG_DRDY_MASK 0x10
#define BM1383AGLV_MODE_CONTROL_REG_RESERVED3_MASK 0x08

#define BM1383AGLV_MODE_CONTROL_REG_RESERVED2_MASK 0x04

#define BM1383AGLV_MODE_CONTROL_REG_MODE_MASK 0x03
#define BM1383AGLV_STATUS_REG_RESERVED_MASK 0xFE
// Named as RD_DRDY in specification
#define BM1383AGLV_STATUS_REG_DRDY_MASK 0x01
#endif

