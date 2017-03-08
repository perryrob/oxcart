/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

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
  LinRegres * PITCH_RATE_linear_regression;

};
#endif
