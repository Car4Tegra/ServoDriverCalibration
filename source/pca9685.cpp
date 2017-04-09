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


   bool PCA9685::openDevice(const std::string arBusName, int aAddress)
   {
      mBusName = arBusName;
      mAddress = aAddress;

      return mpI2CDevice->openDevice(arBusName, aAddress);
   }


   bool PCA9685::close()
   {
      mBusName = "";
      mAddress = 0x00;

      return mpI2CDevice->closeBus();
   }


   bool PCA9685::reset()
   {
      return false;
   }


   int PCA9685::readRegister(int aRegister)
   {
      return mpI2CDevice->readByte(aRegister);
   }


   int PCA9685::writeRegister(int aRegister, int aValue)
   {
      return mpI2CDevice->writeByte(aRegister, aValue);
   }
} // namespace CAR4TEGRA





