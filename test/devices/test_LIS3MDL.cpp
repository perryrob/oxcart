
#include "oxi2cbus.h"
#include "devices/LIS3MDL.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );
    LIS3MDL s;

    i2c.add_device(&s);

    i2c.run();
    b::this_thread::sleep(b::posix_time::milliseconds(10));
    i2c.stop();

    cerr << s.m.x << " " << s.m.y << " " << s.m.z << endl;
    
    return 0;

}
