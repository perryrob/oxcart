#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "oxapp.h"
#include "oxbluebus.h"
#include "oxBlueDevice.h"
#include "devices/KEYBOARD.h"
#include "named_store.h"

#include "trivial_log.h"

using namespace std;


int main(int argc, char *argv[] ) {
  
  init_log();

  KEYBOARD k("/dev/input/event1");

  k.run();
  b::this_thread::sleep(b::posix_time::milliseconds(100000));
  k.stop();
    
  return 0;
}
