#ifndef __AIRDATA_H__
#define __AIRDATA_H__

#include "oxalgo.h"

const double RHO = 1.225;
const double R   = 287.1;

class Airdata : public OxAlgo {

public:
  Airdata() : OxAlgo( "Airdata",100 ) {};
  void run_algo();

  
};
#endif
