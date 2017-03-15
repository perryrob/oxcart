/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __NCURSES_H__
#define __NCURSES_H__

#include <stdint.h>
#include <string>

class NCURSES_DISP {

 public:
  NCURSES_DISP();

  void render_page();
  
  void rw_device();
  ~NCURSES_DISP();
  
 private:
  void led_on( uint8_t LED, bool on );
  void write_string( uint8_t x, uint8_t y, uint8_t size, const std::string &msg);
  bool init;
  uint64_t last_update;

};


#endif
