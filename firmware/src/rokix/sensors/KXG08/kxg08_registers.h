/*
The MIT License (MIT)
Copyright (c) 2017 Kionix Inc.

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

#ifndef __KXG08_REGISTERS_H__
#define __KXG08_REGISTERS_H__
/* registers */
#define KXG08_TEMP_OUT_L 0x00
#define KXG08_TEMP_OUT_H 0x01
#define KXG08_GYRO_XOUT_L 0x02
#define KXG08_GYRO_XOUT_H 0x03
#define KXG08_GYRO_YOUT_L 0x04
#define KXG08_GYRO_YOUT_H 0x05
#define KXG08_GYRO_ZOUT_L 0x06
#define KXG08_GYRO_ZOUT_H 0x07
#define KXG08_ACCEL_XOUT_L 0x08
#define KXG08_ACCEL_XOUT_H 0x09
#define KXG08_ACCEL_YOUT_L 0x0A
#define KXG08_ACCEL_YOUT_H 0x0B
#define KXG08_ACCEL_ZOUT_L 0x0C
#define KXG08_ACCEL_ZOUT_H 0x0D
#define KXG08_AUX1_OUT_1 0x0E
#define KXG08_AUX1_OUT_2 0x0F
#define KXG08_AUX1_OUT_3 0x10
#define KXG08_AUX1_OUT_4 0x11
#define KXG08_AUX1_OUT_5 0x12
#define KXG08_AUX1_OUT_6 0x13
#define KXG08_AUX2_OUT_1 0x14
#define KXG08_AUX2_OUT_2 0x15
#define KXG08_AUX2_OUT_3 0x16
#define KXG08_AUX2_OUT_4 0x17
#define KXG08_AUX2_OUT_5 0x18
#define KXG08_AUX2_OUT_6 0x19
#define KXG08_TIMESTAMP7_0 0x1A
#define KXG08_TIMESTAMP15_8 0x1B
#define KXG08_TIMESTAMP18_16 0x1C
#define KXG08_BUF_PAST 0x1D
#define KXG08_BUF_SMPLEV_L 0x1E
#define KXG08_BUF_SMPLEV_H 0x1F
// Current Tilt Position Register.
#define KXG08_TSCP 0x20
// Previous Tilt Positon Register.
#define KXG08_TSPP 0x21
// Reports the status of Auxiliary Sensors AUX1 and AUX2.
#define KXG08_AUX_STATUS 0x22
// WHO_AM_I
#define KXG08_WHO_AM_I 0x23
#define KXG08_SN7_0 0x24
#define KXG08_SN15_8 0x25
#define KXG08_SN23_16 0x26
#define KXG08_SN31_24 0x27
// Status register 1
#define KXG08_STATUS1 0x30
// Interrupt 1 source register 1
#define KXG08_INT1_SRC1 0x31
// Interrupt 1 source register 2 (WUF direction)
#define KXG08_INT1_SRC2 0x32
// Interrupt 1 source register 3 (Double Tap direction)
#define KXG08_INT1_SRC3 0x33
// Interrupt 1 source register 4
#define KXG08_INT1_SRC4 0x34
#define KXG08_INT1_L 0x35
// Status register 2
#define KXG08_STATUS2 0x36
// Interrupt 2 source register 1
#define KXG08_INT2_SRC1 0x37
// Interrupt 2 source register 2 (WUF direction)
#define KXG08_INT2_SRC2 0x38
// Interrupt 2 source register 3 (Double Tap direction)
#define KXG08_INT2_SRC3 0x39
// Interrupt 2 source register 4
#define KXG08_INT2_SRC4 0x3A
#define KXG08_INT2_L 0x3B
// Accelerometer Control register
#define KXG08_ACCEL_ODR 0x3C
// Accelerometer range control register
#define KXG08_ACCEL_CTL 0x3D
// Gyroscope Control register
#define KXG08_GYRO_ODR 0x3E
// Gyro range control register.
#define KXG08_GYRO_CTL 0x3F
// This register controls the settings for the physical interrupt pins INT1 and INT2
#define KXG08_INT_PIN_CTL 0x40
// Physical interrupt pin INT1 select register.
#define KXG08_INT_PIN_SEL1 0x41
// Physical interrupt pin INT2 select register.
#define KXG08_INT_PIN_SEL2 0x42
// Physical interrupt pin select register
#define KXG08_INT_PIN_SEL3 0x43
// Buffer Full Interrupt enable/mask bit.
#define KXG08_INT_MASK1 0x44
// which axis and direction of detected motion can cause an interrupt.
#define KXG08_INT_MASK2 0x45
// This register controls which axis and direction of tap/double tap can cause an interrupt.
#define KXG08_INT_MASK3 0x46
// This register controls which axis and direction of tilt position can cause an interrupt
#define KXG08_INT_MASK4 0x47
// External Synchronous control register.
#define KXG08_FSYNC_CTL 0x48
#define KXG08_BTS_TH 0x49
#define KXG08_BTSWUF_TH 0x4A
#define KXG08_WUF_TH 0x4B
#define KXG08_BTS_COUNTER 0x4C
#define KXG08_WUF_COUNTER 0x4D
// Wake and Sleep control register 1.
#define KXG08_WAKE_SLEEP_CTL1 0x4E
// WUF and BTS threshold mode.
#define KXG08_WAKE_SLEEP_CTL2 0x4F
// Read/Write control register
#define KXG08_AUX_I2C_CTL_REG 0x50
#define KXG08_AUX_I2C_SAD1 0x51
#define KXG08_AUX_I2C_REG1 0x52
#define KXG08_AUX_I2C_CTL1 0x53
#define KXG08_AUX_I2C_BIT1 0x54
// Defines register read controls for auxiliary I2C device.
#define KXG08_AUX_I2C_ODR 0x55
#define KXG08_AUX_I2C_SAD2 0x56
#define KXG08_AUX_I2C_REG2 0x57
#define KXG08_AUX_I2C_CTL2 0x58
#define KXG08_AUX_I2C_BIT2 0x59
// Defines register read controls for auxiliary I2C device.
#define KXG08_AUX_I2C_ODR2 0x5A
#define KXG08_HYST_SET 0x5B
#define KXG08_TILT_ANGLE_HL 0x5C
#define KXG08_TILT_ANGLE_LL 0x5D
#define KXG08_TILT_TIMER 0x5E
// This register sets the high level threshold for tilt angle detection.
#define KXG08_TILT_TAP_ODR 0x5F
// This register is responsible for enabling/disabling reporting of Tap/Double Tap
#define KXG08_TDTRC 0x60
#define KXG08_TDTC 0x61
#define KXG08_TTH 0x62
#define KXG08_TTL 0x63
#define KXG08_FTD 0x64
#define KXG08_STD 0x65
#define KXG08_TLT 0x66
#define KXG08_TWS 0x67
#define KXG08_FFTH 0x68
#define KXG08_FFC 0x69
// Free Fall Control
#define KXG08_FFCTL 0x6A
// Special control register 1
#define KXG08_CTL_REG_1 0x6B
// Stand-by and operational control register.
#define KXG08_STDBY 0x6E
#define KXG08_BUF_WMITH_L 0x72
#define KXG08_BUF_WMITH_H 0x73
#define KXG08_BUF_TRIGTH_L 0x74
#define KXG08_BUF_TRIGTH_H 0x75
// Read/write control register that controls sample buffer input
#define KXG08_BUF_CTL1 0x76
// Read/write control register that controls aux1 and aux2 buffer input
#define KXG08_BUF_CTL2 0x77
// Read/write control register that controls sample buffer operation
#define KXG08_BUF_EN 0x78
#define KXG08_BUF_STATUS 0x79
#define KXG08_BUF_CLEAR 0x7A
#define KXG08_BUF_READ 0x7B
// WHO_AM_I
#define KXG08_2080_WHO_AM_I 0x23
// WHO_AM_I
#define KXG07_1080_WHO_AM_I 0x23
// WHO_AM_I
#define KXG07_2080_WHO_AM_I 0x23
// WHO_AM_I
#define KXG07_3001_WHO_AM_I 0x23
/* registers bits */
// x-left
#define KXG08_TSCP_LE (0x01 << 5)
// x+right
#define KXG08_TSCP_RI (0x01 << 4)
// y-down
#define KXG08_TSCP_DO (0x01 << 3)
// y+up
#define KXG08_TSCP_UP (0x01 << 2)
// z-facedown
#define KXG08_TSCP_FD (0x01 << 1)
// z+faceup
#define KXG08_TSCP_FU (0x01 << 0)
// x-left
#define KXG08_TSPP_LE (0x01 << 5)
// x+right
#define KXG08_TSPP_RI (0x01 << 4)
// y-down
#define KXG08_TSPP_DO (0x01 << 3)
// y+up
#define KXG08_TSPP_UP (0x01 << 2)
// z-facedown
#define KXG08_TSPP_FD (0x01 << 1)
// z+faceup
#define KXG08_TSPP_FU (0x01 << 0)
// Aux1 sensor is disabled
#define KXG08_AUX_STATUS_AUX1ST_DISABLED (0x00 << 0)
// Aux1 sensor is waiting to be enabled.
#define KXG08_AUX_STATUS_AUX1ST_WAITING_TO_BE_ENABLED (0x01 << 0)
// Aux1 sensor is waiting to be disabled.
#define KXG08_AUX_STATUS_AUX1ST_WAITING_TO_BE_DISABLED (0x02 << 0)
// Aux1 sensor is running.
#define KXG08_AUX_STATUS_AUX1ST_SENSOR_RUNNING (0x03 << 0)
// Aux1 data read error flag.
#define KXG08_AUX_STATUS_AUX1ERR (0x01 << 2)
// Aux1 command sequence failure flag.
#define KXG08_AUX_STATUS_AUX1FAIL (0x01 << 3)
// Aux2 sensor is disabled
#define KXG08_AUX_STATUS_AUX2ST_DISABLED (0x00 << 4)
// Aux2 sensor is waiting to be enabled.
#define KXG08_AUX_STATUS_AUX2ST_WAITING_TO_BE_ENABLED (0x01 << 4)
// Aux2 sensor is waiting to be disabled.
#define KXG08_AUX_STATUS_AUX2ST_WAITING_TO_BE_DISABLED (0x02 << 4)
// Aux2 sensor is running.
#define KXG08_AUX_STATUS_AUX2ST_SENSOR_RUNNING (0x03 << 4)
// Aux1 data read error flag.
#define KXG08_AUX_STATUS_AUX2ERR (0x01 << 6)
// Aux1 command sequence failure flag.
#define KXG08_AUX_STATUS_AUX2FAIL (0x01 << 7)
// WHO_AM_I -value 1080 version
#define KXG08_WHO_AM_I_WIA_ID (0x2A << 0)
// Reports logical OR of non-masked interrupt sources sent to INT1
#define KXG08_STATUS1_INT1 (0x01 << 7)
// Reset indicator.
#define KXG08_STATUS1_POR (0x01 << 6)
// Auxiliary sensor #2 active flag.
#define KXG08_STATUS1_AUX2_ACT (0x01 << 5)
// Auxiliary sensor #1 active flag.
#define KXG08_STATUS1_AUX1_ACT (0x01 << 4)
// Auxiliary communication error
#define KXG08_STATUS1_AUX_ERR (0x01 << 3)
// Sleep mode status
#define KXG08_STATUS1_WAKE_SLEEP_SLEEP_MODE (0x00 << 2)
// Wake mode status
#define KXG08_STATUS1_WAKE_SLEEP_WAKE_MODE (0x01 << 2)
// Gyro's start status
#define KXG08_STATUS1_GYRO_RUN (0x01 << 0)
// Buffer full interrupt.
#define KXG08_INT1_SRC1_INT1_BFI (0x01 << 7)
// Buffer water mark interrupt.
#define KXG08_INT1_SRC1_INT1_WMI (0x01 << 6)
// Wake up function interrupt.
#define KXG08_INT1_SRC1_INT1_WUFS (0x01 << 5)
// Back to sleep interrupt.
#define KXG08_INT1_SRC1_INT1_BTS (0x01 << 4)
// Aux2 data ready interrupt.
#define KXG08_INT1_SRC1_INT1_DRDY_AUX2 (0x01 << 3)
// Aux1 data ready interrupt.
#define KXG08_INT1_SRC1_INT1_DRDY_AUX1 (0x01 << 2)
// Accel data ready interrupt.
#define KXG08_INT1_SRC1_INT1_DRDY_ACC (0x01 << 1)
// Gyro data ready interrupt.
#define KXG08_INT1_SRC1_INT1_DRDY_GYRO (0x01 << 0)
// Wake up event detected on x-axis, negative direction
#define KXG08_INT1_SRC2_INT1_XNWU (0x01 << 5)
// Wake up event detected on x-axis, positive direction.
#define KXG08_INT1_SRC2_INT1_XPWU (0x01 << 4)
// Wake up event detected on y-axis, negative direction
#define KXG08_INT1_SRC2_INT1_YNWU (0x01 << 3)
// Wake up event detected on y-axis, positive direction.
#define KXG08_INT1_SRC2_INT1_YPWU (0x01 << 2)
// Wake up event detected on z-axis, negative direction.
#define KXG08_INT1_SRC2_INT1_ZNWU (0x01 << 1)
// Wake up event detected on z-axis, positive direction.
#define KXG08_INT1_SRC2_INT1_ZPWU (0x01 << 0)
// x-axis, negative direction.
#define KXG08_INT1_SRC3_INT1_XTLE (0x01 << 5)
// x-axis, positive direction.
#define KXG08_INT1_SRC3_INT1_XTRI (0x01 << 4)
// y-axis, negative direction.
#define KXG08_INT1_SRC3_INT1_YTDO (0x01 << 3)
// y-axis, positive direction.
#define KXG08_INT1_SRC3_INT1_YTUP (0x01 << 2)
// z-axis, negative direction.
#define KXG08_INT1_SRC3_INT1_ZTFD (0x01 << 1)
// z-axis, positive direction.
#define KXG08_INT1_SRC3_INT1_ZTFU (0x01 << 0)
// Tilt position interrupt source
#define KXG08_INT1_SRC4_INT1_TPS (0x01 << 3)
// no tap
#define KXG08_INT1_SRC4_INT1_TDTS_NOTAP (0x00 << 1)
// single tap event
#define KXG08_INT1_SRC4_INT1_TDTS_SINGLE (0x01 << 1)
// double tap event
#define KXG08_INT1_SRC4_INT1_TDTS_DOUBLE (0x02 << 1)
// Freefall interrupt source
#define KXG08_INT1_SRC4_INT1_FFS (0x01 << 0)
// reports Logical OR of non-masked interrupt sources sent to INT2 pin.
#define KXG08_STATUS2_INT2 (0x01 << 7)
// Reset indicator.
#define KXG08_STATUS2_POR (0x01 << 6)
// Auxiliary sensor #2 active flag.
#define KXG08_STATUS2_AUX2_ACT (0x01 << 5)
// Auxiliary sensor #1 active flag.
#define KXG08_STATUS2_AUX1_ACT (0x01 << 4)
// Auxiliary communications error.
#define KXG08_STATUS2_AUX_ERR (0x01 << 3)
#define KXG08_STATUS2_WAKE_SLEEP_SLEEP_MODE (0x00 << 2)
#define KXG08_STATUS2_WAKE_SLEEP_WAKE_MODE (0x01 << 2)
// Gyroscope run flag.
#define KXG08_STATUS2_GYRO_RUN (0x01 << 0)
// Buffer full interrupt.
#define KXG08_INT2_SRC1_INT2_BFI (0x01 << 7)
// Buffer water mark interrupt.
#define KXG08_INT2_SRC1_INT2_WMI (0x01 << 6)
// Wake-up function interrupt.
#define KXG08_INT2_SRC1_INT2_WUFS (0x01 << 5)
// Back-to-sleep interrupt.
#define KXG08_INT2_SRC1_INT2_BTS (0x01 << 4)
// Aux2 data ready interrupt.
#define KXG08_INT2_SRC1_INT2_DRDY_AUX2 (0x01 << 3)
// Aux1 data ready interrupt.
#define KXG08_INT2_SRC1_INT2_DRDY_AUX1 (0x01 << 2)
// Accelerometer data ready interrupt.
#define KXG08_INT2_SRC1_INT2_DRDY_ACC (0x01 << 1)
// Gyro data ready interrupt.
#define KXG08_INT2_SRC1_INT2_DRDY_GYRO (0x01 << 0)
// Wake up event detected on x-axis, negative direction
#define KXG08_INT2_SRC2_INT2_XNWU (0x01 << 5)
// Wake up event detected on x-axis, positive direction.
#define KXG08_INT2_SRC2_INT2_XPWU (0x01 << 4)
// Wake up event detected on y-axis, negative direction
#define KXG08_INT2_SRC2_INT2_YNWU (0x01 << 3)
// Wake up event detected on y-axis, positive direction.
#define KXG08_INT2_SRC2_INT2_YPWU (0x01 << 2)
// Wake up event detected on z-axis, negative direction.
#define KXG08_INT2_SRC2_INT2_ZNWU (0x01 << 1)
// Wake up event detected on z-axis, positive direction.
#define KXG08_INT2_SRC2_INT2_ZPWU (0x01 << 0)
// x-axis, negative direction
#define KXG08_INT2_SRC3_INT2_XTLE (0x01 << 5)
// x-axis, positive direction.
#define KXG08_INT2_SRC3_INT2_XTRI (0x01 << 4)
// y-axis, negative direction
#define KXG08_INT2_SRC3_INT2_YTDO (0x01 << 3)
// y-axis, positive direction
#define KXG08_INT2_SRC3_INT2_YTUP (0x01 << 2)
// z-axis, negative direction.
#define KXG08_INT2_SRC3_INT2_ZTFD (0x01 << 1)
// z-axis, positive direction
#define KXG08_INT2_SRC3_INT2_ZTFU (0x01 << 0)
// Tilt position interrupt source.
#define KXG08_INT2_SRC4_INT2_TPS (0x01 << 3)
#define KXG08_INT2_SRC4_INT2_TDTS_NO_TAP_EVENT (0x00 << 1)
#define KXG08_INT2_SRC4_INT2_TDTS_SINGLE_TAP (0x01 << 1)
#define KXG08_INT2_SRC4_INT2_TDTS_DOUBLE_TAP (0x02 << 1)
// Free fall interrupt source.
#define KXG08_INT2_SRC4_INT2_FFS (0x01 << 0)
// Accelerometer low power mode enable
#define KXG08_ACCEL_ODR_LPMODEA (0x01 << 7)
// No Averaging
#define KXG08_ACCEL_ODR_NAVGA_NO_AVG (0x00 << 4)
// 2 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_2_SAMPLE_AVG (0x01 << 4)
// 4 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_4_SAMPLE_AVG (0x02 << 4)
// 8 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_8_SAMPLE_AVG (0x03 << 4)
// 16 Samples Averaged (default)
#define KXG08_ACCEL_ODR_NAVGA_16_SAMPLE_AVG (0x04 << 4)
// 32 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_32_SAMPLE_AVG (0x05 << 4)
// 64 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_64_SAMPLE_AVG (0x06 << 4)
// 128 Samples Averaged
#define KXG08_ACCEL_ODR_NAVGA_128_SAMPLE_AVG (0x07 << 4)
// 0.78Hz
#define KXG08_ACCEL_ODR_ODRA_0P781 (0x00 << 0)
// 1.563Hz
#define KXG08_ACCEL_ODR_ODRA_1P563 (0x01 << 0)
// 3.125Hz
#define KXG08_ACCEL_ODR_ODRA_3P125 (0x02 << 0)
// 6.25Hz
#define KXG08_ACCEL_ODR_ODRA_6P25 (0x03 << 0)
// 12.5Hz
#define KXG08_ACCEL_ODR_ODRA_12P5 (0x04 << 0)
// 25Hz
#define KXG08_ACCEL_ODR_ODRA_25 (0x05 << 0)
// 50Hz
#define KXG08_ACCEL_ODR_ODRA_50 (0x06 << 0)
// 100Hz
#define KXG08_ACCEL_ODR_ODRA_100 (0x07 << 0)
// 200Hz
#define KXG08_ACCEL_ODR_ODRA_200 (0x08 << 0)
// 400Hz
#define KXG08_ACCEL_ODR_ODRA_400 (0x09 << 0)
// 800Hz
#define KXG08_ACCEL_ODR_ODRA_800 (0x0A << 0)
// 1600Hz
#define KXG08_ACCEL_ODR_ODRA_1600 (0x0B << 0)
// 3200Hz
#define KXG08_ACCEL_ODR_ODRA_3200 (0x0C << 0)
// 6400Hz
#define KXG08_ACCEL_ODR_ODRA_6400 (0x0D << 0)
// 12800Hz
#define KXG08_ACCEL_ODR_ODRA_12800 (0x0E << 0)
// 25600Hz
#define KXG08_ACCEL_ODR_ODRA_25600 (0x0F << 0)
// Accelerometer self test polarity control.
#define KXG08_ACCEL_CTL_ACC_ST_POL (0x01 << 5)
// Accelerometer self test enable control.
#define KXG08_ACCEL_CTL_ACC_ST (0x01 << 4)
// BW = ODR/2
#define KXG08_ACCEL_CTL_ACC_BW_ODR_2 (0x00 << 3)
// BW = ODR/8
#define KXG08_ACCEL_CTL_ACC_BW_ODR_8 (0x01 << 3)
#define KXG08_ACCEL_CTL_ACC_FS_2G (0x00 << 0)
#define KXG08_ACCEL_CTL_ACC_FS_4G (0x01 << 0)
#define KXG08_ACCEL_CTL_ACC_FS_8G (0x02 << 0)
#define KXG08_ACCEL_CTL_ACC_FS_16G (0x03 << 0)
// Gyroscope low power mode enable.
#define KXG08_GYRO_ODR_LPMODEG (0x01 << 7)
#define KXG08_GYRO_ODR_NAVGG_NO_AVG (0x00 << 4)
#define KXG08_GYRO_ODR_NAVGG_2_SAMPLE_AVG (0x01 << 4)
#define KXG08_GYRO_ODR_NAVGG_4_SAMPLE_AVG (0x02 << 4)
#define KXG08_GYRO_ODR_NAVGG_8_SAMPLE_AVG (0x03 << 4)
#define KXG08_GYRO_ODR_NAVGG_16_SAMPLE_AVG (0x04 << 4)
#define KXG08_GYRO_ODR_NAVGG_32_SAMPLE_AVG (0x05 << 4)
#define KXG08_GYRO_ODR_NAVGG_64_SAMPLE_AVG (0x06 << 4)
#define KXG08_GYRO_ODR_NAVGG_128_SAMPLE_AVG (0x07 << 4)
// 0.78Hz
#define KXG08_GYRO_ODR_ODRG_0P781 (0x00 << 0)
// 1.563Hz
#define KXG08_GYRO_ODR_ODRG_1P563 (0x01 << 0)
// 3.125Hz
#define KXG08_GYRO_ODR_ODRG_3P125 (0x02 << 0)
// 6.25Hz
#define KXG08_GYRO_ODR_ODRG_6P25 (0x03 << 0)
// 12.5Hz
#define KXG08_GYRO_ODR_ODRG_12P5 (0x04 << 0)
// 25Hz
#define KXG08_GYRO_ODR_ODRG_25 (0x05 << 0)
// 50Hz
#define KXG08_GYRO_ODR_ODRG_50 (0x06 << 0)
// 100Hz
#define KXG08_GYRO_ODR_ODRG_100 (0x07 << 0)
// 200Hz
#define KXG08_GYRO_ODR_ODRG_200 (0x08 << 0)
// 400Hz
#define KXG08_GYRO_ODR_ODRG_400 (0x09 << 0)
// 800Hz
#define KXG08_GYRO_ODR_ODRG_800 (0x0A << 0)
// 1600Hz
#define KXG08_GYRO_ODR_ODRG_1600 (0x0B << 0)
// 3200Hz
#define KXG08_GYRO_ODR_ODRG_3200 (0x0C << 0)
// 6400Hz
#define KXG08_GYRO_ODR_ODRG_6400 (0x0D << 0)
// 12800Hz
#define KXG08_GYRO_ODR_ODRG_12800 (0x0E << 0)
// 12800Hz
#define KXG08_GYRO_ODR_ODRG_12800_1 (0x0F << 0)
// BW = ODR/8
#define KXG08_GYRO_CTL_GYRO_BW_ODR_8 (0x00 << 3)
// BW = ODR/2
#define KXG08_GYRO_CTL_GYRO_BW_ODR_2 (0x01 << 3)
#define KXG08_GYRO_CTL_GYRO_FS_64 (0x00 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_128 (0x01 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_256 (0x02 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_512 (0x03 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_1024 (0x04 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_2048 (0x05 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_TBD1 (0x06 << 0)
#define KXG08_GYRO_CTL_GYRO_FS_TBD2 (0x07 << 0)
// Active high enable for INT2 pin.
#define KXG08_INT_PIN_CTL_IEN2 (0x01 << 7)
#define KXG08_INT_PIN_CTL_IEA2_ACTIVE_LOW (0x00 << 6)
#define KXG08_INT_PIN_CTL_IEA2_ACTIVE_HIGH (0x01 << 6)
// Latched
#define KXG08_INT_PIN_CTL_IEL2_LATCHED (0x00 << 4)
// Pulsed 50uS
#define KXG08_INT_PIN_CTL_IEL2_PULSED_50US (0x01 << 4)
// Pulsed 200uS
#define KXG08_INT_PIN_CTL_IEL2_PULSED_200US (0x02 << 4)
// Realtime
#define KXG08_INT_PIN_CTL_IEL2_REALTIME (0x03 << 4)
// Active high enable for INT1 pin.
#define KXG08_INT_PIN_CTL_IEN1 (0x01 << 3)
#define KXG08_INT_PIN_CTL_IEA1_ACTIVE_LOW (0x00 << 2)
#define KXG08_INT_PIN_CTL_IEA1_ACTIVE_HIGH (0x01 << 2)
// Latched
#define KXG08_INT_PIN_CTL_IEL1_LATCHED (0x00 << 0)
// Pulsed 50uS
#define KXG08_INT_PIN_CTL_IEL1_PULSED_50US (0x01 << 0)
// Pulsed 200uS
#define KXG08_INT_PIN_CTL_IEL1_PULSED_200US (0x02 << 0)
// Realtime
#define KXG08_INT_PIN_CTL_IEL1_REALTIME (0x03 << 0)
// Buffer Full Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_BFI_P1 (0x01 << 7)
// Water Mark Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_WMI_P1 (0x01 << 6)
// Wake Up Function Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_WUF_P1 (0x01 << 5)
// Back To Sleep Function Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_BTS_P1 (0x01 << 4)
// Data Ready Aux2 Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_DRDY_AUX2_P1 (0x01 << 3)
// Data Ready AUX1 Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_DRDY_AUX1_P1 (0x01 << 2)
// Data Ready Accelerometer Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_DRDY_ACC_P1 (0x01 << 1)
// Data Ready Gyroscope Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL1_DRDY_GYRO_P1 (0x01 << 0)
// Buffer Full Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_BFI_P2 (0x01 << 7)
// Water Mark Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_WMI_P2 (0x01 << 6)
// Wake-up Function Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_WUF_P2 (0x01 << 5)
// Back-to-sleep Function Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_BTS_P2 (0x01 << 4)
// Data Ready Aux2 Interrupt for INT2 pin.
#define KXG08_INT_PIN_SEL2_DRDY_AUX2_P2 (0x01 << 3)
// Data Ready AUX1 Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_DRDY_AUX1_P2 (0x01 << 2)
// Data Ready Accelerometer Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_DRDY_ACC_P2 (0x01 << 1)
// Data Ready Gyroscope Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL2_DRDY_GYRO_P2 (0x01 << 0)
// Tilt Position Interrupt for INT2 pin
#define KXG08_INT_PIN_SEL3_TPS_P2 (0x01 << 7)
// Tap/Double Tap Interrupt for INT2 pin.
#define KXG08_INT_PIN_SEL3_TDS_P2 (0x01 << 5)
// Free fall Interrupt for INT2 pin.
#define KXG08_INT_PIN_SEL3_FFS_P2 (0x01 << 4)
// Tilt Position Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL3_TPS_P1 (0x01 << 3)
// Tap/Double Tap Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL3_TDS_P1 (0x01 << 1)
// Free fall Interrupt for INT1 pin.
#define KXG08_INT_PIN_SEL3_FFS_P1 (0x01 << 0)
// Buffer Full Interrupt enable/mask bit.
#define KXG08_INT_MASK1_BFIE (0x01 << 7)
// Water Mark Interrupt enable/mask bit.
#define KXG08_INT_MASK1_WMIE (0x01 << 6)
// Data Ready Aux2 Interrupt enable/mask bit.
#define KXG08_INT_MASK1_DRDY_AUX2 (0x01 << 3)
// Data Ready AUX1 Interrupt enable/mask bit.
#define KXG08_INT_MASK1_DRDY_AUX1 (0x01 << 2)
// Data Ready Accelerometer Interrupt enable/mask bit.
#define KXG08_INT_MASK1_DRDY_ACC (0x01 << 1)
// Data Ready Gyroscope Interrupt enable/mask bit.
#define KXG08_INT_MASK1_DRDY_GYRO (0x01 << 0)
// x negative (x-) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_XNWUE (0x01 << 5)
// x positive (x+) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_XPWUE (0x01 << 4)
// y negative (y-) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_YNWUE (0x01 << 3)
// y positive (y+) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_YPWUE (0x01 << 2)
// z negative (z-) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_ZNWUE (0x01 << 1)
// z positive (z+) mask for WUF/BTS, 0=disable, 1=enable.
#define KXG08_INT_MASK2_ZPWUE (0x01 << 0)
// x negative (x-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TLEM (0x01 << 5)
// x positive (x+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TRIM (0x01 << 4)
// y negative (y-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TDOM (0x01 << 3)
// y positive (y+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TUPM (0x01 << 2)
// z negative (z-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TFDM (0x01 << 1)
// z positive (z+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK3_TFUM (0x01 << 0)
// x negative (x-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TLEM (0x01 << 5)
// x positive (x+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TRIM (0x01 << 4)
// y negative (y-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TDOM (0x01 << 3)
// y positive (y+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TUPM (0x01 << 2)
// z negative (z-): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TFDM (0x01 << 1)
// z positive (z+): 0 = disabled, 1 = enabled
#define KXG08_INT_MASK4_TFUM (0x01 << 0)
// INT2 = interrupt-2.
#define KXG08_FSYNC_CTL_FSYNC_TRIG_INT2 (0x00 << 6)
// INT2 = fsync function
#define KXG08_FSYNC_CTL_FSYNC_TRIG_FSYNC (0x01 << 6)
// FSYNC is disabled. SYNC pin is tri-stated.
#define KXG08_FSYNC_CTL_FSYNC_MODE_DISABLED (0x00 << 4)
// FSYNC is enabled. Sync pin is configured as input pin. Buffer is updated in sync with external clock applied at SYNC pin.
#define KXG08_FSYNC_CTL_FSYNC_MODE_INPUT_EXT (0x01 << 4)
// FSYNC is enabled. Sync pin is configured as input pin. State of SYNC pin is stored in selected sensor's LSB bit.
#define KXG08_FSYNC_CTL_FSYNC_MODE_INPUT (0x02 << 4)
// FSYNC is disabled. SYNC pin is configured as output pin.
#define KXG08_FSYNC_CTL_FSYNC_MODE_OUTPUT (0x03 << 4)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL000 (0x00 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL001 (0x01 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL010 (0x02 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL011 (0x03 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL100 (0x04 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL101 (0x05 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL110 (0x06 << 0)
// Definition according FSYNC_MODE selection
#define KXG08_FSYNC_CTL_FSYNC_SEL_SEL111 (0x07 << 0)
// Absolute threshold. ASIC compares current output to threshold.
#define KXG08_WAKE_SLEEP_CTL1_TH_MODE_ABSOLUTE_THRESHOLD (0x00 << 5)
// Relative threshold. ASIC compares difference between current output and previous output to threshold.
#define KXG08_WAKE_SLEEP_CTL1_TH_MODE_RELATIVE_THRESHOLD (0x01 << 5)
// Counter is cleared once activity level is outside the threshold.
#define KXG08_WAKE_SLEEP_CTL1_C_MODE_COUNTER_CLEAR (0x00 << 4)
// Counter is decremented by one when activity level is outside the threshold.
#define KXG08_WAKE_SLEEP_CTL1_C_MODE_COUNTER_DECREMENT (0x01 << 4)
// 0.78Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_0P781 (0x00 << 0)
// 1.563Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_1P563 (0x01 << 0)
// 3.125Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_3P125 (0x02 << 0)
// 6.25Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_6P25 (0x03 << 0)
// 12.5Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_12P5 (0x04 << 0)
// 25Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_25 (0x05 << 0)
// 50Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_50 (0x06 << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL1_OWUF_100 (0x07 << 0)
// Active high back-to-sleep function enable
#define KXG08_WAKE_SLEEP_CTL2_BTS_EN (0x01 << 7)
// Active high wake-up function enable.
#define KXG08_WAKE_SLEEP_CTL2_WUF_EN (0x01 << 6)
// Forces transition to sleep state.
#define KXG08_WAKE_SLEEP_CTL2_MAN_SLEEP (0x01 << 5)
// Forces transition to wake state.
#define KXG08_WAKE_SLEEP_CTL2_MAN_WAKE (0x01 << 4)
#define KXG08_WAKE_SLEEP_CTL2_OBTS_0P048828 (0x00 << 0)
#define KXG08_WAKE_SLEEP_CTL2_OBTS_0P097656 (0x01 << 0)
#define KXG08_WAKE_SLEEP_CTL2_OBTS_0P19531 (0x02 << 0)
#define KXG08_WAKE_SLEEP_CTL2_OBTS_0P3906 (0x03 << 0)
// 0.78Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_0P781 (0x04 << 0)
// 1.563Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_1P563 (0x05 << 0)
// 3.125Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_3P125 (0x06 << 0)
// 6.25Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_6P25 (0x07 << 0)
// 12.5Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_12P5 (0x08 << 0)
// 25Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_25 (0x09 << 0)
// 50Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_50 (0x0A << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_100 (0x0B << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_100_2 (0x0C << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_100_3 (0x0D << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_100_4 (0x0E << 0)
// 100Hz
#define KXG08_WAKE_SLEEP_CTL2_OBTS_100_5 (0x0F << 0)
// Defines control bit polarity for aux2 enable/disable command sequences.
#define KXG08_AUX_I2C_CTL_REG_AUX_CTL_POL2 (0x01 << 5)
// Defines control bit polarity for aux1 enable/disable command sequences.
#define KXG08_AUX_I2C_CTL_REG_AUX_CTL_POL1 (0x01 << 4)
// 100kHz
#define KXG08_AUX_I2C_CTL_REG_AUX_BUS_SPD_100 (0x00 << 3)
// 400kHz
#define KXG08_AUX_I2C_CTL_REG_AUX_BUS_SPD_400 (0x01 << 3)
#define KXG08_AUX_I2C_CTL_REG_AUX_PULL_UP_DISABLED (0x00 << 2)
#define KXG08_AUX_I2C_CTL_REG_AUX_PULL_UP_ENABLED (0x01 << 2)
#define KXG08_AUX_I2C_CTL_REG_AUX_BYPASS (0x01 << 1)
#define KXG08_AUX_I2C_ODR_AUX1_D_0 (0x00 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_1 (0x01 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_2 (0x02 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_3 (0x03 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_4 (0x04 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_5 (0x05 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_6 (0x06 << 4)
#define KXG08_AUX_I2C_ODR_AUX1_D_DNE (0x07 << 4)
// 0.78Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_0P781 (0x00 << 0)
// 1.563Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1P563 (0x01 << 0)
// 3.125Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_3P125 (0x02 << 0)
// 6.25Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_6P25 (0x03 << 0)
// 12.5Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_12P5 (0x04 << 0)
// 25Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_25 (0x05 << 0)
// 50Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_50 (0x06 << 0)
// 100Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_100 (0x07 << 0)
// 200Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_200 (0x08 << 0)
// 400Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_400 (0x09 << 0)
// 800Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_800 (0x0A << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1600 (0x0B << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1600_1 (0x0C << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1600_2 (0x0D << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1600_3 (0x0E << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR_AUX1ODR_1600_4 (0x0F << 0)
#define KXG08_AUX_I2C_ODR2_AUX2_D_0 (0x00 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_1 (0x01 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_2 (0x02 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_3 (0x03 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_4 (0x04 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_5 (0x05 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_6 (0x06 << 4)
#define KXG08_AUX_I2C_ODR2_AUX2_D_DNE (0x07 << 4)
// 0.78Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_0P781 (0x00 << 0)
// 1.563Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1P563 (0x01 << 0)
// 3.125Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_3P125 (0x02 << 0)
// 6.25Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_6P25 (0x03 << 0)
// 12.5Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_12P5 (0x04 << 0)
// 25Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_25 (0x05 << 0)
// 50Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_50 (0x06 << 0)
// 100Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_100 (0x07 << 0)
// 200Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_200 (0x08 << 0)
// 400Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_400 (0x09 << 0)
// 800Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_800 (0x0A << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1600 (0x0B << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1600_1 (0x0C << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1600_2 (0x0D << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1600_3 (0x0E << 0)
// 1600Hz
#define KXG08_AUX_I2C_ODR2_AUX2ODR_1600_4 (0x0F << 0)
// 12.5Hz
#define KXG08_TILT_TAP_ODR_OTDT_12P5 (0x00 << 3)
// 25Hz
#define KXG08_TILT_TAP_ODR_OTDT_25 (0x01 << 3)
// 50Hz
#define KXG08_TILT_TAP_ODR_OTDT_50 (0x02 << 3)
// 100Hz
#define KXG08_TILT_TAP_ODR_OTDT_100 (0x03 << 3)
// 200Hz
#define KXG08_TILT_TAP_ODR_OTDT_200 (0x04 << 3)
// 400Hz
#define KXG08_TILT_TAP_ODR_OTDT_400 (0x05 << 3)
// 800Hz
#define KXG08_TILT_TAP_ODR_OTDT_800 (0x06 << 3)
// 1600Hz
#define KXG08_TILT_TAP_ODR_OTDT_1600 (0x07 << 3)
// 1.563Hz
#define KXG08_TILT_TAP_ODR_OTP_1P563 (0x00 << 0)
// 3.125Hz
#define KXG08_TILT_TAP_ODR_OTP_3P125 (0x01 << 0)
// 6.25Hz
#define KXG08_TILT_TAP_ODR_OTP_6P25 (0x02 << 0)
// 12.5Hz
#define KXG08_TILT_TAP_ODR_OTP_12P5 (0x03 << 0)
// 25Hz
#define KXG08_TILT_TAP_ODR_OTP_25 (0x04 << 0)
// 50Hz
#define KXG08_TILT_TAP_ODR_OTP_50 (0x05 << 0)
// 50Hz
#define KXG08_TILT_TAP_ODR_OTP_50_1 (0x06 << 0)
// 50Hz
#define KXG08_TILT_TAP_ODR_OTP_50_2 (0x07 << 0)
// enables/disables the double tap interrupt
#define KXG08_TDTRC_DTRE (0x01 << 1)
// enables/disables single tap interrupt
#define KXG08_TDTRC_STRE (0x01 << 0)
// Free fall engine enable
#define KXG08_FFCTL_FFIE (0x01 << 7)
#define KXG08_FFCTL_ULMODE_LATCHED (0x00 << 6)
#define KXG08_FFCTL_ULMODE_UNLATCHED (0x01 << 6)
// count up/down
#define KXG08_FFCTL_DCRM_UP_DOWN (0x00 << 3)
// count up/reset
#define KXG08_FFCTL_DCRM_UP_RESET (0x01 << 3)
// 12.5Hz
#define KXG08_FFCTL_OFFI_12P5 (0x04 << 0)
// 25Hz
#define KXG08_FFCTL_OFFI_25 (0x05 << 0)
// 50Hz
#define KXG08_FFCTL_OFFI_50 (0x06 << 0)
// 100Hz
#define KXG08_FFCTL_OFFI_100 (0x07 << 0)
// 200Hz
#define KXG08_FFCTL_OFFI_200 (0x08 << 0)
// 400Hz
#define KXG08_FFCTL_OFFI_400 (0x09 << 0)
// 800Hz
#define KXG08_FFCTL_OFFI_800 (0x0A << 0)
// 1600Hz
#define KXG08_FFCTL_OFFI_1600 (0x0B << 0)
// initiates software reset, which performs the RAM reboot routine.
#define KXG08_CTL_REG_1_SRST (0x01 << 7)
// Tilt position engine enable.
#define KXG08_CTL_REG_1_TILT_EN (0x01 << 3)
// Tap/Double Tap engine enable.
#define KXG08_CTL_REG_1_TAP_EN (0x01 << 2)
// Timestamp mode enable.
#define KXG08_CTL_REG_1_CONT_TIME_EN (0x01 << 0)
// Active high I2C disable bit
#define KXG08_STDBY_I2C_DIS (0x01 << 7)
// Temperature sensor is enabled.
#define KXG08_STDBY_TEMP_STDBY_ENABLED (0x00 << 5)
// Temperature sensor is disabled.
#define KXG08_STDBY_TEMP_STDBY_DISABLED (0x01 << 5)
// Aux2 sensor is enabled.
#define KXG08_STDBY_AUX2_STDBY_ENABLED (0x00 << 4)
// Aux2 sensor is disabled.
#define KXG08_STDBY_AUX2_STDBY_DISABLED (0x01 << 4)
// Aux1 sensor is enabled.
#define KXG08_STDBY_AUX1_STDBY_ENABLED (0x00 << 3)
// Aux1 sensor is disabled.
#define KXG08_STDBY_AUX1_STDBY_DISABLED (0x01 << 3)
// Gyro fast start function is disabled.
#define KXG08_STDBY_GYRO_FSTART_DISABLED (0x00 << 2)
// Gyro fast start function is enabled.
#define KXG08_STDBY_GYRO_FSTART_ENABLED (0x01 << 2)
// Gyro sensor is enabled.
#define KXG08_STDBY_GYRO_STDBY_ENABLED (0x00 << 1)
// Gyro sensor is disabled.
#define KXG08_STDBY_GYRO_STDBY_DISABLED (0x01 << 1)
// Accelerometer sensor is enabled.
#define KXG08_STDBY_ACC_STDBY_ENABLED (0x00 << 0)
// Accelerometer sensor is disabled.
#define KXG08_STDBY_ACC_STDBY_DISABLED (0x01 << 0)
#define KXG08_BUF_CTL1_BUF_TEMP (0x01 << 6)
#define KXG08_BUF_CTL1_BUF_ACC_X (0x01 << 5)
#define KXG08_BUF_CTL1_BUF_ACC_Y (0x01 << 4)
#define KXG08_BUF_CTL1_BUF_ACC_Z (0x01 << 3)
#define KXG08_BUF_CTL1_BUF_GYR_X (0x01 << 2)
#define KXG08_BUF_CTL1_BUF_GYR_Y (0x01 << 1)
#define KXG08_BUF_CTL1_BUF_GYR_Z (0x01 << 0)
#define KXG08_BUF_CTL2_BUF_AUX2 (0x01 << 1)
#define KXG08_BUF_CTL2_BUF_AUX1 (0x01 << 0)
// controls activation of the sample buffer.
#define KXG08_BUF_EN_BUFE (0x01 << 7)
// Active high buffer times stamp enable.
#define KXG08_BUF_EN_BUF_TIME_EN (0x01 << 4)
// The buffer collects 4096 bytes of data until full, collecting new data only when the buffer is not full.
#define KXG08_BUF_EN_BUF_M_FIFO (0x00 << 0)
// The buffer holds the last 4096 bytes of data. Once the buffer is full, the oldest data is discarded to make room for newer data.
#define KXG08_BUF_EN_BUF_M_STREAM (0x01 << 0)
// When a trigger event occurs (logic high input on TRIG pin), the buffer holds the last data set of SMP[11:0] samples
#define KXG08_BUF_EN_BUF_M_TRIGGER (0x02 << 0)
#define KXG08_BUF_EN_BUF_M_NOT_VALID (0x03 << 0)
// reports the status of the buffers trigger function if this mode has been selected.
#define KXG08_BUF_STATUS_BUF_TRIG (0x01 << 7)
// WHO_AM_I -value -2080 version
#define KXG08_2080_WHO_AM_I_WIA_ID (0x26 << 0)
// WHO_AM_I -value -1080 version
#define KXG07_1080_WHO_AM_I_WIA_ID (0x29 << 0)
// WHO_AM_I -value -2080 version
#define KXG07_2080_WHO_AM_I_WIA_ID (0x25 << 0)
// WHO_AM_I -value -3001 version
#define KXG07_3001_WHO_AM_I_WIA_ID (0x2F << 0)
 /*registers bit masks */
