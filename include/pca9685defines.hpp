/**
 * @copyright
 * MIT License
 *
 * Copyright (c) 2017 Car4Tegra
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file pca9685.hpp
 * @date 09.04.2017
 *
 * @brief This file contains definitions for the PCA9685 I2C PWM driver
 *
 * @details
 * The values for the defines below could be found in the PCA9685 datasheet from NXP
 * (http://cache.nxp.com/documents/data_sheet/PCA9685.pdf?pspll=1)
 *
 * @version 0.1 - 09.04.2017 - File created
 */


#ifndef PCA9685DEFINES_HPP
#define PCA9685DEFINES_HPP


// PCA9685 register addresses (table 4 in NXP datasheet)

#define PCA9685_REG_MODE1           0x00     ///< Mode register 1
#define PCA9685_REG_MODE2           0x01     ///< Mode register 2
#define PCA9685_REG_SUBADR1         0x02     ///< I2C-bus subaddress 1
#define PCA9685_REG_SUBADR2         0x03     ///< I2C-bus subaddress 2
#define PCA9685_REG_SUBADR3         0x04     ///< I2C-bus subaddress 3
#define PCA9685_REG_ALLCALLADR      0x05     ///< LED All Call I2C-bus address

#define PCA9685_REG_LED0_ON_L       0x06     ///< LED0 output and brightness control byte 0
#define PCA9685_REG_LED0_ON_H       0x07     ///< LED0 output and brightness control byte 1
#define PCA9685_REG_LED0_OFF_L      0x08     ///< LED0 output and brightness control byte 2
#define PCA9685_REG_LED0_OFF_H      0x09     ///< LED0 output and brightness control byte 3

#define PCA9685_REG_LED1_ON_L       0x0A     ///< LED1 output and brightness control byte 0
#define PCA9685_REG_LED1_ON_H       0x0B     ///< LED1 output and brightness control byte 1
#define PCA9685_REG_LED1_OFF_L      0x0C     ///< LED1 output and brightness control byte 2
#define PCA9685_REG_LED1_OFF_H      0x0D     ///< LED1 output and brightness control byte 3

#define PCA9685_REG_LED2_ON_L       0x0E     ///< LED2 output and brightness control byte 0
#define PCA9685_REG_LED2_ON_H       0x0F     ///< LED2 output and brightness control byte 1
#define PCA9685_REG_LED2_OFF_L      0x10     ///< LED2 output and brightness control byte 2
#define PCA9685_REG_LED2_OFF_H      0x11     ///< LED2 output and brightness control byte 3

#define PCA9685_REG_LED3_ON_L       0x12     ///< LED3 output and brightness control byte 0
#define PCA9685_REG_LED3_ON_H       0x13     ///< LED3 output and brightness control byte 1
#define PCA9685_REG_LED3_OFF_L      0x14     ///< LED3 output and brightness control byte 2
#define PCA9685_REG_LED3_OFF_H      0x15     ///< LED3 output and brightness control byte 3

#define PCA9685_REG_LED4_ON_L       0x16     ///< LED4 output and brightness control byte 0
#define PCA9685_REG_LED4_ON_H       0x17     ///< LED4 output and brightness control byte 1
#define PCA9685_REG_LED4_OFF_L      0x18     ///< LED4 output and brightness control byte 2
#define PCA9685_REG_LED4_OFF_H      0x19     ///< LED4 output and brightness control byte 3

#define PCA9685_REG_LED5_ON_L       0x1A     ///< LED5 output and brightness control byte 0
#define PCA9685_REG_LED5_ON_H       0x1B     ///< LED5 output and brightness control byte 1
#define PCA9685_REG_LED5_OFF_L      0x1C     ///< LED5 output and brightness control byte 2
#define PCA9685_REG_LED5_OFF_H      0x1D     ///< LED5 output and brightness control byte 3

#define PCA9685_REG_LED6_ON_L       0x1E     ///< LED6 output and brightness control byte 0
#define PCA9685_REG_LED6_ON_H       0x1F     ///< LED6 output and brightness control byte 1
#define PCA9685_REG_LED6_OFF_L      0x20     ///< LED6 output and brightness control byte 2
#define PCA9685_REG_LED6_OFF_H      0x21     ///< LED6 output and brightness control byte 3

#define PCA9685_REG_LED7_ON_L       0x22     ///< LED7 output and brightness control byte 0
#define PCA9685_REG_LED7_ON_H       0x23     ///< LED7 output and brightness control byte 1
#define PCA9685_REG_LED7_OFF_L      0x24     ///< LED7 output and brightness control byte 2
#define PCA9685_REG_LED7_OFF_H      0x25     ///< LED7 output and brightness control byte 3

#define PCA9685_REG_LED8_ON_L       0x26     ///< LED8 output and brightness control byte 0
#define PCA9685_REG_LED8_ON_H       0x27     ///< LED8 output and brightness control byte 1
#define PCA9685_REG_LED8_OFF_L      0x28     ///< LED8 output and brightness control byte 2
#define PCA9685_REG_LED8_OFF_H      0x29     ///< LED8 output and brightness control byte 3

