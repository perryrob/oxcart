

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
