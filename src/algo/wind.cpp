/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "algo/wind.h"
#include "oxapp.h"
#include "algo/wind.h"
#include "conversion.h"
#include <cmath>

void Wind::run_algo() {

  double tas = OxApp::algo_press->get_val( TAS );
  double gs = OxApp::l_gps_fix->get_val(  SPEED );
  double crs = OxApp::l_gps_fix->get_val( TRACK );
  double hd = OxApp::algo_mad_euler->get_val( YAW );

  double sin_hd_crs = sin((hd-crs)/2.0);

  double wind_speed = 0.0;
  double wind_dir = 0.0;
  
  wind_speed = sqrt( (tas-gs)*(tas-gs) +
                           4.0 * tas*gs*( sin_hd_crs * sin_hd_crs ));
  wind_dir = crs + atan2( tas*sin(hd-crs), tas*cos( hd-crs ) - gs ) ;

  if ( wind_dir < 0.0 ) {
    wind_dir = wind_dir + 2.0 * M_PI;
  }
  if ( wind_dir > 2.0 * M_PI ) {
    wind_dir = wind_dir - 2.0 * M_PI;
  }
  OxApp::algo_wind->set_val( WIND_DIR,  wind_dir );
  OxApp::algo_wind->set_val( WIND_SPEED,  wind_speed );
}

