/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxi2cbus.h"


void OxI2CBus::threaded_task() {
  BOOST_LOG_TRIVIAL(debug) << "threaded_task()";
  while (keep_running) {
    BOOST_LOG_TRIVIAL(debug) <<  "while";
    for( std::deque<OxI2CDevice*>::iterator itr = devices.begin();
         itr != devices.end(); ++itr ) {
      BOOST_LOG_TRIVIAL(debug) <<  "for";
      if(  (*itr)->is_multiplexed() ) {
        BOOST_LOG_TRIVIAL(debug) <<  "multiplexer";
        (*itr)->get_multiplexer()->rw_device();
      }
      BOOST_LOG_TRIVIAL(debug) <<  "rw: " << (*itr)->get_name();
      (*itr)->rw_device();
    }
    b::this_thread::yield();
  }
  BOOST_LOG_TRIVIAL(debug) << "threaded_task() COMPLETE";
}


void OxI2CBus::run() {
  BOOST_LOG_TRIVIAL(debug) <<  "OxI2CBus::run() called";
  keep_running = true;
  thr = new b::thread(b::bind(&OxI2CBus::threaded_task, this));
  BOOST_LOG_TRIVIAL(debug) <<  "thread new";
}

void OxI2CBus::stop() {
  keep_running = false;
  thr->join();
  delete thr;
  thr = 0;
}

void OxI2CBus::add_device( OxI2CDevice *device ) {
  device->set_bus(this);
  if (device->get_multiplexer() != 0 ) {
    device->get_multiplexer()->set_bus(this);
  }
  devices.push_back( device );
  BOOST_LOG_TRIVIAL(debug) <<  "add_device: " << device->get_name();
}
  
OxI2CBus::~OxI2CBus() {
  if ( keep_running ) {
    BOOST_LOG_TRIVIAL(debug) <<  "~OxI2CBus, deleting thread..." << 
      keep_running << " " << thr;
    keep_running = false;
    delete thr;
  }
  devices.clear();
}
