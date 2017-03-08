/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "oxalgo.h"


bool OxAlgo::run_it() {

  if ( OxApp::get_time_ms() - last_run >= interval ) {
    last_run = OxApp::get_time_ms();
    return true;
  }
  return false;
}
