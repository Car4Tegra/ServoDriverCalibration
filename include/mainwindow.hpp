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
 * @file mainwindow.hpp
 * @date 02.04.2017
 *
 * @brief This file contains the declaration of class MainWindow
 *
 * @details
 * The MainWindow class handles the actions from the GUI
 *
 * @version 0.1 - 12.04.2017 - File created
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


// setting defines
#define I2C_BUS_FIRST               0        ///< ID of the first I2C bus
#define I2C_BUS_LAST                6        ///< ID of the last I2C bus
#define PWM_MIN                     0        ///< Minimum PWM value
#define PWM_MAX                     4095     ///< Maximum PWM value

#define I2C_BUS_DEFAULT             0        ///< Index of the I2C bus which is selected by default
#define I2C_DEVICE_DEFAULT          "80"     ///< Address of the PCA9685 device which is selected by default (hex)
#define I2C_SPEED_CHANNEL_DEFAULT   0        ///< Default PWM channel for ESC
#define I2C_STEER_CHANNEL_DEFAULT   1        ///< Default PWM channel for steering servo
#define PWM_SPEED_MIN_DEFAULT       160      ///< Default minimum PWM value for speed control
#define PWM_SPEED_MAX_DEFAULT       715      ///< Default maximum PWM value for speed control
#define PWM_STEER_MIN_DEFAULT       300      ///< Default minimum PWM value for steering control
#define PWM_STEER_MAX_DEFAULT       500      ///< Default maximum PWM value for steering control
#define PWM_SPEED_INV_DEFAULT       false    ///< Speed PWM values inverted by default or not
#define PWM_STEER_INV_DEFAULT       true     ///< Steer PWM values inverted by default or not


// QT includes
#include <QMainWindow>

// std includes
#include <string>
#include <memory>

// CAR4TEGRA includes
#include "include/pca9685.hpp"


namespace Ui {
   class MainWindow;
} // namespace UI


/**
 * @class MainWindow mainwindow.hpp "include/mainwindow.hpp"
 * @brief The MainWindow class handles the actions from the GUI
 */
class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   /**
    * @brief Constructor
    *
    * @param[in]  apParent    QT parent for window creation
    */
   explicit MainWindow(QWidget* apParent = 0);


   /**
    * @brief Destructor
    */
   ~MainWindow();

private:
   /**
    * @brief Init GUI elements with values
    */
   void init();


   /**
    * @brief Convert hexadecimal number to binary number (both in string)
    *
    * @param[in]  aHexValue   Hexadecimal value for conversion
    *
    * @return 8-Bit binary representation of the input hex value
    */
   QString hexToBin(QString aHexValue);


   /**
    * @brief Convert binary number to hexadecimal number (both in string)
    *
    * @param[in]  aBinValue   Binary value for conversion
    *
    * @return 8-Bit hexadecimal representation of the input binary value
    */
   QString binToHex(QString aBinValue);


private slots:
   /**
    * @brief Connect button clicked
    */
   void on_btConnect_clicked();


   /**
    * @brief Disconnect button clicked
    */
   void on_btDisconnect_clicked();


   /**
    * @brief Value of hexadecimal address changed by user
    *
    * @param[in]  acrArg1     New text value
    */
   void on_leAddressHex_textEdited(const QString& acrArg1);


   /**
    * @brief Value of binary address changed by user
    *
    * @param[in]  acrArg1     New text value
    */
   void on_leAddressBin_textEdited(const QString& acrArg1);


   /**
    * @brief Editing of lower speed border finished
    */
   void on_sBSpeedBot_editingFinished();


   /**
    * @brief Editing of upper speed border finished
    */
   void on_sBSpeedTop_editingFinished();


   /**
    * @brief Editing of lower steering border finished
    */
   void on_sBSteerBot_editingFinished();


   /**
    * @brief Editing of upper steering border finished
    */
   void on_sBSteerTop_editingFinished();


   /**
    * @brief Position of speed slider changed
    *
    * @param[in]  aPosition      New slider position
    */
   void on_slidSpeed_sliderMoved(int aPosition);


   /**
    * @brief Position of steering slider changed
    *
    * @param[in]  aPosition      New slider position
    */
   void on_slidSteer_sliderMoved(int aPosition);


   /**
    * @brief Invert the PWM values fo steering
    *
    * @param[in]  aChecked       Inverting used
    */
   void on_cbInvSteer_clicked(bool aChecked);


   /**
    * @brief Invert the PWM values fo speed control
    *
    * @param[in]  aChecked       Inverting used
    */
   void on_cbInvSpeed_clicked(bool aChecked);

private:
   Ui::MainWindow* mpUi;            ///< QT UI instance
   std::unique_ptr<CAR4TEGRA::PCA9685> mpDriver;   ///< PCA9685 device
}; // class MainWindow

#endif // MAINWINDOW_H
