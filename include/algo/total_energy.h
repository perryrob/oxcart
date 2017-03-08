/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __TOTAL_ENERGY_H__
#define __TOTAL_ENERGY_H__

#include "oxalgo.h"
#include "algo/linregres.h"

class TotalEnergy : public OxAlgo {

public:

  TotalEnergy();
  void run_algo();
  ~TotalEnergy();

 private:

  LinRegres * TE_linear_regression;
  LinRegres * AIRSPEED_linear_regression;
  LinRegres * TAS_linear_regression;
  LinRegres * ALTITUDE_linear_regression;
  LinRegres * TE_ALTITUDE_linear_regression;
};
#endif