#define KXG08_BUF_SMPLEV_L_SMP_LEV3_0_MASK 0xF0
#define KXG08_BUF_SMPLEV_H_SMP_LEV11_4_MASK 0xFF
// Detailed aux1 communication status.
#define KXG08_AUX_STATUS_AUX1ST_MASK 0x03
// Detailed aux1 communication status.
#define KXG08_AUX_STATUS_AUX2ST_MASK 0x30

#define KXG08_WHO_AM_I_WIA_MASK 0xFF
// Wake/sleep status flag
#define KXG08_STATUS1_WAKE_SLEEP_MASK 0x04
// Tap/DoubleTap interrupt source.
#define KXG08_INT1_SRC4_INT1_TDTS_MASK 0x06
// Wake/sleep status flag
#define KXG08_STATUS2_WAKE_SLEEP_MASK 0x04

#define KXG08_INT2_SRC4_INT2_TDTS_MASK 0x06
// Accelerometer OSR control.
#define KXG08_ACCEL_ODR_NAVGA_MASK 0x70

#define KXG08_ACCEL_ODR_ODRA_MASK 0x0F
// Accelerometer bandwidth control.
#define KXG08_ACCEL_CTL_ACC_BW_MASK 0x08
// Accelerometer full scale range select.
#define KXG08_ACCEL_CTL_ACC_FS_MASK 0x03

