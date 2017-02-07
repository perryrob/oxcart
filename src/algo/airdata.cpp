
#include "constants.h"
#include "oxapp.h"
#include "algo/airdata.h"

void Airdata::run_algo() {
  /**
   * Indicated Airspeed
   */
  int32_t pt =  OxApp::l_pressure->get_val( BMP_PITOT );
  if (pt < OxApp::l_pressure->get_val( BMP_STATIC )) {
    pt = OxApp::l_pressure->get_val( BMP_STATIC );
  }
  OxApp::algo_press->set_val( AIRSPEED, sqrt( 2.0 *
                (pt - OxApp::l_pressure->get_val( BMP_STATIC )) /
                                              SI_RHO));
  /**
   * True Airspeed
   */
  double local_rho =  OxApp::l_pressure->get_val( BMP_PITOT ) /
    SI_R /  (OxApp::l_temp->get_val( BMP_PITOT ) + KELVIN);
  OxApp::algo_press->set_val( TAS, OxApp::algo_press->get_val( AIRSPEED ) *
                              sqrt( SI_RHO / local_rho ));
  
}
