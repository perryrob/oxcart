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

  TCA9548A tca9548( TCA9548A_CH2 );

  LIS3MDL l;
  BMP085 p;
  LSM6 s;
  GPS gps;
  
  p.set_multiplexer( &tca9548 );

  i2c.add_device(&p);
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
