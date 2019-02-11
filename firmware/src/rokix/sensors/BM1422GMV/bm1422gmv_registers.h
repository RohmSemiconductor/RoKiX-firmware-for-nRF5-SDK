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

#ifndef __BM1422GMV_REGISTERS_H__
#define __BM1422GMV_REGISTERS_H__
/* registers */
#define BM1422GMV_REGISTER_DUMP_START 0x0D
// Information 16bit
#define BM1422GMV_INFO 0x0D
#define BM1422GMV_INFO_MSB 0x0E
// This register can be used for supplier recognition, as it can be factory written to a known byte value.
#define BM1422GMV_WHO_AM_I 0x0F
// Xch Output value
#define BM1422GMV_DATAX 0x10
#define BM1422GMV_DATAX_MSB 0x11
// Ych Output value
#define BM1422GMV_DATAY 0x12
#define BM1422GMV_DATAY_MSB 0x13
// Zch Output value
#define BM1422GMV_DATAZ 0x14
#define BM1422GMV_DATAZ_MSB 0x15
#define BM1422GMV_STA1 0x18
// Control setting
#define BM1422GMV_CNTL1 0x1B
// Control setting 2
#define BM1422GMV_CNTL2 0x1C
// Control setting 3
#define BM1422GMV_CNTL3 0x1D
// Preset time register
#define BM1422GMV_PRET 0x30
// Average time setting
#define BM1422GMV_AVER 0x40
// Control setting. Reserved
#define BM1422GMV_CNTL4_LSB 0x5C
// Control setting. RSTB_LV=1 when register written (data irrelevant), RSTB_LV=0 when PC1=0 written.
#define BM1422GMV_CNTL4_MSB 0x5D
// Temperature value
#define BM1422GMV_TEMP 0x60
#define BM1422GMV_TEMP_MSB 0x61
// Xch offset value
#define BM1422GMV_OFF_X 0x6C
// Ych offset value
#define BM1422GMV_OFF_Y 0x72
// Zch offset value
#define BM1422GMV_OFF_Z 0x78
// DATAX value per OFF_X
#define BM1422GMV_FINEOUTPUTX 0x90
#define BM1422GMV_FINEOUTPUTX_MSB 0x91
// DATAY value per OFF_Y
#define BM1422GMV_FINEOUTPUTY 0x92
#define BM1422GMV_FINEOUTPUTY_MSB 0x93
// DATAZ value per OFF_Z
#define BM1422GMV_FINEOUTPUTZ 0x94
#define BM1422GMV_FINEOUTPUTZ_MSB 0x95
// Reserved
#define BM1422GMV_SENSX 0x96
#define BM1422GMV_SENSX_MSB 0x97
// Reserved
#define BM1422GMV_SENSY 0x98
#define BM1422GMV_SENSY_MSB 0x99
// Reserved
#define BM1422GMV_SENSZ 0x9A
#define BM1422GMV_SENSZ_MSB 0x9B
// Axis interference Xch to Zch
#define BM1422GMV_GAIN_PARA_X_Z 0x9C
// Axis interference Xch to Ych
#define BM1422GMV_GAIN_PARA_X_Y 0x9D
// Axis interference Ych to Zch
#define BM1422GMV_GAIN_PARA_Y_Z 0x9E
// Axis interference Ych to Xch
#define BM1422GMV_GAIN_PARA_Y_X 0x9F
// Axis interference Zch to Ych
#define BM1422GMV_GAIN_PARA_Z_Y 0xA0
// Axis interference Zch to Xch
#define BM1422GMV_GAIN_PARA_Z_X 0xA1
// Reserved
#define BM1422GMV_OFFZEROX 0xF8
#define BM1422GMV_OFFZEROX_MSB 0xF9
// Reserved
#define BM1422GMV_OFFZEROY 0xFA
#define BM1422GMV_OFFZEROY_MSB 0xFB
// Reserved
#define BM1422GMV_OFFZEROZ 0xFC
#define BM1422GMV_OFFZEROZ_MSB 0xFD
#define BM1422GMV_REGISTER_DUMP_END 0x1E
/* registers bits */
// WHO_AM_I -value
#define BM1422GMV_WHO_AM_I_WIA_ID (0x41 << 0)
#define BM1422GMV_STA1_DRDY_READY (0x01 << 6)
// PowerDown
#define BM1422GMV_CNTL1_PC1_OFF (0x00 << 7)
// Active
#define BM1422GMV_CNTL1_PC1_ON (0x01 << 7)
// 12bit resolution
#define BM1422GMV_CNTL1_OUT_BIT_12 (0x00 << 6)
// 14bit resolution
#define BM1422GMV_CNTL1_OUT_BIT_14 (0x01 << 6)
// Reset release
#define BM1422GMV_CNTL1_RST_LV_RELEASE (0x00 << 5)
// Reset (POR)
#define BM1422GMV_CNTL1_RST_LV_RESET (0x01 << 5)
#define BM1422GMV_CNTL1_ODR_10 (0x00 << 3)
#define BM1422GMV_CNTL1_ODR_100 (0x01 << 3)
#define BM1422GMV_CNTL1_ODR_20 (0x02 << 3)
#define BM1422GMV_CNTL1_ODR_1000 (0x03 << 3)
// Continuous mode
#define BM1422GMV_CNTL1_FS1_CONT (0x00 << 1)
// Single mode
#define BM1422GMV_CNTL1_FS1_SINGLE (0x01 << 1)
#define BM1422GMV_CNTL2_DREN_DISABLED (0x00 << 3)
#define BM1422GMV_CNTL2_DREN_ENABLED (0x01 << 3)
#define BM1422GMV_CNTL2_DRP_LOWACTIVE (0x00 << 2)
#define BM1422GMV_CNTL2_DRP_HIGHACTIVE (0x01 << 2)
#define BM1422GMV_CNTL3_FORCE_START (0x01 << 6)
// write "0"
#define BM1422GMV_PRET_PS (0x01 << 0)
#define BM1422GMV_AVER_AVG_4TIMES (0x00 << 2)
#define BM1422GMV_AVER_AVG_1TIMES (0x01 << 2)
#define BM1422GMV_AVER_AVG_2TIMES (0x02 << 2)
#define BM1422GMV_AVER_AVG_8TIMES (0x03 << 2)
#define BM1422GMV_AVER_AVG_16TIMES (0x04 << 2)
 /*registers bit masks */
#define BM1422GMV_WHO_AM_I_WIA_MASK 0xFF
// Data ready status
#define BM1422GMV_STA1_DRDY_MASK 0x40
#define BM1422GMV_CNTL1_PC1_MASK 0x80
// Output data bit setting
#define BM1422GMV_CNTL1_OUT_BIT_MASK 0x40
// Reset release (RST_LV=0 & RSTB_LV=1)
#define BM1422GMV_CNTL1_RST_LV_MASK 0x20

#define BM1422GMV_CNTL1_ODR_MASK 0x18
#define BM1422GMV_CNTL1_FS1_MASK 0x02
// DRDY enable setting. (0:Disable, 1:Enable)
#define BM1422GMV_CNTL2_DREN_MASK 0x08
#define BM1422GMV_CNTL2_DRP_MASK 0x04
#define BM1422GMV_CNTL3_FORCE_MASK 0x40

#define BM1422GMV_AVER_AVG_MASK 0x1C
#endif

