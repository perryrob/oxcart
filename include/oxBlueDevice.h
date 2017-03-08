/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

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
