/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __oxalgothread_h__
#define __oxalgothread_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>

#include <deque>

#include "oxalgo.h"
#include "trivial_log.h"
#include "ns.h"

class OxAlgoThread {

public:

  OxAlgoThread() : keep_running(false) {}

  void run();
  void stop();
  void add_algo( OxAlgo *algo );

  inline bool running() { return keep_running;  }

  virtual ~OxAlgoThread();
  
private:

  bool keep_running;
  
  b::thread * thr=0;
  std::deque<OxAlgo *> algos;

  void threaded_task();
};

#endif
