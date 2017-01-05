#ifndef __OX_I2C_DEVICE_H__
#define __OX_I2C_DEVICE_H__

#include <string>

class OxI2CDevice {

public:

  OxI2CDevice( const std::string &name ) : name( name ) {}
  inline std::string const & get_name() { return name; }

  
  virtual void read_sensor() = 0;

protected:
  
  OxI2CDevice() {}  
  virtual ~OxI2CDevice(){};

private:
  const std::string name;

};

#endif
