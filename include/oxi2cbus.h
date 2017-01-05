#ifndef __oxbus_h__
#define __oxbus_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>

#include <deque>

#include "arduino_wire.h"
#include "oxi2cdevice.h"
#include "ns.h"

class OxI2CBus : public ArduinoWire {

public:

  OxI2CBus() : is_running(false) {}

  OxI2CBus(const char * i2c_bus) : ArduinoWire( i2c_bus ) {
    is_running = false;
  }
  
  inline void run() {
    thr = new b::thread(b::bind(&OxI2CBus::threaded_task, this));
    is_running = true;
  }
  inline void stop() {
    is_running = false;
    thr->join();
    delete thr;
    thr = 0;
  }

  void add_device( OxI2CDevice *device ) {
    devices.push_back( device );
  }
  
  inline bool running() { return is_running;  }

  virtual ~OxI2CBus() {
    delete thr;
    is_running = false;
    devices.clear();
  }
  
  
private:

  bool is_running;
  
  b::thread * thr=0;
  std::deque<OxI2CDevice *> devices;

  void threaded_task() {
    while (is_running) {
      for( std::deque<OxI2CDevice*>::iterator itr = devices.begin();
           itr != devices.end(); ++itr ) {
        if(  (*itr)->is_multiplexed() ) {
          (*itr)->get_multiplexer()->rw_sensor();
        }
        (*itr)->rw_sensor();
      }
    }
  }
};

#endif
