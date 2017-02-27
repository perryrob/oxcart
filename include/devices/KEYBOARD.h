#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#include "key_mapper.h"
#include "oxBlueDevice.h"
#include "ns.h"

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};


class KEYBOARD {

public:
  KEYBOARD(const char * dev);
  
  void run();
  void stop();
  ~KEYBOARD() {};

private:
  void threaded_task();
  void open_keyboard();
  std::string buffer;
  int device_fd;
  bool failed;
  bool keep_running;
  KeyMapper key_mapper;
  int rv;
  struct timeval timeout;
  fd_set set;
  std::string device;
  b::thread * thr=0;
};
#endif


