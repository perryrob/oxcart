/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "oxapp.h"
#include "oxbluebus.h"
#include "oxBlueDevice.h"
#include "devices/KEYBOARD.h"
#include "named_store.h"

#include "trivial_log.h"

using namespace std;


int main(int argc, char *argv[] ) {
  
  init_log();

  KEYBOARD k("/dev/input/event1");

  OxApp::manual_int_vals->set_val( SYS_CMD,0 ); 
  
  int MAX_COUNT=100;
  int count = 0;
  
  k.run();
  while( OxApp::manual_int_vals->get_val( SYS_CMD ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << OxApp::KEYBOARD_BUFFER->get_str();
    b::this_thread::sleep(b::posix_time::milliseconds(100));
    ++count;
    if (count == MAX_COUNT )
      OxApp::manual_int_vals->set_val( SYS_CMD,1 ); 
  }
  BOOST_LOG_TRIVIAL(debug) << "stopping...";
  k.stop();
  OxApp::manual_int_vals->set_val( SYS_CMD,0 ); 
  return 0;
}
