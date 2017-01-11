#ifndef __oxGPSDbus_h__
#define __oxGPSDbus_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>

#include <deque>

#include "oxGPSDDevice.h"
#include "gpsd_shm.h"
#include "ns.h"

class OxGPSDbus : public GPSD_SHM {

public:

  OxGPSDbus() : GPSD_SHM(), keep_running(false) {}

  void run();
  void stop();
  void add_device( OxGPSDDevice *device );

  inline bool running() { return keep_running;  }

  virtual ~OxGPSDbus();
  
private:

  bool keep_running;
  
  b::thread * thr=0;

  std::deque<OxGPSDDevice *> devices;

  void threaded_task();
};

#endif
