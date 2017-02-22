#include <boost/chrono/system_clocks.hpp>
#include "devices/TCA9548A.h"
#include "devices/ARDUINO_DISP.h"
#include <iostream>
#include <cassert>
#include "trivial_log.h"

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );
    TCA9548A tca9548_4( TCA9548A_CH4 );
    TCA9548A tca9548_0( TCA9548A_OFF );
    ARDUINO_DISP d;


    d.set_multiplexer( &tca9548_4 );
    i2c.add_device( &d );        
    tca9548_4.rw_device();

    d.rw_device();

    d.set_multiplexer( &tca9548_0 );
    i2c.add_device( &d );
    tca9548_0.rw_device();

    return 0;

}
