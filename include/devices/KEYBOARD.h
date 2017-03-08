/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#include "command_proc.h"
#include "key_mapper.h"
#include "oxBlueDevice.h"
#include "ns.h"

class KEYBOARD {

public:
  KEYBOARD(const char * dev);
  
  void run();
  void stop();
  ~KEYBOARD() {};

private:
  CommandProc command_proc;
  void threaded_task();
  void open_keyboard();
  int device_fd;
  bool failed;
  bool keep_running;
  int rv;
  struct timeval timeout;
  fd_set set;  
  std::string device;
  b::thread * thr=0;
};
#endif


