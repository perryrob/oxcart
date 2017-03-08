/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "devices/LIS3MDL.h"
#include "devices/TCA9548A.h"
#include "devices/BMP085.h"
#include "devices/LSM6.h"
#include "devices/GPS.h"

#include "oxapp.h"
#include "oxi2cbus.h"
#include "oxGPSDbus.h"

#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {
  
  OxApp::create();

  OxI2CBus i2c( "/dev/i2c-2" );
  OxGPSDbus gps_bus;

  TCA9548A tca9548_1( TCA9548A_CH1 );
  TCA9548A tca9548_2( TCA9548A_CH2 );
  TCA9548A tca9548_3( TCA9548A_CH3 );
  
  BMP085 p1;
  BMP085 p2;
  BMP085 p3;
  
  p1.set_multiplexer( &tca9548_1 );
  p2.set_multiplexer( &tca9548_2 );
  p3.set_multiplexer( &tca9548_3 );
  
  i2c.add_device(&p1);
  i2c.add_device(&p2);
  i2c.add_device(&p3);

  LIS3MDL l;
  LSM6 s;
  GPS gps;
  
  i2c.add_device(&s);
  i2c.add_device(&l);
  gps_bus.add_device( &gps );

  i2c.run();
  gps_bus.run();
  b::this_thread::sleep(b::posix_time::milliseconds(5000));
  i2c.stop();
  gps_bus.stop();

  OxApp::destroy();
  return 0;
}
