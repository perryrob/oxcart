
#include "oxapp.h"
#include "oxalgo.h"


bool OxAlgo::run_it() {

  if ( OxApp::get_time_ms() - last_run >= interval ) {
    last_run = OxApp::get_time_ms();
    return true;
  }
  return false;
}
