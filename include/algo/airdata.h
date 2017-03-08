/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __AIRDATA_H__
#define __AIRDATA_H__

#include "oxalgo.h"

class Airdata : public OxAlgo {

public:
  Airdata() : OxAlgo( "Airdata",100 ) {};
  void run_algo();

  
};
#endif
