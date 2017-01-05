#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include "oxmem.h"
#include "oxi2cbus.h"
#include "oxi2cdevice.h"
#include "named_store.h"

using namespace std;


class TestDevice : public OxI2CDevice {

public:

  TestDevice( const string &name ) : OxI2CDevice( name ) {
    running = true;
  }
                                                       
  void read_sensor() {
    for( int i=0; i < 1000; ++i ) {
      cerr << ".";
    }
    cerr << endl;
    running = false;
  }

  bool running;
  
};


int main(int argc, char *argv[] ) {

  OxI2CBus i2c( "/dev/null" );
  TestDevice test_device( "Test Device" );
  i2c.add_device( &test_device );
  i2c.run();

  while( test_device.running ) {
    cerr << "x";
  }
    
  cerr << endl << "complete";

  
  return 0;
}
