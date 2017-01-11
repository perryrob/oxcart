
#include "devices/TCA9548A.h"
#include "devices/BMP085.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );
    TCA9548A tca9548( TCA9548A_CH2 );
    BMP085 p;

    p.set_multiplexer( &tca9548 );
    i2c.add_device(&p);

    i2c.run();
    b::this_thread::sleep(b::posix_time::milliseconds(10));
    i2c.stop();

    // sensitive to Tucson
    assert( p.lastPressure() > 1000.0 );
    assert( p.lastAltitude() > 500.0 );
    assert( p.lastTemperature() > 10.0 );
    
    cout << p.lastPressure() << " " << p.lastAltitude() << " " << p.lastTemperature() << endl;

return 0;

}
