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
 * @file mainwindow.cpp
 * @date 02.04.2017
 *
 * @brief This file contains the definition of class MainWindow
 *
 * @version 0.1 - 12.04.2017 - File created
 */


// std includes
#include <exception>
#include <stdexcept>


// internal includes
#include "include/mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* apParent)
    : QMainWindow(apParent),
      mpUi(new Ui::MainWindow),
      mpDriver(std::make_unique<CAR4TEGRA::PCA9685>())
{
    mpUi->setupUi(this);
    this->init();
}


MainWindow::~MainWindow()
{
    delete mpUi;
}


void MainWindow::init()
{
   // save default loction of border selection elements (for inverting)
   mPosSteerTop = mpUi->sBSteerTop->pos();
   mPosSteerBot = mpUi->sBSteerBot->pos();
   mPosSpeedTop = mpUi->sBSpeedTop->pos();
   mPosSpeedBot = mpUi->sBSpeedBot->pos();

   // init GUI elements with default values

   this->enableI2CSettings(true);

   mpUi->leAddressHex->setText(QLatin1String(I2C_DEVICE_DEFAULT));
   mpUi->leAddressBin->setText(this->hexToBin(QLatin1String(I2C_DEVICE_DEFAULT)));

   for(size_t i = I2C_BUS_FIRST; i <= I2C_BUS_LAST; i++)
   {
      mpUi->cbBusSelect->addItem(QString("/dev/i2c-" + QString::number(i)));
   }
   mpUi->cbBusSelect->setCurrentIndex(I2C_BUS_DEFAULT);

   mpUi->cbInvSpeed->setChecked(PWM_SPEED_INV_DEFAULT);
   mpUi->cbInvSteer->setChecked(PWM_STEER_INV_DEFAULT);

   mpUi->sBSpeedBot->setRange(PWM_MIN, PWM_SPEED_MAX_DEFAULT - 1);
   mpUi->sBSpeedBot->setValue(PWM_SPEED_MIN_DEFAULT);
   mpUi->sBSpeedTop->setRange(PWM_SPEED_MIN_DEFAULT + 1, PWM_MAX);
   mpUi->sBSpeedTop->setValue(PWM_SPEED_MAX_DEFAULT);
   if(PWM_SPEED_INV_DEFAULT)
   {
      mpUi->sBSpeedBot->move(mPosSpeedTop);
      mpUi->sBSpeedTop->move(mPosSpeedBot);
   }

   mpUi->slidSpeed->setRange(PWM_SPEED_MIN_DEFAULT, PWM_SPEED_MAX_DEFAULT);
   mpUi->slidSpeed->setValue((PWM_SPEED_MAX_DEFAULT - PWM_SPEED_MIN_DEFAULT) / 2 + PWM_SPEED_MIN_DEFAULT);
   mpUi->slidSpeed->setInvertedAppearance(PWM_SPEED_INV_DEFAULT);
   mpUi->lSpeedVal->setText(QString::number(mpUi->slidSpeed->value()));   

   mpUi->sBSteerBot->setRange(PWM_MIN, PWM_STEER_MAX_DEFAULT - 1);
   mpUi->sBSteerBot->setValue(PWM_STEER_MIN_DEFAULT);
   mpUi->sBSteerTop->setRange(PWM_STEER_MIN_DEFAULT + 1, PWM_MAX);
   mpUi->sBSteerTop->setValue(PWM_STEER_MAX_DEFAULT);
   if(PWM_STEER_INV_DEFAULT)
   {
      mpUi->sBSteerBot->move(mPosSteerTop);
      mpUi->sBSteerTop->move(mPosSteerBot);
   }

   mpUi->slidSteer->setMinimum(PWM_STEER_MIN_DEFAULT);
   mpUi->slidSteer->setMaximum(PWM_STEER_MAX_DEFAULT);
   mpUi->slidSteer->setValue((PWM_STEER_MAX_DEFAULT - PWM_STEER_MIN_DEFAULT) / 2 + PWM_STEER_MIN_DEFAULT);
   mpUi->slidSteer->setInvertedAppearance(PWM_STEER_INV_DEFAULT);
   mpUi->lSteerVal->setText(QString::number(mpUi->slidSteer->value()));

   mpUi->lDir1->setVisible(false);
   mpUi->lDir2->setVisible(false);

   mpUi->sbChannelSpeed->setValue(I2C_SPEED_CHANNEL_DEFAULT);
   mpUi->sbChannelSteer->setValue(I2C_STEER_CHANNEL_DEFAULT);

   mpUi->sBFreq->setMinimum(PWM_FREQ_MIN);
   mpUi->sBFreq->setMaximum(PWM_FREQ_MAX);
   mpUi->sBFreq->setValue(PWM_FREQ_DEFAULT);
}