#define KXG08_GYRO_ODR_NAVGG_MASK 0x70
#define KXG08_GYRO_ODR_ODRG_MASK 0x0F

#define KXG08_GYRO_CTL_GYRO_BW_MASK 0x08

#define KXG08_GYRO_CTL_GYRO_FS_MASK 0x07
// Interrupt polarity select for INT2 pin.
#define KXG08_INT_PIN_CTL_IEA2_MASK 0x40
#define KXG08_INT_PIN_CTL_IEL2_MASK 0x30
// Interrupt polarity select for INT1 pin.
#define KXG08_INT_PIN_CTL_IEA1_MASK 0x04
#define KXG08_INT_PIN_CTL_IEL1_MASK 0x03
// Defines INT2 and SYNC_TRIG pin functionality
#define KXG08_FSYNC_CTL_FSYNC_TRIG_MASK 0x40
// FSYNC enable and mode select.
#define KXG08_FSYNC_CTL_FSYNC_MODE_MASK 0x30

#define KXG08_FSYNC_CTL_FSYNC_SEL_MASK 0x07

#define KXG08_WAKE_SLEEP_CTL1_TH_MODE_MASK 0x20
// Defines de-bounce counter clear mode.
#define KXG08_WAKE_SLEEP_CTL1_C_MODE_MASK 0x10
// sets the Output Data Rate for the Wake-up (motion detection).
#define KXG08_WAKE_SLEEP_CTL1_OWUF_MASK 0x07
// sets the Output Data Rate for the Back to Sleep (BTS).
#define KXG08_WAKE_SLEEP_CTL2_OBTS_MASK 0x0F
// Sets I2C bus speed.
#define KXG08_AUX_I2C_CTL_REG_AUX_BUS_SPD_MASK 0x08
// Active pullup
#define KXG08_AUX_I2C_CTL_REG_AUX_PULL_UP_MASK 0x04
#define KXG08_AUX_I2C_ODR_AUX1_D_MASK 0x70
#define KXG08_AUX_I2C_ODR_AUX1ODR_MASK 0x0F
// Number of bytes read back via Auxiliary I2C bus from device
#define KXG08_AUX_I2C_ODR2_AUX2_D_MASK 0x70
#define KXG08_AUX_I2C_ODR2_AUX2ODR_MASK 0x0F

