/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/
#ifndef __COMMAND_PROC_H__
#define __COMMAND_PROC_H__

#include <linux/input.h>
#include "key_mapper.h"
#include "trivial_log.h"
#include <string>

static const uint8_t DO_NOTHING=0;
static const uint8_t SET_ALT=1;
static const uint8_t SET_PITCH=2;
static const uint8_t SET_MAC=3;

class CommandProc {

 public:
  CommandProc() {}
  void init();
  void process_event(  struct input_event &ev );

 private:
  KeyMapper key_mapper;
  std::string buffer;
  uint8_t CMD;
  uint8_t cmd_pressed;
  void process_command();
};

#endif