QString MainWindow::hexToBin(QString aHexValue)
{
   // first: convert to decimal int
   bool lCheck;
   int lVal = aHexValue.toInt(&lCheck, 16);
   if(!lCheck)
      return "00000000";

   // second: print as binary
   return QString("%1").arg(lVal, 8, 2, QChar('0'));
}


QString MainWindow::binToHex(QString aBinValue)
{
   // first: convert to decimal int
   bool lCheck;
   int lVal = aBinValue.toInt(&lCheck, 2);
   if(!lCheck)
      return "00";

   // second: print as hex
   return QString("%1").arg(lVal, 2, 16, QChar('0'));
}


void MainWindow::enableI2CSettings(bool aEnable)
{
   mpUi->btConnect->setEnabled(aEnable);
   mpUi->btDisconnect->setEnabled(!aEnable);
   mpUi->cbBusSelect->setEnabled(aEnable);
   mpUi->leAddressBin->setEnabled(aEnable);
   mpUi->leAddressHex->setEnabled(aEnable);
}


void MainWindow::updateSpeedVisualization(int aValue)
{
   // get invertation status
   bool lInv = mpUi->cbInvSpeed->isChecked();

   // check if direction is forward or backward
   int lMid = (mpUi->sBSpeedTop->value() - mpUi->sBSpeedBot->value()) / 2 + mpUi->sBSpeedBot->value();
   bool lStop = (aValue == lMid);
   bool lForward = ((aValue > lMid) && !lInv) ||
                   ((aValue < lMid) && lInv);

   // updated GUI elements for speed visualization
   mpUi->lDir1->setPixmap(lForward ? QPixmap(":/car/images/Arrow_Right.png") : QPixmap(":/car/images/Arrow_Left.png"));
   mpUi->lDir2->setPixmap(lForward ? QPixmap(":/car/images/Arrow_Right.png") : QPixmap(":/car/images/Arrow_Left.png"));

   // show speed visualization GUI elements only if not stopped
   mpUi->lDir1->setVisible(!lStop);
   mpUi->lDir2->setVisible(!lStop);
}


void MainWindow::updateSteerVisualization(int aValue)
{
   // get invertation status
   bool lInv = mpUi->cbInvSteer->isChecked();

   // check if direction is left or right
   int lMid = (mpUi->sBSteerTop->value() - mpUi->sBSteerBot->value()) / 2 + mpUi->sBSteerBot->value();
   bool lNeutral = (aValue == lMid);
   bool lLeft = ((aValue > lMid) && !lInv) ||
                   ((aValue < lMid) && lInv);

   // updated GUI elements for steering visualization
   if(lNeutral)
      mpUi->lImage->setPixmap(QPixmap(":/car/images/Car.png"));
   else
      mpUi->lImage->setPixmap(lLeft ? QPixmap(":/car/images/Car_Left.png") : QPixmap(":/car/images/Car_Right.png"));
}


