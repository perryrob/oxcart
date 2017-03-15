
#include "devices/NCURSES.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread/thread.hpp>
#include "ns.h"

using namespace std;

int main(int argc, char * argv [] ) {

  NCURSES_DISP nd;

  for(int i=0; i < 10; ++i ) {
    nd.rw_device();
    b::this_thread::sleep(b::posix_time::milliseconds(100));
  }

  return 0;
}
