#ifndef __KOBO_H__
#define  __KOBO_H__

#include "oxBlueDevice.h"

class KOBO : public OxBlueDevice {

public:

  KOBO() : OxBlueDevice( "KOBO" ) {}
  void rw_device();
  ~KOBO() {};

};

#endif