#define KXG08_TILT_TAP_ODR_OTDT_MASK 0x38

#define KXG08_TILT_TAP_ODR_OTP_MASK 0x07
// Free fall interrupt latch/un-latch control
#define KXG08_FFCTL_ULMODE_MASK 0x40
#define KXG08_FFCTL_DCRM_MASK 0x08

#define KXG08_FFCTL_OFFI_MASK 0x07
// Active low Temperature sensor enable.
#define KXG08_STDBY_TEMP_STDBY_MASK 0x20
// Active low aux2 sensor enable.
#define KXG08_STDBY_AUX2_STDBY_MASK 0x10
// Active low aux1 sensor enable.
#define KXG08_STDBY_AUX1_STDBY_MASK 0x08
// Active high gyroscope fast start sensor enable
#define KXG08_STDBY_GYRO_FSTART_MASK 0x04
// Active low gyroscope sensor enable.
#define KXG08_STDBY_GYRO_STDBY_MASK 0x02
// Active low Accelerometer sensor enable.
#define KXG08_STDBY_ACC_STDBY_MASK 0x01
#define KXG08_BUF_WMITH_L_SMP_TH13_0_MASK 0xF0
#define KXG08_BUF_WMITH_H_SMP_TH11_4_MASK 0xFF
#define KXG08_BUF_TRIGTH_L_TRIG_TH3_0_MASK 0xF0
#define KXG08_BUF_TRIGTH_H_TRIG_TH11_4_MASK 0xFF
// selects the operating mode of the sample buffer
#define KXG08_BUF_EN_BUF_M_MASK 0x03

#define KXG08_2080_WHO_AM_I_WIA_MASK 0xFF

#define KXG07_1080_WHO_AM_I_WIA_MASK 0xFF

#define KXG07_2080_WHO_AM_I_WIA_MASK 0xFF

#define KXG07_3001_WHO_AM_I_WIA_MASK 0xFF
#endif

