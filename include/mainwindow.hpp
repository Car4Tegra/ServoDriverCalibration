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
 * @version 0.1 - 09.04.2017 - File created
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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


private slots:


private:
   Ui::MainWindow* mpUi;            ///< QT UI instance
   std::unique_ptr<CAR4TEGRA::PCA9685> mpDriver;   ///< PCA9685 device
}; // class MainWindow

#endif // MAINWINDOW_H
