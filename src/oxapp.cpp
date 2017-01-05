#include "oxapp.h"
#include <boost/interprocess/managed_shared_memory.hpp>

bip::managed_shared_memory * OxApp::create() {
  //Create or open shared memory segment.
  if (OxApp::shm == 0) {
    OxApp::shm = new bip::managed_shared_memory(bip::open_or_create,
                                                MEM_NAME.c_str(),
                                                MEM_SIZE*sizeof(std::size_t));
  }
  return OxApp::shm;
}
/************************************************************
 * Careful calling destroy, since it nukes the entire shared
 * memory pool. This should only be called when all apps are
 * shut down that want to access it.
 */
void OxApp::destroy() {
  bip::shared_memory_object::remove( MEM_NAME.c_str() );
  delete OxApp::shm;
  OxApp::shm = 0;
}

