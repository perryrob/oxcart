
#include "devices/LIS3MDL.h"
#include "devices/TCA9548A.h"
#include "devices/BMP085.h"
#include "devices/LSM6.h"
#include "devices/GPS.h"
#include "devices/ARDUINO_DISP.h"

#include "oxapp.h"
#include "oxi2cbus.h"
#include "oxGPSDbus.h"

#include <signal.h>
#include <cstdlib>

#include "trivial_log.h"

#include <iostream>

static bool KEEP_GOING = true;

void control_c(int s) {
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){
  
  init_production_log();
 
  OxApp::create();

  /************************************************************
   * Get the device buses up and running.
  */
  OxI2CBus i2c( "/dev/i2c-2" );
  OxGPSDbus gps_bus;
  /************************************************************
   * Set up the multiplexers for the BMP085s which run through 
   * then TCA9548A
   */
  TCA9548A tca9548_1( TCA9548A_CH1 );
  TCA9548A tca9548_2( TCA9548A_CH2 );
  TCA9548A tca9548_3( TCA9548A_CH3 );
  TCA9548A tca9548_4( TCA9548A_CH4 );
  
  /************************************************************
   * Create the Arduino SHARP MEM disply
   */
  ARDUINO_DISP aurduino_disp;
  aurduino_disp.set_multiplexer( &tca9548_4 );
  /************************************************************
   * Create the Pressure device objects. Not that p1 is pitot,
   * p2 is static and p3 is total energy.
   */  
  BMP085 p1;
  BMP085 p2;
  BMP085 p3;
  /************************************************************
   * Add the channels in the multiplexer to the devices
  */
  p1.set_multiplexer( &tca9548_1 );
  p2.set_multiplexer( &tca9548_2 );
  p3.set_multiplexer( &tca9548_3 );
 
  /************************************************************
   * Create the IMU devices. The magnetometer and the IMU
   */
  LIS3MDL l;
  LSM6 s;
  /************************************************************
   * Add the devices  to the I2C bus
   */  
  i2c.add_device(&s);
  i2c.add_device(&p1);  // te
  i2c.add_device(&s);   
  i2c.add_device(&p2); // static / alt
  i2c.add_device(&s);
  i2c.add_device(&p3); // pitot
  i2c.add_device(&s);
  i2c.add_device(&l);
  i2c.add_device(&s);
  i2c.add_device( &aurduino_disp );
  /************************************************************
   * Create the GPS object and add it to the gps serial bus
  */
  GPS gps;
  gps_bus.add_device( &gps );
  /************************************************************
   * Start the device threads
   */
  i2c.run();
  gps_bus.run();
  
  
  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  while( KEEP_GOING ) {
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  }

  i2c.stop();
  gps_bus.stop();
  OxApp::destroy();

}
