#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include "ns.h"

static const unsigned int FILE_MODE=0;
static const unsigned int CONSOLE_MODE=1;

static const unsigned int BASIC_LEVEL=0;
static const unsigned int DEBUG_LEVEL=1;
static const unsigned int FLIGTH_COLLECT_LEVEL=2;

static const unsigned int MAX_FILE_SIZE=10000000; // 10Mb
static const char S = ';';

static const std::string BONE_PATH="/mnt/sdcard/data/OXCART.csv";

class Output {

public:

  Output(unsigned int mode, unsigned int level);
  void run();
  void stop();
  ~Output();

private:

  void threaded_task();
  b::thread * thr=0;
  bool keep_running;
  unsigned int _mode;
  unsigned int _level;

};
#endif
