/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __OX_I2C_DEVICE_H__
#define __OX_I2C_DEVICE_H__

#include "arduino_wire.h"
#include <string>

static const unsigned int MAX_RETRY_COUNT = 5000;

class OxI2CDevice {

public:

 OxI2CDevice( const std::string &name ) :  initialized(false),
    name( name ), multiplexer(0), device_failed(false), retry_count(0) {}

  inline std::string const & get_name() { return name; }

  void set_multiplexer( OxI2CDevice * multiplexer ) {
    this->multiplexer = multiplexer;
  }

  inline bool is_multiplexed() { return multiplexer != 0;}
  inline OxI2CDevice * get_multiplexer() { return multiplexer; }
  void set_bus( ArduinoWire *i2cbus ) { Wire = i2cbus; }

  inline bool is_device_failed() {
    if( device_failed ) {
      ++retry_count;
      if ( retry_count >= MAX_RETRY_COUNT  ) {
        device_failed = false;
        initialized = false;
        retry_count = 0;
      }
    }
    return device_failed;
  }
  inline void set_device_failed(){ device_failed = true; }

  virtual void rw_device() = 0;

  
protected:

  OxI2CDevice() {}  
  virtual ~OxI2CDevice(){}
  ArduinoWire *Wire;
  bool initialized;
  
private:

  const std::string name;
  OxI2CDevice *multiplexer;
  bool device_failed;
  unsigned int retry_count;

};

#endif
