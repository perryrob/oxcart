#include "oxapp.h"
#include "algo/airdata.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char *argv[] ) {

  Airdata ad;

  OxApp::l_pressure->set_val( BMP_PITOT, 93037.0 );
  OxApp::l_pressure->set_val( BMP_STATIC, 93037.0 );
  OxApp::l_temp->set_val( BMP_STATIC, 20.0 );

  ad.run_algo();

  assert( OxApp::algo_press->get_val( AIRSPEED ) == 0 );
  assert( OxApp::algo_press->get_val( TAS ) == 0 );

  OxApp::l_pressure->set_val( BMP_PITOT, 93037.0 );
  OxApp::l_pressure->set_val( BMP_STATIC, 93047.0 );
  OxApp::l_temp->set_val( BMP_STATIC, 20.0 );

  ad.run_algo();

  assert( OxApp::algo_press->get_val( AIRSPEED ) == 0 );
  assert( OxApp::algo_press->get_val( TAS ) == 0 );

  OxApp::l_pressure->set_val( BMP_PITOT,  70000.0 );
  OxApp::l_pressure->set_val( BMP_STATIC, 67629.53 );
  OxApp::l_temp->set_val( BMP_STATIC, 20.0 );

  ad.run_algo();

  assert( OxApp::algo_press->get_val( AIRSPEED ) *  1.94384 > 120.0); //knots
  assert( OxApp::algo_press->get_val( AIRSPEED ) *  1.94384 < 121.0); //knots
  assert( OxApp::algo_press->get_val( TAS ) > 72.0 ); // m/s
  assert( OxApp::algo_press->get_val( TAS ) < 73.0 );// m/s
  
  cerr << OxApp::algo_press->get_val( AIRSPEED ) * 1.94384<< " " << 
    OxApp::algo_press->get_val( TAS ) << endl;
  
  return 0;
}
