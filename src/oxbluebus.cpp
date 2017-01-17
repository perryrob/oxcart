#include "oxbluebus.h"
#include "trivial_log.h"

OxBluebus::OxBluebus(std::string &address, int channel) : 
  BlueComm(address, channel),
  keep_running(false) {
  open();
}

void OxBluebus::threaded_task() {
  while (keep_running) {
    for( std::deque<OxBlueDevice*>::iterator itr = devices.begin();
         itr != devices.end(); ++itr ) {
      (*itr)->rw_device();
    }
    b::this_thread::yield();
  }
}

void OxBluebus::run() {
  keep_running = true;
  thr = new b::thread(b::bind(&OxBluebus::threaded_task, this));
}

void OxBluebus::stop() {
  keep_running = false;
  thr->join();
  delete thr;
  thr = 0;
}

void OxBluebus::add_device( OxBlueDevice *device ) {
  if ( is_open() ) {
    device->set_bus( this );  
    devices.push_back( device );
    BOOST_LOG_TRIVIAL(debug) <<  "device added";
  } else {
    BOOST_LOG_TRIVIAL(warning) <<  "device NOT added, Bluetooth is not open";
  }
}
  
OxBluebus::~OxBluebus() {
  keep_running = false;
  delete thr;
  devices.clear();
  close();
}
