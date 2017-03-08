INTRODUCTION
============

Very rough still in-development source code. The plan is to clean everything up so the cross build setup and isntallation are repeatable. 3/8/2017 These instructions are not for the novice...yet!

The goal of this project is to provide a high performance computing platform that is installed in a sailplane. It has an IMU, 3 air data sensors, GPS, simple display and of course the Beaglebone Black single board computer. There are similar projects like the BlueFly vario and production products like the Vaulter Vario (http://s624368771.online.de/homepage/index.php/produkte/vaulter), The KOBO.cpp file outputs the Vaulter NMEA streams that seem to work great with an unmodified XCSoar 6.8 installation.

The bluetooth interface communicates to an XCSoar (https://www.xcsoar.org)  device, currently a KOBO eReader that is modified to communicate using SPP bluetooth.

***** USE AT YOUR OWN RISK ******

CONOPS
======

The software has 3 main components that run as separate user space programs. The oxcart_d program manages all of the sensors and writes their values into a shared memory space. All sensors are read using I2C (400kHz)  except the GPS. The program oxalgos reads the shared memory sensor values and then runs these through filters and linear regression algorithms. It's important to note that all sensor readings and algorithm calculations are timestamped in echoch milliseconds so rates are easily calculated. The final software component is oxclient. It can read the shared memory space and output values to a shell or with the -k argument connect to the bluetooth bus and send data to the KOB reader.

BUILDING
========

The system is currently being built on a linux Ubuntu 16.04 64 bit system using the ARM toolchain and cros compiler. I install the native arm libraries and includes in /usr/local/arm-linux-gnueabihf. The cross compiler is installed using the usual Ubuntu apt software manager. I also use the latest meson and ninja build tools. I compile and install those locally on the build host linux computer.

Boost (1.58) is cross compiled and installed on the host using the prefix /usr/local/arm-linux-gnueabihf. 


Setting Up the beaglebone
=========================

Main instructions to install latest ubuntu onto the beaglebone

http://elinux.org/BeagleBoardUbuntu#eMMC:_All_BeagleBone_Varients_with_eMMC

Download the image
------------------
wget https://rcn-ee.com/rootfs/2017-01-23/flasher/BBB-eMMC-flasher-ubuntu-16.04.1-console-armhf-2017-01-23-2gb.img.xz

Create the SD card following the instructions above
---------------------------------------------------
xzcat BBB-eMMC-flasher-ubuntu-16.04.1-console-armhf-2017-01-23-2gb.img.xz | sudo dd of=/dev/sdX


Additional Notes
----------------
Then install boost binaries for 1.58 sudo apt-get install libboost-all-dev

Install GPSD and chrony. Not that it may be wise to build the latest GPSD from source.


Hardware BOM
============

$68.00 (1) Beaglebone: https://www.digikey.com/products/en/development-boards-kits-programmers/33?k=beaglebone&newproducts=1

$4.95  (2) https://www.adafruit.com/products/706    
$19.90 (2) https://www.adafruit.com/products/572    
$6.95  (1) https://www.adafruit.com/products/2717
$29.85 (3) https://www.adafruit.com/products/2651 *
$13.95 (1) https://www.adafruit.com/products/2419
$39.95 (1) https://www.adafruit.com/products/1393
$12.95 (1) https://www.adafruit.com/products/960
$3.95  (1)  https://www.adafruit.com/products/851
$14.95 (1) https://www.pololu.com/product/2574
$15.95 (1) https://www.pololu.com/product/2738

* replacements for BMP85

Still need box and misc hardware wire and solder ~$20.00

~$250.00 as of 3/8/2017