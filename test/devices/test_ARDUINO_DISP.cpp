/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <boost/chrono/system_clocks.hpp>
#include "devices/TCA9548A.h"
#include "devices/ARDUINO_DISP.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "oxapp.h"
#include <iostream>
#include <cassert>
#include "trivial_log.h"

using namespace std;

int main(int argc, char * argv [] ) {


  init_info_log();

  OxI2CBus i2c( "/dev/i2c-2" );
  TCA9548A tca9548_4( TCA9548A_CH4 );
  TCA9548A tca9548_0( TCA9548A_OFF );
  ARDUINO_DISP d;
  
  OxApp::manual_int_vals->set_val( DISP_PAGE_NO,0 ) ;
  
  
  d.set_multiplexer( &tca9548_4 );
  i2c.add_device( &d );        
  tca9548_4.rw_device();
  
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  
  d.set_multiplexer( &tca9548_0 );
  i2c.add_device( &d );
  tca9548_0.rw_device();
  
  return 0;

}
