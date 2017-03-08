/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"

int main(int argc, char *argv[] ) {

  OxApp::create();
  bip::managed_shared_memory * shm = OxApp::get_shared_mem();
  assert( shm != 0 );
  OxApp::destroy();
  shm = OxApp::get_shared_mem();
  std::cout << OxApp::get_time_ms() << std::endl;
  assert( shm == 0 );
  return 0;
}
