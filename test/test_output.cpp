/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "output.h"
#include "oxapp.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 


int main(int argc, char *argv[] ) {

  OxApp::create();

  Output o(FILE_MODE,BASIC_LEVEL);

  o.run();
  b::this_thread::sleep(b::posix_time::milliseconds(1000*200));
  o.stop();

  return 0;

}
