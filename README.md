BUILD
=====
meson build && cd build && ninja


OXCART
======
Open-XC-Airborne-Realtime-Telemetry

oxcart - main

* oxapp - contains the named shared memory manager

* oxmem - reads and writes to shaxsred mem

* oxbus - base virtual device class Threaded

ox_wire - implements an Arduino like i2c communication singleton class

oxdev_i2c - inherits from oxdev opens Wire (ox_wire) singleton if needed.

oxdev_i2c_switch - inherits from oxdev opens Wire singleton if needed
                   adds oxdev_i2c devices attached to switch.

oxdev_serial - inherits from oxdev ( GPS reader with write methods )

ox_display - inherits from oxdev_i2c, encapsulates oxdev_i2c_switch
             switched device

* named_store - shared mem base class to store 

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

Implementation notes
====================

i2c = ArduinoWire::OxI2CBus( const char * address )
i2c.add_device( OxDevice )
i2c.run()  // starts thread that loops though devices and calls read_sensor


TODO
====
Still need to add the named_store implementation to the OxDevice or device class itself.....
Still need to add the multiplexing device.