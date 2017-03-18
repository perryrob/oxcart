/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "algo/turbulence.h"
#include <cassert>
#include <random>

using namespace std;

int main(int argc, char *argv[] ) {

  init_log();
  
  OxApp::create();

  Turbulence turb;

  random_device rd;
  mt19937 mt(rd());    
  uniform_real_distribution<double> dist(1.0,2.0);

  for(unsigned int i=0; i < 400; ++i) {
    OxApp::algo_misc_rate->set_val(LOAD_FACTOR, dist(mt));
    turb.run_algo();
    if (turb.ready()) {
      BOOST_LOG_TRIVIAL(debug) << "freq: " << turb.freq();
      BOOST_LOG_TRIVIAL(debug) << "amp: " << turb.amp();
    }
  }

  return 0;
}
