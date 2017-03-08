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
#include "oxmem.h"
#include "oxbluebus.h"
#include "oxBlueDevice.h"
#include "named_store.h"

#include "trivial_log.h"

using namespace std;

class TestBlueDevice : public OxBlueDevice {

public:
  TestBlueDevice( const string &name ) : OxBlueDevice( name ) {}
  void rw_device() {
    string msg("This is a test.\n");
    bus->write(msg);
  }
  ~TestBlueDevice(){}
};


int main(int argc, char *argv[] ) {

  init_log();

  string remote_device = "00:06:66:73:E6:0D";

  
  OxBluebus bus( remote_device ,1 );
  TestBlueDevice test_device( "Test Device" );
  
  bus.add_device( &test_device );
  bus.run();

  b::this_thread::sleep(b::posix_time::milliseconds(100));

  bus.stop();

  cerr << endl << "complete" << endl;;
  
  return 0;
}
