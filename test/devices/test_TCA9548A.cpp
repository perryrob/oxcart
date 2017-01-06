#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "devices/TCA9548A.h"
#include "trivial_log.h"


int main(int argc, char * argv[] ) {

  init_log();
  /**
  BOOST_LOG_TRIVIAL(debug) << "main" ;
  OxI2CBus i2c( "/dev/i2c-2" );
  BOOST_LOG_TRIVIAL(debug) << "bus" ;
  TCA9548A tca9548a_multi( TCA9548A_OFF );
  BOOST_LOG_TRIVIAL(debug) << "multi" ;
  TCA9548A tca9548a( TCA9548A_CH2 );
  BOOST_LOG_TRIVIAL(debug) << "device" ;
  tca9548a.set_multiplexer( &tca9548a_multi );
  BOOST_LOG_TRIVIAL(debug) << "set multi" ;
  i2c.add_device( &tca9548a );
  BOOST_LOG_TRIVIAL(debug) << "add device" ;
  i2c.run();
  BOOST_LOG_TRIVIAL(debug) << "run" ;
  b::this_thread::sleep(b::posix_time::milliseconds(100));
  BOOST_LOG_TRIVIAL(debug) << "WAKE UP" ;
  i2c.stop();
  BOOST_LOG_TRIVIAL(debug) << "stop" ;
  */

  OxI2CBus i2c( "/dev/i2c-2" );

  TCA9548A tca9548a_multi( TCA9548A_OFF );
  TCA9548A tca9548a( TCA9548A_CH2 );
  TCA9548A tca9548a_off( TCA9548A_OFF );

  tca9548a.set_multiplexer( &tca9548a_multi );

  i2c.add_device( &tca9548a );
  i2c.add_device( &tca9548a_off );

  i2c.run();
  b::this_thread::sleep(b::posix_time::milliseconds(10));
  i2c.stop();

  return 0;
  
}
