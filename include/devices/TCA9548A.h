#ifndef __TCA9548A_H__
#define __TCA9548A_H__

#include "arduino_wire.h"
#include "oxi2cbus.h"
#include "oxi2cdevice.h"

#define TCA9548A_OFF 0x00
#define TCA9548A_CH1 0x01
#define TCA9548A_CH2 0x02
#define TCA9548A_CH3 0x04
#define TCA9548A_CH4 0x08


class TCA9548A : public OxI2CDevice {

public:

  TCA9548A( uint8_t channel) : OxI2CDevice( "TCA9548A"),channel( channel ){}
  void rw_device();
  inline uint8_t get_channel() {return channel;}
  
private:

  uint8_t channel;
  static const uint8_t ADDRESS;

};
#endif
