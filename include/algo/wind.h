#ifndef __WIND_H__
#define __WIND_H__

#include "oxalgo.h"

class Wind : public OxAlgo {

 public:
  Wind() : OxAlgo("Wind",100) {};
  void run_algo();
};

#endif
