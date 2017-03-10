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

  OxI2CBus i2c_dummy( "/dev/i2c-2" );
  OxI2CBus i2c( "/dev/i2c-1" );

  ARDUINO_DISP d;
  
  OxApp::manual_int_vals->set_val( DISP_PAGE_NO,0 ) ;
  
  
  i2c.add_device( &d );        
  
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  d.rw_device();
  
  return 0;

}
