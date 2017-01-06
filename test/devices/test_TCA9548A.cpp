#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "devices/TCA9548A.h"

int main(int argc, char * argv[] ) {

  OxI2CBus i2c( "/dev/i2c-2" );
  TCA9548A tca9548a_multi( TCA9548A_OFF );
  TCA9548A tca9548a( TCA9548A_CH2 );
  tca9548a.set_multiplexer( &tca9548a_multi );
  i2c.add_device( &tca9548a );
  i2c.run();
  b::this_thread::sleep(b::posix_time::milliseconds(5));
  i2c.stop();
  return 0;
  
}
