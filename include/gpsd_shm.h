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
