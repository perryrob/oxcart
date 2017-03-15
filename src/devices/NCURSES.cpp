/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "devices/NCURSES.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <ncurses.h>
#include "conversion.h"
#include <math.h>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "trivial_log.h"

NCURSES_DISP::NCURSES_DISP() : init(true),
                               last_update(0) {
  initscr();

}

void NCURSES_DISP::rw_device() {
  if( OxApp::get_time_ms() - last_update > 200 ) {
    render_page();
    last_update = OxApp::get_time_ms();
  } else {
    return;
  }
  refresh();
}
void NCURSES_DISP::led_on( uint8_t LED, bool on ) {
}
void NCURSES_DISP::write_string( uint8_t x, uint8_t y, 
                                 uint8_t size, const std::string &msg) {
  mvprintw( y/10 , x/2 , msg.c_str());
}

void NCURSES_DISP::render_page() {
  
  led_on( 1, (bool)OxApp::system_status->get_val( LED_1 ) );
  led_on( 2, (bool)OxApp::system_status->get_val( LED_2 ) );
  led_on( 3, (bool)OxApp::system_status->get_val( LED_3 ) );  

  clear();


  switch( OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) ) {

  case 0:
    write_string( 30, 0, 1, OX_VERSION );
    // Display the date and time
    std::string tmp_str;
    OxApp::get_time_str( tmp_str );
    write_string( 0, 10, 1, tmp_str );
    std::stringstream ss;
    // Show GPS mode
    if(OxApp::l_gps_fix->get_val(STATUS)==0)
      ss << "GPS: NO FIX";
    if(OxApp::l_gps_fix->get_val(STATUS)==1)
      ss << "GPS: FIX";
    if(OxApp::l_gps_fix->get_val(STATUS)==2)
      ss << "GPS: DGPS";
    write_string( 0, 20, 1, ss.str() );
    ss.str(std::string()); // clear
    ss.precision(0);
    // Show Pressure Alt
    ss << "Alt: " << std::fixed <<
      Conv::feet(static_cast<double>(OxApp::algo_press->get_val(PRESSURE_ALTITUDE))) ;
    write_string( 0, 30, 1, ss.str() );
    ss.str(std::string()); // clear
    ss.precision(2);
    // Show Kolsman pressure
    ss << "Pres: " << std::fixed <<
      Conv::inches_merc(
          static_cast<double>(OxApp::manual_double_vals->get_val(
                                   SEA_LEVEL_PRESSURE)
                              )
                        );
    write_string( 0, 40, 1, ss.str() );

    ss.str(std::string()); // clear
    ss.precision(1);
    // Show TAS
    ss << "TAS: " << std::fixed <<
      Conv::knots(OxApp::algo_press->get_val(AIRSPEED));
    write_string( 0, 50, 1, ss.str() );
    
    ss.str(std::string()); // clear
    ss.precision(2);
    ss << "RPY: " << std::fixed << OxApp::algo_mad_euler->get_val(ROLL) <<
      "," <<
      std::fixed << OxApp::algo_mad_euler->get_val(PITCH) <<
      "," <<
      std::fixed << OxApp::algo_mad_euler->get_val(YAW);
    write_string( 0, 60, 1, ss.str() );
    ss.str(std::string()); // clear
    ss.precision(1);
    ss << "G: " << std::fixed << OxApp::algo_misc_rate->get_val(LOAD_FACTOR);
    
    if ( OxApp::system_status->get_val( OUTPUT) ) {
      ss << " data:ON";
    } else {
      ss << " data:OFF";
    }
    
    write_string( 0, 70, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "> " <<  OxApp::KEYBOARD_BUFFER->get_str();
    write_string( 0, 80, 1, ss.str() );

    ss.str(std::string()); // clear
    ss << "led1: " <<  (bool)OxApp::system_status->get_val( LED_1 ) <<
      " led2: " <<  (bool)OxApp::system_status->get_val( LED_2 ) <<
      " led3: " <<  (bool)OxApp::system_status->get_val( LED_3 );
    write_string( 0, 90, 1, ss.str() );

    ss.str(std::string()); // clear
    ss.precision(1);
    ss <<   std::fixed << OxApp::l_mag->get_val(X) << " " <<
      std::fixed << OxApp::l_mag->get_val(Y) << " " <<
      std::fixed << OxApp::l_mag->get_val(Z) ;
    
    write_string( 0, 100, 1, ss.str() );


    break;    
  }

}

NCURSES_DISP::~NCURSES_DISP() {
  endwin();
}
