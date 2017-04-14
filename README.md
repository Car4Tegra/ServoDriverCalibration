# PCA9685 Servo Driver Calibration Tool

## Purpose
This tool allows to find the PWM range for a servo and / or ESC (electronic speed control) connected to a [NXP PCA9685](http://cache.nxp.com/documents/data_sheet/PCA9685.pdf?pspll=1) 16 channel PWM I2C controller.

## Supported Platforms
The code was tested on the following platforms:
 - **Nvidia Jetson TX1** running *Ubuntu 16.04.02 LTS*

## Hardware Setup
How to connect the PCA9685 to the I2C bus is shown in the [Car4Tegra Wiki](https://wiki.car4tegra.de/index.php?title=Servo_Driver).

## Software Setup
The program requires the `libi2c-dev` and `i2c-tools` libraries:

```Shell
sudo apt-get install libi2c-dev i2c-tools
```

Important is to allow access from user space for the I2C bus files:

```Shell
sudo chmod 666 /dev/i2c-*
```

## License
The program and all of its files are under **MIT license** (see [LICENSE.md](LICENSE.md) for details)!
