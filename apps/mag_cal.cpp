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
#include "devices/ARDUINO_DISP.h"

#include "oxapp.h"
#include "oxi2cbus.h"
#include "oxGPSDbus.h"

#include <signal.h>
#include <cstdlib>

#include "trivial_log.h"

#include <iostream>
#include <fstream>

using namespace std;

static bool KEEP_GOING = true;

void control_c(int s) {
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){
  
  init_info_log();
 
  OxApp::create();
  /************************************************************
   * Create the Arduino SHARP MEM disply
   */
  OxI2CBus diaplsy_i2c( "/dev/i2c-1" );
  ARDUINO_DISP aurduino_disp;
  diaplsy_i2c.add_device( &aurduino_disp );
  diaplsy_i2c.run();
  
  OxApp::system_status->set_val( LED_1,1 );
  OxApp::system_status->set_val( LED_2,1 );
  OxApp::system_status->set_val( LED_3,1 );

  OxApp::KEYBOARD_BUFFER->set_str( "* starting *",14);
  if( OxApp::time_set() ){}
  OxApp::KEYBOARD_BUFFER->set_str( "** CAL **",14);

  OxApp::system_status->set_val( LED_2,0 );
  OxApp::system_status->set_val( LED_3,0 );
  /************************************************************
   * Get the device buses up and running.
  */
  OxI2CBus i2c( "/dev/i2c-2" );
 
  /************************************************************
   * Create the IMU devices. The magnetometer and the IMU
   */
  LIS3MDL l;
  i2c.add_device(&l);
  /************************************************************
   */
  diaplsy_i2c.add_device( &aurduino_disp );

  /************************************************************
   * Do not thread the buss since it will call rw_device which
   * adds corerctions.
   */
  //   i2c.run();
  
  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  l.init();

  ofstream myfile;
  myfile.open ("/mnt/sdcard/data/mag_cal.txt", ios::out );

  /************************************************************
   *
   * Initialize the min max
   */
  l.read(); //read x,y,z
  int16_t mag_max[3] = {l.m.x, l.m.y, l.m.z};
  int16_t mag_min[3] = {l.m.x, l.m.y, l.m.z};

  bool update = false;
  
  while( KEEP_GOING ) {

    l.read(); //read x,y,z
    
    if(l.m.x > mag_max[0]) {
      mag_max[0] = l.m.x;
      update = true;
    }
    if(l.m.x < mag_min[0]) {
      mag_min[0] = l.m.x;
      update = true;
    }
    if(l.m.y > mag_max[1]) {
      mag_max[1] = l.m.y;
      update = true;
    }
    if(l.m.y < mag_min[1]) {
      mag_min[1] = l.m.y;
      update = true;
    }
    if(l.m.z > mag_max[2]) {
      mag_max[2] = l.m.z;
      update = true;
    }
    if(l.m.z < mag_min[2]) {
      mag_min[2] = l.m.z;
      update = true;
    }

    myfile << l.m.x << " " << l.m.y << " " << l.m.z << endl;
      
    if ( update ) {
      BOOST_LOG_TRIVIAL(info) << mag_min[0] << " " << mag_max[0] << " " <<
        mag_min[1] << " " << mag_max[1] << " " << 
        mag_min[2] << " " << mag_max[2]  << " " <<
        (mag_max[0] + mag_min[0]) / 2 << " " <<
        (mag_max[1] + mag_min[1]) / 2 << " " <<
        (mag_max[2] + mag_min[2]) / 2 ;
      myfile << l.m.x << " " << l.m.y << " " << l.m.z << " " << 
        mag_min[0] << " " << mag_max[0] << " " <<
        mag_min[1] << " " << mag_max[1] << " " << 
        mag_min[2] << " " << mag_max[2]  << " " <<
        (mag_max[0] + mag_min[0]) / 2 << " " <<
        (mag_max[1] + mag_min[1]) / 2 << " " <<
        (mag_max[2] + mag_min[2]) / 2 << endl;        
        OxApp::system_status->set_val( LED_1,1 );        
        update = false;
    } else {
        OxApp::system_status->set_val( LED_1,0 );
      }
    b::this_thread::sleep(b::posix_time::milliseconds(50));
  }

  OxApp::KEYBOARD_BUFFER->set_str( "** DONE **",10);
  OxApp::system_status->set_val( LED_1,0 );
  OxApp::system_status->set_val( LED_2,0 );
  OxApp::system_status->set_val( LED_3,0 );
  myfile.close();

  b::this_thread::sleep(b::posix_time::milliseconds(500));
  
  diaplsy_i2c.stop();
}
