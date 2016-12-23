OXCART
======
Open-XC-Airborne-Realtime-Telemetry

oxcart - main

oxmem - reads and writes to shaxsred mem

oxdev - base virtual device class Threaded

oxdev_i2c - inherits from oxdev opens Wire singleton if needed.

oxdev_i2c_switch - inherits from oxdev opens Wire singleton if needed
                   adds oxdev_i2c devices attached to switch.

oxdev_serial - inherits from oxdev ( GPS reader with write methods )

ox_display - inherits from oxdev_i2c, encapsulates oxdev_i2c_switch
             switched device

BMP85 - inherits from oxdev_i2c, encapsulates oxdev_i2c_switch
        switched device

LSM6DS33 - inherits from oxdev_i2c, encapsulates oxdev_i2c_switch
           switched device

GPS - Read this from GPSD SHM


oxtran - encapsulates oxdev_serial, sends data to XCSoar 

Boost SH MEM
============
http://stackoverflow.com/questions/33513051/structures-and-vectors-in-boost-shared-memory
http://coliru.stacked-crooked.com/a/0ab21481b69d87bb

BUILD
=====
Meson http://mesonbuild.com/documentation.html
sudo apt-get install python3 ninja-build

git clone git://github.com/mesonbuild/meson
sudo python3 setup.py install
sudo chown root.perryr /usr/local/bin/meson
sudo chown -R root.perryr /usr/local/lib/python3.5/dist-packages/mesonbuild

Gotta git ninja
===============
git clone git://github.com/ninja-build/ninja.git && cd ninja
./configure.py --bootstrap
sudo cp ninja /usr/bin/

mkdir build
meson build
cd build
ninja