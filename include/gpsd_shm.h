/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/
#ifndef __GPSD_SHM_H__
#define __GPSD_SHM_H__

#include "trivial_log.h"
#include <libgpsmm.h>

class GPSD_SHM :  public gpsmm {

public:

  GPSD_SHM();
  
protected:

  bool streaming;
  
  virtual ~GPSD_SHM();
 
};


#endif
