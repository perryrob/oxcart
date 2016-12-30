#ifndef __oxdev_h__
#define __oxdev_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include "ns.h"

class OxDev  {

public:

  OxDev(){ is_running = false; }
  
  inline void run() {
    thr = new b::thread(b::bind(&OxDev::threaded_task, this));
    is_running = true;
  }
  inline void stop() {
    is_running = false;
    thr->join();
  }

  static void set_shared_mem( bip::managed_shared_memory * s ) {
    OxDev::shm = s;
  }
  inline bool running() { return is_running;  }
  virtual ~OxDev() {
    delete thr;
    is_running = false;
  }
  
protected:

  virtual void threaded_task() = 0;
  bool is_running;
  static bip::managed_shared_memory * shm;
  
private:

  b::thread * thr;

};
bip::managed_shared_memory * OxDev::shm = 0;
#endif