#define PCA9685_REG_LED9_ON_L       0x2A     ///< LED9 output and brightness control byte 0
#define PCA9685_REG_LED9_ON_H       0x2B     ///< LED9 output and brightness control byte 1
#define PCA9685_REG_LED9_OFF_L      0x2C     ///< LED9 output and brightness control byte 2
#define PCA9685_REG_LED9_OFF_H      0x2D     ///< LED9 output and brightness control byte 3

#define PCA9685_REG_LED10_ON_L      0x2E     ///< LED10 output and brightness control byte 0
#define PCA9685_REG_LED10_ON_H      0x2F     ///< LED10 output and brightness control byte 1
#define PCA9685_REG_LED10_OFF_L     0x30     ///< LED10 output and brightness control byte 2
#define PCA9685_REG_LED10_OFF_H     0x31     ///< LED10 output and brightness control byte 3

#define PCA9685_REG_LED11_ON_L      0x32     ///< LED11 output and brightness control byte 0
#define PCA9685_REG_LED11_ON_H      0x33     ///< LED11 output and brightness control byte 1
#define PCA9685_REG_LED11_OFF_L     0x34     ///< LED11 output and brightness control byte 2
#define PCA9685_REG_LED11_OFF_H     0x35     ///< LED11 output and brightness control byte 3

#define PCA9685_REG_LED12_ON_L      0x36     ///< LED12 output and brightness control byte 0
#define PCA9685_REG_LED12_ON_H      0x37     ///< LED12 output and brightness control byte 1
#define PCA9685_REG_LED12_OFF_L     0x38     ///< LED12 output and brightness control byte 2
#define PCA9685_REG_LED12_OFF_H     0x39     ///< LED12 output and brightness control byte 3

#define PCA9685_REG_LED13_ON_L      0x3A     ///< LED13 output and brightness control byte 0
#define PCA9685_REG_LED13_ON_H      0x3B     ///< LED13 output and brightness control byte 1
#define PCA9685_REG_LED13_OFF_L     0x3C     ///< LED13 output and brightness control byte 2
#define PCA9685_REG_LED13_OFF_H     0x3D     ///< LED13 output and brightness control byte 3

#define PCA9685_REG_LED14_ON_L      0x3E     ///< LED14 output and brightness control byte 0
#define PCA9685_REG_LED14_ON_H      0x3F     ///< LED14 output and brightness control byte 1
#define PCA9685_REG_LED14_OFF_L     0x40     ///< LED14 output and brightness control byte 2
#define PCA9685_REG_LED14_OFF_H     0x41     ///< LED14 output and brightness control byte 3

#define PCA9685_REG_LED15_ON_L      0x42     ///< LED15 output and brightness control byte 0
#define PCA9685_REG_LED15_ON_H      0x43     ///< LED15 output and brightness control byte 1
#define PCA9685_REG_LED15_OFF_L     0x44     ///< LED15 output and brightness control byte 2
#define PCA9685_REG_LED15_OFF_H     0x45     ///< LED15 output and brightness control byte 3

#define PCA9685_REG_ALL_LED_ON_L    0xFA     ///< load all the LEDn_ON registers, byte 0
#define PCA9685_REG_ALL_LED_ON_H    0xFB     ///< load all the LEDn_ON registers, byte 1
#define PCA9685_REG_ALL_LED_OFF_L   0xFC     ///< load all the LEDn_OFF registers, byte 0
#define PCA9685_REG_ALL_LED_OFF_H   0xFD     ///< load all the LEDn_OFF registers, byte 1

#define PCA9685_REG_PRE_SCALE       0xFE     ///< prescaler for PWM output frequency
#define PCA9685_REG_TESTMODE        0xFF     ///< defines the test mode to be entered


// MODE1 register bit masks (table 5 in NXP datasheet)

#define PCA9685_MODE1_RESTART       0b10000000     ///< Bit 7
#define PCA9685_MODE1_EXTCLK        0b01000000     ///< Bit 6
#define PCA9685_MODE1_AI            0b00100000     ///< Bit 5
#define PCA9685_MODE1_SLEEP         0b00010000     ///< Bit 4
#define PCA9685_MODE1_SUB1          0b00001000     ///< Bit 3
#define PCA9685_MODE1_SUB2          0b00000100     ///< Bit 2
#define PCA9685_MODE1_SUB3          0b00000010     ///< Bit 1
#define PCA9685_MODE1_ALLCALL       0b00000001     ///< Bit 0


// MODE2 register bit masks (table 6 in NXP datasheet)

#define PCA9685_MODE2_INVRT         0b00010000     ///< Bit 4
#define PCA9685_MODE2_OCH           0b00001000     ///< Bit 3
#define PCA9685_MODE2_OUTDRV        0b00000100     ///< Bit 2
#define PCA9685_MODE2_OUTNE_1       0b00000010     ///< Bit 1
#define PCA9685_MODE2_OUTNE_0       0b00000001     ///< Bit 0


#endif // PCA9685DEFINES_HPP

