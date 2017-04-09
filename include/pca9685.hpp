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
 * @date 05.04.2017
 *
 * @brief This file contains the declaration of class PCA9685 at namespace CAR4TEGRA
 *
 * @details
 * The PCA9685 class represents an PCA9685 PWM driver device. It offers functions to connect
 * to the device over I2C and to write and read data from/to it.
 *
 * @version 0.1 - 09.04.2017 - File created
 */


#ifndef PCA9685_H
#define PCA9685_H


// std includes
#include <memory>
#include <string>

// Car4Tegra includes
#include "include/pca9685defines.hpp"
#include "include/i2cdevice.hpp"


namespace CAR4TEGRA
{
   /**
    * @class PCA9685 pca9685.hpp "include/pca9685.hpp"
    * @brief The PCA9685 class represents an PCA9685 PWM driver device
    *
    * The PCA9685 class represents an PCA9685 PWM driver device. It offers functions to connect
    * to the device over I2C and to write and read data from/to it.
    */
   class PCA9685
   {
   public:
      /**
       * @brief Standard constructor with no input
       */
      PCA9685();


      /**
       * @brief Destructor
       */
      ~PCA9685();


      /** @{ @name Control functions */

      /**
       * @brief Opens a specified PCA9685 device
       *
       * @param[in]  acrBusName     Name of the I2C bus (format: "/dev/i2c-0")
       * @param[in]  aAddress       Adress of the PCA9685 device
       *
       * @return `TRUE` if bus has been opened successfully, `FALSE` otherwise
       */
      bool openDevice(const std::string acrBusName, int aAddress);


      /**
       * @brief Closes the current opened PCA9685 device
       *
       * @return `TRUE` if device has been closed (or was already closed) successfully, `FALSE` otherwise
       */
      bool close();


      /**
       * @brief Resets the current opened PCA9685 device
       *
       * @return `TRUE` if device has been reseted successfully, `FALSE` otherwise
       */
      bool reset();

      /** @} */


      /** @{ @name Data functions */

      /**
       * @brief Reads a register byte from the currently opened PCA9685 device
       *
       * @param[in]  aRegister      Register to read from
       *
       * @return Returns the register value or `-1` if something went wrong
       */
      int readRegister(int aRegister);

      /**
       * @brief Writes a register byte to the currently opened PCA9685 device
       *
       * @param[in]  aRegister      Register to write to
       * @param[in]  aValue         Value to write to the register
       *
       * @return Returns the writing result or `-1` if something went wrong
       */
      int writeRegister(int aRegister, int aValue);


      /**
       * @brief Writes the PWM settings for a single channel
       *
       * @param[in]  aFrequency     Freqeuncy for PWM reference oscillator (24 - 1526 Hz)
       */
      void setPWMFrequency(float aFrequency);


      /**
       * @brief Writes the PWM settings for a single channel
       *
       * @param[in]  aChannel       Channel number (0 - 15)
       * @param[in]  aOnValue       Value for PWM ON (0 - 4095)
       * @param[in]  aOffValue      Value for PWM OFF (0 - 4095)
       */
      void setPWM(int aChannel, int aOnValue, int aOffValue);


      /**
       * @brief Writes the PWM settings for all channels
       *
       * @param[in]  aOnValue       Value for PWM ON (0 - 4095)
       * @param[in]  aOffValue      Value for PWM OFF (0 - 4095)
       */
      void setAllPWM(int aOnValue, int aOffValue);

      /** @} */


   private:

      /**
       * @brief Checks a given bit
       *
       * @param[in]  aValue      Value to check
       * @param[in]  aBitMask    Bit mask to check
       *
       * @return Returns the value of the bit (0 or 1)
       */
      int checkBit(int aValue, int aBitMask);


   private:

      std::unique_ptr<CAR4TEGRA::I2cDevice> mpI2CDevice; ///< Instance of the used I2C device
      int mAddress;                 ///< Address of the PCA9685 device
      std::string mBusName;         ///< Name of the I2C bus the PCA9685 device is connected to
   }; // class PCA9685
} // namespace CAR4TEGRA

#endif // PCA9685_H
