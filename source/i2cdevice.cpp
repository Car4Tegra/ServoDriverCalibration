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
 * @file i2cdevice.cpp
 * @date 02.04.2017
 *
 * @brief This file contains the definition of class I2cDevice at namespace CAR4TEGRA
 *
 * @version 0.1 - 07.04.2017 - File created
 */


// std includes
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <exception>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>

// Car4Tegra includes
#include "include/i2cdevice.hpp"


namespace CAR4TEGRA
{
   I2cDevice::I2cDevice()
      : mI2CBus(-1), mDevAddress(0x00)
   {
      // nothing to do
   }


   I2cDevice::~I2cDevice()
   {
      this->closeBus();
   }


   void I2cDevice::openBus(const std::string& acrBusName)
   {
      mI2CBusName = acrBusName;

      // try to open bus
      if((mI2CBus = open(mI2CBusName.c_str(), O_RDWR)) < 0)
      {
         throw std::runtime_error("Failed to open I2C bus \"" + mI2CBusName +
                                  "\" (Error " + std::to_string(errno) +
                                  ": " + strerror(errno) + ")");
      }
   }


   void I2cDevice::openDevice(int aAddress)
   {
      mDevAddress = aAddress;

      // check if bus is open
      if(mI2CBus < 0)
      {
         throw std::runtime_error("Failed to open I2C device: I2C bus is not open");
      }

      // try to open (address has to be shifted by 1 to remove r/w bit
      if(ioctl(mI2CBus, I2C_SLAVE, mDevAddress / 2) < 0)
      {
         throw std::runtime_error("Failed to open I2C device \"" + std::to_string(mDevAddress) +
                                  "\" (Error " + std::to_string(errno) +
                                  ": " + strerror(errno) + ")");
      }
   }


   void I2cDevice::openDevice(const std::string& acrBusName, int aAddress)
   {
      this->openBus(acrBusName);
      this->openDevice(aAddress);
   }


   void I2cDevice::closeBus()
   {
      if(mI2CBus > 0)
      {
         if(close(mI2CBus) < 0)
         {
            throw std::runtime_error("Failed to close I2C bus \"" + mI2CBusName +
                                     "\" (Error " + std::to_string(errno) +
                                     ": " + strerror(errno) + ")");
         }
      }

      mDevAddress = 0x00;
      mI2CBus = -1;
   }


   int I2cDevice::readByte(int aRegister)
   {
      // check if bus is open
      if(mI2CBus < 0)
      {
         throw std::runtime_error("Failed to read from I2C device: I2C bus is not open");
      }

      // check if device is open
      if(mDevAddress == 0x00)
      {
         throw std::runtime_error("Failed to read from I2C device: I2C device is not open");
      }


      // try to read
      int lRes = i2c_smbus_read_byte_data(mI2CBus, aRegister);

      // check if reading was succesfully
      if(lRes < 0)
      {
         throw std::runtime_error("Failed to read register \"" + std::to_string(aRegister) +
                                  "\" from I2C device \"" + std::to_string(mDevAddress) +
                                  "\" (Error " + std::to_string(errno) +
                                  ": " + strerror(errno) + ")");
      }

      return lRes;
   }


   int I2cDevice::writeByte(int aRegister, int aValue)
   {
      // check if bus is open
      if(mI2CBus < 0)
      {
         throw std::runtime_error("Failed to read from I2C device: I2C bus is not open");
      }

      // check if device is open
      if(mDevAddress == 0x00)
      {
         throw std::runtime_error("Failed to read from I2C device: I2C device is not open");
      }


      // try to write
      int lRes = i2c_smbus_write_byte_data(mI2CBus, aRegister, aValue);

      // check if writing was succesfully
      if(lRes < 0)
      {
         throw std::runtime_error("Failed to write register \"" + std::to_string(aRegister) +
                                  "\" from I2C device \"" + std::to_string(mDevAddress) +
                                  "\" with value \"" + std::to_string(aValue) +
                                  "\" (Error " + std::to_string(errno) +
                                  ": " + strerror(errno) + ")");
      }

      return lRes;
   }
} // namespace CAR4TEGRA
