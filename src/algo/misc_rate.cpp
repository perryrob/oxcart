
#include "oxapp.h"
#include "algo/misc_rate.h"
#include "trivial_log.h"

MiscRate::MiscRate() : OxAlgo( "Miscellaneous Rate", 150 ) {

    GPS_ACCEL_linear_regression = new LinRegres( 500 );
}

void MiscRate::run_algo() {

  GPS_ACCEL_linear_regression->update(OxApp::l_gps_fix->get_time(SPEED),
                               OxApp::l_gps_fix->get_val(SPEED));

  if (GPS_ACCEL_linear_regression->ready()) {
   OxApp::algo_misc_rate->set_val(GPS_ACCELERATION,
                                 GPS_ACCEL_linear_regression->slope_per_sec());
  }
}

MiscRate::~MiscRate() {

  delete GPS_ACCEL_linear_regression;

}
