#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T18:22:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServoDriverCalibration
TEMPLATE = app


SOURCES += \
    source/main.cpp \
    source/mainwindow.cpp \
    source/pca9685.cpp \
    source/i2cdevice.cpp

HEADERS  += \
    include/mainwindow.hpp \
    include/pca9685.hpp \
    include/i2cdevice.hpp \
    include/pca9685defines.hpp

FORMS    += \
    resource/mainwindow.ui

CONFIG += c++14
