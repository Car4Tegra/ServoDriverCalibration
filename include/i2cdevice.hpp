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
 * @file i2cdevice.hpp
 * @date 02.05.2017
 *
 * @brief This file contains the declaration of class I2cDevice at namespace CAR4TEGRA
 *
 * @details
 * The I2cDevice class represents an I2C slave device. It offers functions to connect
 * to the device and to write and read data from/to it.
 *
 * @version 0.1 - 07.04.2017 - File created
 */


#ifndef I2cDevice_H
#define I2cDevice_H


// std includes
#include <string>


namespace CAR4TEGRA
{
   /**
    * @class I2cDevice i2cdevice.hpp "include/i2cdevice.hpp"
    * @brief The I2cDevice class represents an I2C slave device
    *
    * The I2cDevice class represents an I2C slave device. It offers functions to connect
    * to the device and to write and read data from/to it.
    */
   class I2cDevice
   {
   public:
      /**
       * @brief Standard constructor with no input
       */
      I2cDevice();


      /**
       * @brief Destructor
       */
      ~I2cDevice();


      /** @{ @name Control functions */

      /**
       * @brief Opens a specified I2C bus
       *
       * @param[in]  arBusName      Name of the bus (format: "/dev/i2c-0")
       *
       * @return `TRUE` if bus has been opened successfully else `FALSE` otherwise
       */
      bool openBus(const std::string& arBusName);


      /**
       * @brief Opens a specified I2C device
       *
       * @param[in]  aAddress       Adress of the I2C device
       *
       * @return `TRUE` if device has been opened successfully else `FALSE` otherwise
       */
      bool openDevice(int aAddress);


      /**
       * @brief Opens a specified I2C device
       *
       * @param[in]  arBusName      Name of the bus (format: "/dev/i2c-0")
       * @param[in]  aAddress       Adress of the I2C device
       *
       * @return `TRUE` if device has been opened successfully else `FALSE` otherwise
       */
      bool openDevice(const std::string& arBusName, int aAddress);


      /**
       * @brief Closes the current opened I2C bus
       *
       * @return `TRUE` if bus has been closed (or was already closed) successfully else `FALSE` otherwise
       */
      bool closeBus();

      /** @} */


      /** @{ @name Data functions */

      /**
       * @brief Reads a register byte from the currently opened I2C device
       *
       * @param[in]  aRegister      Register to read from
       *
       * @return Returns the regeister value or `-1` if something went wrong
       */
      int readByte(int aRegister);


      /**
       * @brief Writes a register byte to the currently opened I2C device
       *
       * @param[in]  aRegister      Register to write to
       * @param[in]  aValue         Value to write to the register
       *
       * @return Returns the writing result or `-1` if something went wrong
       */
      int writeByte(int aRegister, int aValue);

      /** @} */


   private:
      std::string mI2CBusName;   ///< Name of the currently opened I2C bus
      int mI2CBus;               ///< File pointer to the currently opened I2C bus
      int mDevAddress;           ///< Address of the currently opened I2C device
   };
}

#endif // I2cDevice_H
