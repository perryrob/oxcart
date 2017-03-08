/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxGPSDbus.h"
#include "trivial_log.h"

void OxGPSDbus::threaded_task() {
  BOOST_LOG_TRIVIAL(debug) << "GPS_BUS threaded_task()";
  while (keep_running) {
    BOOST_LOG_TRIVIAL(debug) << "GPS_BUS while";
    for( std::deque<OxGPSDDevice*>::iterator itr = devices.begin();
         itr != devices.end(); ++itr ) {
      BOOST_LOG_TRIVIAL(debug) << "GPS_BUS for";
      (*itr)->rw_device();
      BOOST_LOG_TRIVIAL(debug) << "GPS_BUS rw: " << (*itr)->get_name();
    }
    b::this_thread::yield();
  }
  BOOST_LOG_TRIVIAL(debug) << "GPS_BUS threaded_task() COMPLETE";
}

void OxGPSDbus::run() {
  BOOST_LOG_TRIVIAL(debug) <<  "GPS_BUS run called";
  keep_running = true;
  thr = new b::thread(b::bind(&OxGPSDbus::threaded_task, this));
  BOOST_LOG_TRIVIAL(debug) <<  "GPS_BUS thread new";
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
  BOOST_LOG_TRIVIAL(debug) <<  "GPS_BUS add_device: " << device->get_name();
}
  
OxGPSDbus::~OxGPSDbus() {
  keep_running = false;
  delete thr;
  devices.clear();
}
