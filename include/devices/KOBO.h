#ifndef __KOBO_H__
#define  __KOBO_H__

#include "algo/polar.h"
#include "oxBlueDevice.h"

class KOBO : public OxBlueDevice {

public:

  KOBO() : OxBlueDevice( "KOBO" ) {}
  void rw_device();
  ~KOBO() {};

 private:
  Polar polar;

};

#endif


