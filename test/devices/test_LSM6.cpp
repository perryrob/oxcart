
#include "oxi2cbus.h"
#include "devices/LSM6.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );
    LSM6 s;

    i2c.add_device(&s);

    i2c.run();
    b::this_thread::sleep(b::posix_time::milliseconds(10));
    i2c.stop();

    cerr << s.a.x << " " << s.a.y << " " << s.a.z << endl;
    cerr << s.g.x << " " << s.g.y << " " << s.g.z << endl;
    
    return 0;

}
