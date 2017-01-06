#ifndef __oxbus_h__
#define __oxbus_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>

#include <deque>

#include "trivial_log.h"
#include "oxi2cdevice.h"
#include "ns.h"

class OxI2CBus : public ArduinoWire {

public:

  OxI2CBus() : keep_running(false) {}

  OxI2CBus(const char * i2c_bus) : ArduinoWire( i2c_bus ) {
    keep_running = false;
  }

  void run();
  void stop();
  void add_device( OxI2CDevice *device );

  inline bool running() { return keep_running;  }

  virtual ~OxI2CBus();
  
private:

  bool keep_running;
  
  b::thread * thr=0;
  std::deque<OxI2CDevice *> devices;

  void threaded_task();
};

#endif
