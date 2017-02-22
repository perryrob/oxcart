#ifndef __ARDUINO_DISP_H__
#define __ARDUINO_DISP_H__

#include "arduino_core.h"
#include "oxi2cdevice.h"

#define DEBUG 0

#define BLACK 0
#define WHITE 1

#define LED_1_OFF 0x11
#define LED_2_OFF 0x12
#define LED_3_OFF 0x13
#define LED_1_ON  0x14
#define LED_2_ON  0x15
#define LED_3_ON  0x16


#define ARDUINO_I2CADDR 0x20

class ARDUINO_DISP : public OxI2CDevice {

 public:
  ARDUINO_DISP();

  void rw_device();
  ~ARDUINO_DISP() {} 
    
 private:


};


#endif