void MainWindow::setPWMValue(int aChannel, int aValue)
{
   try
   {
      // write new value to device
      mpDriver->setPWM(aChannel, 0, aValue);
   }
   catch(const std::runtime_error e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
   catch(const std::exception e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
}


void MainWindow::on_btConnect_clicked()
{
   try
   {
      // try to open bus and device
      bool lCheck;
      mpDriver->openDevice(mpUi->cbBusSelect->currentText().toStdString(),
                           mpUi->leAddressHex->text().toInt(&lCheck, 16));

      // disable bus / device settings
      this->enableI2CSettings(false);

      mpUi->tbLog->append("Connected to 0x" + mpUi->leAddressHex->text() +
                          " on bus " + mpUi->cbBusSelect->currentText());

      // set device to default values and disable PWM outputs (value: 0 / 0)
      mpDriver->reset();
      mpDriver->setPWMFrequency((float)mpUi->sBFreq->value());
      mpDriver->setAllPWM(0, 0);
   }
   catch(const std::runtime_error e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
   catch(const std::exception e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
}


void MainWindow::on_btDisconnect_clicked()
{
   try
   {
      // disable PWM outputs (value: 0 / 0)
      mpDriver->setAllPWM(0, 0);
   }
   catch(const std::runtime_error e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
   catch(const std::exception e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }

   try
   {
      mpDriver->close();

      // enable bus / device settings
      this->enableI2CSettings(true);

      mpUi->tbLog->append("Disconnected");
   }
   catch(const std::runtime_error e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
   catch(const std::exception e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }

}


void MainWindow::on_leAddressHex_textEdited(const QString& acrArg1)
{
   // updated binary address
   mpUi->leAddressBin->setText(this->hexToBin(acrArg1));
}


void MainWindow::on_leAddressBin_textEdited(const QString& acrArg1)
{
   // updated hex address
   mpUi->leAddressHex->setText(this->binToHex(acrArg1));
}


void MainWindow::on_sBSpeedBot_editingFinished()
{
   mpUi->sBSpeedTop->setMinimum(mpUi->sBSpeedBot->value() + 1);
   if(mpUi->slidSpeed->value() < mpUi->sBSpeedBot->value())
   {
      mpUi->slidSpeed->setValue(mpUi->sBSpeedBot->value());
      mpUi->lSpeedVal->setText(QString::number(mpUi->slidSpeed->value()));
      this->setPWMValue(mpUi->sbChannelSpeed->value(), mpUi->slidSpeed->value());
   }
   mpUi->slidSpeed->setMinimum(mpUi->sBSpeedBot->value());
   this->updateSpeedVisualization(mpUi->slidSpeed->value());
}


void MainWindow::on_sBSpeedTop_editingFinished()
{
   mpUi->sBSpeedBot->setMaximum(mpUi->sBSpeedTop->value() - 1);
   if(mpUi->slidSpeed->value() > mpUi->sBSpeedTop->value())
   {
      mpUi->slidSpeed->setValue(mpUi->sBSpeedTop->value());
      mpUi->lSpeedVal->setText(QString::number(mpUi->slidSpeed->value()));
      this->setPWMValue(mpUi->sbChannelSpeed->value(), mpUi->slidSpeed->value());
   }
   mpUi->slidSpeed->setMaximum(mpUi->sBSpeedTop->value());
   this->updateSpeedVisualization(mpUi->sBSpeedTop->value());
}


void MainWindow::on_sBSteerBot_editingFinished()
{
   mpUi->sBSteerTop->setMinimum(mpUi->sBSteerBot->value() + 1);
   if(mpUi->slidSteer->value() < mpUi->sBSteerBot->value())
   {
      mpUi->slidSteer->setValue(mpUi->sBSteerBot->value());
      mpUi->lSteerVal->setText(QString::number(mpUi->slidSteer->value()));
      this->setPWMValue(mpUi->sbChannelSteer->value(), mpUi->slidSteer->value());
   }
   mpUi->slidSteer->setMinimum(mpUi->sBSteerBot->value());
   this->updateSteerVisualization(mpUi->slidSteer->value());
}


void MainWindow::on_sBSteerTop_editingFinished()
{
   mpUi->sBSteerBot->setMaximum(mpUi->sBSteerTop->value() - 1);
   if(mpUi->slidSteer->value() > mpUi->sBSteerTop->value())
   {
      mpUi->slidSteer->setValue(mpUi->sBSteerTop->value());
      mpUi->lSteerVal->setText(QString::number(mpUi->slidSteer->value()));
      this->setPWMValue(mpUi->sbChannelSteer->value(), mpUi->slidSteer->value());
   }
   mpUi->slidSteer->setMaximum(mpUi->sBSteerTop->value());
   this->updateSteerVisualization(mpUi->slidSteer->value());
}


void MainWindow::on_slidSpeed_sliderMoved(int aPosition)
{
   this->updateSpeedVisualization(aPosition);
   this->setPWMValue(mpUi->sbChannelSpeed->value(), aPosition);
}


void MainWindow::on_slidSteer_sliderMoved(int aPosition)
{
   this->updateSteerVisualization(aPosition);
   this->setPWMValue(mpUi->sbChannelSteer->value(), aPosition);
}


void MainWindow::on_cbInvSteer_clicked(bool aChecked)
{
   mpUi->slidSteer->setInvertedAppearance(aChecked);
   mpUi->sBSteerBot->move(aChecked ? mPosSteerTop : mPosSteerBot);
   mpUi->sBSteerTop->move(aChecked ? mPosSteerBot : mPosSteerTop);

   this->updateSteerVisualization(mpUi->slidSteer->value());
}


void MainWindow::on_cbInvSpeed_clicked(bool aChecked)
{
   mpUi->slidSpeed->setInvertedAppearance(aChecked);
   mpUi->sBSpeedBot->move(aChecked ? mPosSpeedTop : mPosSpeedBot);
   mpUi->sBSpeedTop->move(aChecked ? mPosSpeedBot : mPosSpeedTop);

   this->updateSpeedVisualization(mpUi->sBSpeedTop->value());
}


void MainWindow::on_sBFreq_editingFinished()
{
   try
   {
      // set new PWM frequency
      mpDriver->setPWMFrequency((float)mpUi->sBFreq->value());

      mpUi->tbLog->append("PWM frequency changed to " + QString("%1").arg(mpUi->sBFreq->value(), 0, 'f', 3) + " Hz");
   }
   catch(const std::runtime_error e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
   catch(const std::exception e)
   {
      mpUi->tbLog->append(QLatin1String(e.what()));
   }
}
