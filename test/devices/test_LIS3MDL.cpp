/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

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
    b::this_thread::sleep(b::posix_time::milliseconds(5000));
    i2c.stop();

    cerr << s.m.x << " " << s.m.y << " " << s.m.z << endl;
    
    return 0;

}
