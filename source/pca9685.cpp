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
 * @file pca9685.cpp
 * @date 05.04.2017
 *
 * @brief This file contains the definition of class PCA9685 at namespace CAR4TEGRA
 *
 * @version 0.1 - 09.04.2017 - File created
 */


// std includes
#include <unistd.h>
#include <math.h>
#include <exception>
#include <stdexcept>


// Car4Tegra includes
#include "include/pca9685.hpp"


namespace CAR4TEGRA
{
   PCA9685::PCA9685()
      : mpI2CDevice(std::make_unique<CAR4TEGRA::I2cDevice>()), mAddress(0x00), mBusName("")
   {
      // nothing to do
   }


   PCA9685::~PCA9685()
   {
      this->close();
   }


   void PCA9685::openDevice(const std::string arBusName, int aAddress)
   {
      mBusName = arBusName;
      mAddress = aAddress;

      mpI2CDevice->openDevice(arBusName, aAddress);
   }


   void PCA9685::close()
   {
      mBusName = "";
      mAddress = 0x00;

      mpI2CDevice->closeBus();
   }


   void PCA9685::reset()
   {
      // write basic settings
      this->writeRegister(PCA9685_REG_MODE1, PCA9685_MODE1_ALLCALL);
      this->writeRegister(PCA9685_REG_MODE2, PCA9685_MODE2_OUTDRV);

      // wait for oscillator (at least 500us)
      usleep(2000);
   }


   int PCA9685::readRegister(int aRegister)
   {
      return mpI2CDevice->readByte(aRegister);
   }


   int PCA9685::writeRegister(int aRegister, int aValue)
   {
      return mpI2CDevice->writeByte(aRegister, aValue);
   }


   void PCA9685::setPWMFrequency(float aFrequency)
   {
      // limit argument to allowed range
      float lFreq = fmin(fmax(aFrequency, 24), 1526);

      // calculate prescale for 25 MHz internal oscillator
      int lPrescale = (int)round((25000000.0f / (4096 * lFreq)) - 1.0f);

      // prepare device to change prescale (only writeable wenn SLEEP = 1)
      int lMode1 = this->readRegister(PCA9685_REG_MODE1);
      int lMode1Res = (lMode1 & 0x7F) | PCA9685_MODE1_SLEEP;
      this->writeRegister(PCA9685_REG_MODE1, lMode1Res);

      // set new freqeuncy prescale
      this->writeRegister(PCA9685_REG_PRE_SCALE, lPrescale);

      // reset MODE1 and wait for oscillator (at least 500us)
      this->writeRegister(PCA9685_REG_MODE1, lMode1);
      usleep(2000);

      // restart PWM
      this->writeRegister(PCA9685_REG_MODE1, lMode1 | PCA9685_MODE1_RESTART);
   }


   void PCA9685::setPWM(int aChannel, int aOnValue, int aOffValue)
   {
      // check if valid channel
      if(aChannel > 15 || aChannel < 0)
      {
         throw std::range_error("Invalid channel \"" + std::to_string(aChannel) +
                                "\" (has to be between 0 and 15)");
      }


      // limit arguments to allowed range
      int lOnValue = fmin(fmax(aOnValue, 0), 4095);
      int lOffValue = fmin(fmax(aOffValue, 0), 4095);

      // write register values
      this->writeRegister(PCA9685_REG_LED0_ON_L + 4 * aChannel, lOnValue & 0xFF);
      this->writeRegister(PCA9685_REG_LED0_ON_H + 4 * aChannel, lOnValue >> 8);
      this->writeRegister(PCA9685_REG_LED0_OFF_L + 4 * aChannel, lOffValue & 0xFF);
      this->writeRegister(PCA9685_REG_LED0_OFF_H + 4 * aChannel, lOffValue >> 8);
   }


   void PCA9685::setAllPWM(int aOnValue, int aOffValue)
   {
      // limit arguments to allowed range
      int lOnValue = fmin(fmax(aOnValue, 0), 4095);
      int lOffValue = fmin(fmax(aOffValue, 0), 4095);

      // write register values
      this->writeRegister(PCA9685_REG_ALL_LED_ON_L, lOnValue & 0xFF);
      this->writeRegister(PCA9685_REG_ALL_LED_ON_H, lOnValue >> 8);
      this->writeRegister(PCA9685_REG_ALL_LED_OFF_L, lOffValue & 0xFF);
      this->writeRegister(PCA9685_REG_ALL_LED_OFF_H, lOffValue >> 8);
   }


   int checkBit(int aValue, int aBitMask)
   {
      return aValue & aBitMask;
   }
} // namespace CAR4TEGRA





