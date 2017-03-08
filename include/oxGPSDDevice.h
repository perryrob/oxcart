/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __OX_GPSD_DEVICE_H__
#define __OX_GPSD_DEVICE_H__

#include "gpsd_shm.h"
#include <string>

class OxGPSDDevice {

public:

  OxGPSDDevice( const std::string &name ) : name( name ) {}
  inline std::string const & get_name() { return name; }

  void set_bus( GPSD_SHM *gpsd_shm ) { this->gpsd_shm = gpsd_shm; }

  virtual void rw_device() = 0;

  
protected:

  GPSD_SHM *gpsd_shm;
  OxGPSDDevice() {}  
  virtual ~OxGPSDDevice(){}

  gps_data_t* gps_data;
  
private:

  const std::string name;
  
};

#endif
