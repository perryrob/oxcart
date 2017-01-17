#ifndef __OX_BLUE_DEVICE_H__
#define __OX_BLUE_DEVICE_H__

#include "blue_comm.h"
#include <string>

class OxBlueDevice {

public:

  OxBlueDevice( const std::string &name ) : name( name ) {}
  inline std::string const & get_name() { return name; }

  void set_bus( BlueComm *bus ) { this->bus = bus; }

  virtual void rw_device() = 0;
  
protected:

  BlueComm *bus;
  OxBlueDevice() {}  
  virtual ~OxBlueDevice(){}
  
private:

  const std::string name;
  
};

#endif
