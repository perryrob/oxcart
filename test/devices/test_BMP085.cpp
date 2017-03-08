/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <boost/chrono/system_clocks.hpp>
#include "devices/TCA9548A.h"
#include "devices/BMP085.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );

    TCA9548A tca9548_1( TCA9548A_CH1 );
    TCA9548A tca9548_2( TCA9548A_CH2 );
    TCA9548A tca9548_3( TCA9548A_CH3 );

    BMP085 p1;
    BMP085 p2;
    BMP085 p3;

    p1.set_multiplexer( &tca9548_1 );
    p2.set_multiplexer( &tca9548_2 );
    p3.set_multiplexer( &tca9548_3 );

    i2c.add_device(&p1);
    i2c.add_device(&p2);
    i2c.add_device(&p3);

    i2c.run();
    b::this_thread::sleep(b::posix_time::milliseconds(500));
    i2c.stop();
    
    // sensitive to Tucson
    assert( p3.lastPressure() > 1000.0 );
    assert( p3.lastAltitude() > 500.0 );
    assert( p3.lastTemperature() > 10.0 );
    
    cout << p3.lastPressure() << " " << p3.lastAltitude() << " " << p3.lastTemperature() << endl;

    boost::chrono::system_clock::time_point now = boost::chrono::system_clock::now();
    boost::chrono::nanoseconds sec =  now.time_since_epoch();
    cout << sec.count() << " nanoseconds" << endl;

    boost::chrono::microseconds microSecs = boost::chrono::duration_cast<boost::chrono::microseconds>(sec);
    cout << (long long)microSecs.count() << " microseconds" << endl;

  //Cast nanoseconds type to milliseconds type Here
    boost::chrono::milliseconds milliSecs = boost::chrono::duration_cast<boost::chrono::milliseconds>(sec);

    std::cout << (uint64_t)milliSecs.count() << " milliseconds" << endl;

return 0;

}
