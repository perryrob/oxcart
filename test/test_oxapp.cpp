#include <boost/interprocess/managed_shared_memory.hpp>

#include "oxapp.h"
#include "ns.h"

int main(int argc, char *argv[] ) {

  OxApp::create();
  bip::managed_shared_memory * shm = OxApp::get_shared_mem();
  assert( shm != 0 );
  OxApp::destroy();
  shm = OxApp::get_shared_mem();
  assert( shm == 0 );
  return 0;
}
