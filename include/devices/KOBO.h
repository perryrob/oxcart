#ifndef __KOBO_H__
#define  __KOBO_H__

#include "algo/polar.h"
#include "oxBlueDevice.h"

class KOBO : public OxBlueDevice {

public:

 KOBO(uint64_t interval=100) : OxBlueDevice( "KOBO" ),
    interval(interval), last_run(0) {}
  void rw_device();
  ~KOBO() {};

 private:
  Polar polar;
  uint64_t interval;
  uint64_t last_run;

};

#endif


