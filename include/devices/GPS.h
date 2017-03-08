/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __GPS_H__
#define __GPS_H__

#include "oxGPSDDevice.h"

#include <gps.h>
#include "gpsd/gpsd_config.h"
#include "gpsd/gpsdclient.h"
#include "gpsd/revision.h"


class GPS : public OxGPSDDevice {

public:

 GPS() : OxGPSDDevice( "GPS" ) {}

  void rw_device();
  void NMEA();
  inline struct gps_data_t* get_data() { return new_gps_data; }
  
  ~GPS() {}
  
private:
  struct gps_data_t* new_gps_data;
};

#endif


