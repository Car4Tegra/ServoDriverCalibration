# PCA9685 Servo Driver Calibration Tool

## Purpose
This tool allows to find the PWM range for a servo and / or ESC (electronic speed control) connected to a [NXP PCA9685](http://cache.nxp.com/documents/data_sheet/PCA9685.pdf?pspll=1) 16 channel PWM I2C controller.

## Supported Platforms
The code was tested on the following platforms:
 - **Nvidia Jetson TX1** running *Ubuntu 16.04.02 LTS*

## Hardware Setup
How to connect the PCA9685 to the I2C bus is shown in the [Car4Tegra Wiki](https://wiki.car4tegra.de/index.php?title=Servo_Driver).

## Software Setup
The program requires the `libi2c-dev`, `i2c-tools` and `qt5-default` (or `qtcreator` instead) packages:

```Shell
sudo apt-get install libi2c-dev i2c-tools
sudo apt-get install qt5-default
```

The project could be build without Qt Creator from terminal:

```Shell
git clone https://github.com/Car4Tegra/ServoDriverCalibration.git
mkdir ./ServoDriverCalibration/build
cd ./ServoDriverCalibration/build/
qmake ./../ServoDriverCalibration.pro
make
```

Important is to add the user to the `i2c` group (e.g. user `ubuntu`):

```Shell
sudo adduser ubuntu i2c
```

Start the tool with:

```Shell
./ServoDriverCalibration &
```

## License
The program and all of its files are under **MIT license** (see [LICENSE.md](LICENSE.md) for details)!
