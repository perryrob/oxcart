#ifndef __OX_I2C_DEVICE_H__
#define __OX_I2C_DEVICE_H__

#include "arduino_wire.h"
#include <string>

class OxI2CDevice {

public:

  OxI2CDevice( const std::string &name ) : name( name ), multiplexer(0) {}
  inline std::string const & get_name() { return name; }

  void set_multiplexer( OxI2CDevice * multiplexer ) {
    this->multiplexer = multiplexer;
  }

  inline bool is_multiplexed() { return multiplexer != 0;}
  inline OxI2CDevice * get_multiplexer() { return multiplexer; }
  void set_bus( ArduinoWire *i2cbus ) { Wire = i2cbus; }

  virtual void rw_device() = 0;

  
protected:

  ArduinoWire *Wire;  
  OxI2CDevice() {}  
  virtual ~OxI2CDevice(){}

private:

  const std::string name;
  OxI2CDevice *multiplexer;
  
};

#endif
