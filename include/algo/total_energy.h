#ifndef __AIRDATA_H__
#define __AIRDATA_H__

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
