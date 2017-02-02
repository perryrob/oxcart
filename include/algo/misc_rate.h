#ifndef __MISCRATE_H__
#define __MISCRATE_H__

#include "oxalgo.h"
#include "algo/linregres.h"

class MiscRate : public OxAlgo {

public:

  MiscRate();
  void run_algo();
  ~MiscRate();

 private:

  LinRegres * GPS_ACCEL_linear_regression;

};
#endif
