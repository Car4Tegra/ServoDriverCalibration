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
 * @file main.hpp
 * @date 02.04.2017
 *
 * @brief This file contains the main function
 *
 * @details
 * The main function starts the application and loads the GUI main window
 *
 * @version 0.1 - 09.04.2017 - File created
 */


// QT includes
#include <QApplication>

// internal includes
#include "include/mainwindow.hpp"


/**
 * @brief Main funcition
 *
 * @param[in]  aArgc    Number of arguments
 * @param[in]  apArgv   Value of arguments
 *
 * @return `0` if application works fine, `non zero` otherwise
 */
int main(int aArgc, char* apArgv[])
{
    QApplication lApp(aArgc, apArgv);
    MainWindow lWindow;
    lWindow.show();

    return lApp.exec();
}
