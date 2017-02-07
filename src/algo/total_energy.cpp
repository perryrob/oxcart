
#include "oxapp.h"
#include "algo/total_energy.h"
#include "trivial_log.h"

TotalEnergy::TotalEnergy() : OxAlgo( "Total Energy",100 ) {

    TE_linear_regression = new LinRegres( 2500 );
    AIRSPEED_linear_regression = new LinRegres( 1000 );
    TAS_linear_regression = new LinRegres( 1000 );
    ALTITUDE_linear_regression = new LinRegres( 2500 );
    TE_ALTITUDE_linear_regression = new LinRegres( 2500 );

    TE_ALTITUDE_linear_regression->set_filter(1.0,
                                             0.2,
                                             1.5,
                                             1.0);

  }

void TotalEnergy::run_algo() {

  AIRSPEED_linear_regression->update(OxApp::algo_press->get_time(AIRSPEED),
                                     OxApp::algo_press->get_val(AIRSPEED));
  if (AIRSPEED_linear_regression->ready()) {
    OxApp::algo_press_rate->set_val(PRESSURE_AIRSPEED, 
                                   AIRSPEED_linear_regression->slope_per_sec());
  }
  
  TAS_linear_regression->update(OxApp::algo_press->get_time(TAS),
                               OxApp::algo_press->get_val(TAS));
  if (TAS_linear_regression->ready()) {
    OxApp::algo_press_rate->set_val(PRESSURE_TAS, 
                                    TAS_linear_regression->slope_per_sec());
  }

  ALTITUDE_linear_regression->update(OxApp::algo_press->get_time(ALTITUDE),
                               OxApp::algo_press->get_val(ALTITUDE));
  if (ALTITUDE_linear_regression->ready()) {
    OxApp::algo_press_rate->set_val(PRESSURE_ALTITUDE, 
                                ALTITUDE_linear_regression->slope_per_sec());
  }
  /**
   * This isn't setting the correct values, hmmmmmm.
   */
  TE_linear_regression->update( OxApp::l_pressure->get_time(BMP_TE),
                                OxApp::l_pressure->get_val(BMP_TE));
  if (TE_linear_regression->ready()) {
    OxApp::algo_press_rate->set_val(PRESSURE_TE,
                                    TE_linear_regression->slope_per_sec());
  }
  
  TE_ALTITUDE_linear_regression->update(
                               OxApp::algo_press->get_time(TE_ALTITUDE),
                               OxApp::algo_press->get_val(TE_ALTITUDE));
  if (TE_ALTITUDE_linear_regression->ready()) {
    OxApp::algo_press_rate->set_val(PRESSURE_TE_ALTITUDE, 
                                    TE_ALTITUDE_linear_regression->slope_per_sec());
  }
}

TotalEnergy::~TotalEnergy() {

  delete TE_linear_regression;
  delete AIRSPEED_linear_regression;
  delete TAS_linear_regression;
  delete ALTITUDE_linear_regression;
  delete TE_ALTITUDE_linear_regression;

}
