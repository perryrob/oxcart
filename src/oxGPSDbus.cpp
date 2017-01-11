#include "oxGPSDbus.h"

void OxGPSDbus::threaded_task() {
  while (keep_running) {
    for( std::deque<OxGPSDDevice*>::iterator itr = devices.begin();
         itr != devices.end(); ++itr ) {
      (*itr)->rw_sensor();
    }
  }
}

void OxGPSDbus::run() {
  keep_running = true;
  thr = new b::thread(b::bind(&OxGPSDbus::threaded_task, this));
}

void OxGPSDbus::stop() {
  keep_running = false;
  thr->join();
  delete thr;
  thr = 0;
}

void OxGPSDbus::add_device( OxGPSDDevice *device ) {
  device->set_bus( this );
  devices.push_back( device );
}
  
OxGPSDbus::~OxGPSDbus() {
  keep_running = false;
  delete thr;
  devices.clear();
}
