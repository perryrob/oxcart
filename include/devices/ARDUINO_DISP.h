/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __ARDUINO_DISP_H__
#define __ARDUINO_DISP_H__

#include "arduino_core.h"
#include "oxi2cdevice.h"
#include <map>
#include <string>

#define DEBUG 0

#define BLACK 0
#define WHITE 1

#define LED_1_OFF 0x11
#define LED_2_OFF 0x12
#define LED_3_OFF 0x13
#define LED_1_ON  0x14
#define LED_2_ON  0x15
#define LED_3_ON  0x16

#define TXT_CMD   0x20
#define CLEAR_CMD 0x50

#define ARDUINO_I2CADDR 0x20

static const uint8_t MAX_PAGES=3;

class ARDUINO_DISP : public OxI2CDevice {

 public:
  ARDUINO_DISP();

  void render_page();
  
  void rw_device();
  ~ARDUINO_DISP() {} 
  
 private:
  void led_on( uint8_t LED, bool on );
  void write_string( uint8_t x, uint8_t y, uint8_t size, const std::string &msg);
  bool init;
  uint64_t last_update;
  std::map<uint16_t,std::string> display_text;
  std::map<uint16_t,uint8_t> display_size;
};


#endif
