/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/
#ifndef __oxBLUEbus_h__
#define __oxBLUEbus_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>

#include <deque>

#include "oxBlueDevice.h"
#include "blue_comm.h"
#include "ns.h"

class OxBluebus : public BlueComm {

public:

  OxBluebus(){}
  OxBluebus(std::string &address, int channel);

  void run();
  void stop();
  void add_device( OxBlueDevice *device );

  inline bool running() { return keep_running;  }

  virtual ~OxBluebus();
  
private:

  bool keep_running;
  
  b::thread * thr=0;

  std::deque<OxBlueDevice *> devices;

  void threaded_task();
};

#endif
