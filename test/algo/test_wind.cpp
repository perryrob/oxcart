/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "algo/wind.h"
#include "conversion.h"
#include <cmath>
#include <cassert>

using namespace std;

int main(int argc, char *argv[] ) {

  OxApp::create();

  OxApp::algo_press->set_val( TAS, 25.0 );
  OxApp::l_gps_fix->set_val(  SPEED, 25.0 );
  OxApp::l_gps_fix->set_val( TRACK,  M_PI / 4.0); // 45
  OxApp::algo_mad_euler->set_val( YAW,  M_PI / 4.0);
  
  Wind wind;

  wind.run_algo();

  assert( Conv::knots(OxApp::algo_wind->get_val( WIND_SPEED )) == 0 );
  assert( Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) == 45 );

  /*****************************************************************************/

  OxApp::algo_press->set_val( TAS, 50.0 );
  OxApp::l_gps_fix->set_val(  SPEED, 55 );
  OxApp::l_gps_fix->set_val( TRACK,  M_PI / 4.0); // 45
  OxApp::algo_mad_euler->set_val( YAW,  M_PI / 4.0);
  
  wind.run_algo();

  assert( OxApp::algo_wind->get_val( WIND_SPEED ) == 5 );
  assert( Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) == 180.0 + 45.0 );

   /*****************************************************************************/

  OxApp::algo_press->set_val( TAS, 50.0 );
  OxApp::l_gps_fix->set_val(  SPEED, 45 );
  OxApp::l_gps_fix->set_val( TRACK,  M_PI / 4.0); // 45
  OxApp::algo_mad_euler->set_val( YAW,  M_PI / 4.0);
  
  wind.run_algo();

  assert( OxApp::algo_wind->get_val( WIND_SPEED ) == 5 );
  assert( Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) == 45.0 );

   /*****************************************************************************/
  // http://www.raeng.org.uk/publications/other/1-aircraft-navigation
  OxApp::algo_press->set_val( TAS, Conv::knots2ms(100.0));
  OxApp::l_gps_fix->set_val(  SPEED, Conv::knots2ms(86.7));
  OxApp::l_gps_fix->set_val( TRACK,  Conv::deg2rad(54.0)); 
  OxApp::algo_mad_euler->set_val( YAW,  Conv::deg2rad(44.7));
  
  wind.run_algo();

  assert( OxApp::algo_wind->get_val( WIND_SPEED ) > Conv::knots2ms(20.0) );
  assert( OxApp::algo_wind->get_val( WIND_SPEED ) < Conv::knots2ms(21.0) );
  assert( Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) > Conv::rad2deg(0.0));
  assert( Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) < Conv::rad2deg(1.0));


  /*****************************************************************************/

  OxApp::algo_press->set_val( TAS, Conv::knots2ms(100.0));
  OxApp::l_gps_fix->set_val(  SPEED, Conv::knots2ms(100.0));

  for (double deg = 0.0; deg < 360.0; deg=deg+1.0) {
    
    OxApp::l_gps_fix->set_val( TRACK,  Conv::deg2rad(deg)); 
    OxApp::algo_mad_euler->set_val( YAW,  Conv::deg2rad(deg));

    wind.run_algo();
    
    assert( OxApp::algo_wind->get_val( WIND_SPEED ) == 0.0 );
    assert( fabs(Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )) - deg) < 1.0);
  }
  /*****************************************************************************/

  OxApp::algo_press->set_val( TAS, Conv::knots2ms(100.0));
  OxApp::l_gps_fix->set_val(  SPEED, Conv::knots2ms(90.0));

  for (double deg = 0.0; deg < 296; deg=deg+1.0) {
    
    OxApp::l_gps_fix->set_val( TRACK,  Conv::deg2rad(deg)); 
    OxApp::algo_mad_euler->set_val( YAW,  Conv::deg2rad(deg + 10.0));

    wind.run_algo();

    assert( OxApp::algo_wind->get_val( WIND_SPEED ) - 10.0 < 1.0 );
    assert( fabs(deg - fabs(Conv::rad2deg(OxApp::algo_wind->get_val( WIND_DIR )))) < 64.0);
  }
  
   return 0;
}
