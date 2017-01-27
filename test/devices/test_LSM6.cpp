
#include "oxapp.h"
#include "oxi2cbus.h"
#include "devices/LSM6.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char * argv [] ) {

    OxI2CBus i2c( "/dev/i2c-2" );
    LSM6 s;

    i2c.add_device(&s);

    s.rw_device();
    
    cerr <<  OxApp::l_accel->get_val(X) << " " <<
         OxApp::l_accel->get_val(Y) << " " <<
      OxApp::l_accel->get_val(Z) << endl;

    cerr <<  OxApp::l_gyro->get_val(X) << " " <<
      OxApp::l_gyro->get_val(Y) << " " <<
      OxApp::l_gyro->get_val(Z) << endl;
    
    return 0;

}
