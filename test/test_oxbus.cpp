#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "oxmem.h"
#include "oxi2cbus.h"
#include "oxi2cdevice.h"
#include "named_store.h"

using namespace std;

class TestMultiplexer : public OxI2CDevice {
public:
  TestMultiplexer( const string &name ) : OxI2CDevice( name ) {}
  void rw_sensor() {cerr << "MULTIPLEX";}
  ~TestMultiplexer(){}
};

class TestDevice : public OxI2CDevice {

public:

  TestDevice( const string &name ) : OxI2CDevice( name ) {
    running = true;
  }
                                                       
  void rw_sensor() {
    for( int i=0; i < 5; ++i ) {
      cerr << ".";
      b::this_thread::sleep(b::posix_time::milliseconds(1));
    }
    cerr << endl;
    running = false;
  }
  ~TestDevice(){}
  bool running;
  
};


int main(int argc, char *argv[] ) {

  OxI2CBus i2c( "/dev/null" );
  TestDevice test_device( "Test Device" );
  TestMultiplexer test_multi("Multiplexer");

  test_device.set_multiplexer( &test_multi );
  
  i2c.add_device( &test_device );
  i2c.run();

  while( test_device.running ) {
    b::this_thread::sleep(b::posix_time::milliseconds(6));
    cerr << "x";
  }

  i2c.stop();

  cerr << endl << "complete";
  
  return 0;
}
