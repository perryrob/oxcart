/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/
#include "oxapp.h"
#include "algo/polar.h"
#include "devices/ARDUINO_DISP.h"
#include "devices/TCA9548A.h"
#include "conversion.h"
#include <math.h>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "trivial_log.h"

ARDUINO_DISP::ARDUINO_DISP()  : OxI2CDevice( "ARDUINO_DISP"), init(true),
                                last_update(0) {}

void ARDUINO_DISP::rw_device() {
  BOOST_LOG_TRIVIAL(debug) << "start rw_device()";
  if (init) {
    for(uint8_t led=1; led <= 3; ++led) {
      led_on( led, true ); 
      led_on( led, false ); 
    }
    Wire->beginTransmission(ARDUINO_I2CADDR);
    Wire->write(CLEAR_CMD);  
    Wire->endTransmission();
    init=false;
    last_update = OxApp::get_time_ms();
    render_page();
  }
  if( OxApp::get_time_ms() - last_update > 200 ) {
    render_page();
    last_update = OxApp::get_time_ms();
  } else {
    return;
  }
  
  /***
   * This is needed to pad the I2C writes
   */
  Wire->beginTransmission(ARDUINO_I2CADDR);
  Wire->write(0x0);  
  Wire->endTransmission();
  BOOST_LOG_TRIVIAL(debug) << "end rw_device()";
}
void ARDUINO_DISP::led_on( uint8_t LED, bool on ) {

  switch( LED ) {
  case 1:
    if( on ) {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_1_ON);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_1_on";
    } else {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_1_OFF);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_1_off";

    }
    break;
  case 3: // BUG Lower light compensate for arduino mis-code.
    if( on ) {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_2_ON);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_2_on";
    } else {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_2_OFF);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_2_off";
    }
    break;
  case 2: // BUG Lower light compensate for arduino mis-code.
    if( on ) {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_3_ON);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_3_on";
    } else {
      Wire->beginTransmission(ARDUINO_I2CADDR);
      Wire->write(LED_3_OFF);
      Wire->endTransmission();
      BOOST_LOG_TRIVIAL(debug) << "LED_3_off";
    }
    break;    
  }
}
void ARDUINO_DISP::write_string( uint8_t x, uint8_t y, 
                                 uint8_t size, const std::string &msg) {
  uint16_t index = ((uint16_t)x << 8) | y;

  auto search = display_text.find( index );

  if( search != display_text.end() ) {
    std::string old_msg = display_text[index];
    uint8_t old_size =  display_size[index];
    Wire->beginTransmission(ARDUINO_I2CADDR);
    Wire->write( TXT_CMD );
    Wire->write( x );
    Wire->write( y );
    Wire->write( old_size );
    Wire->write( 1 );
    std::vector<uint8_t> vec(old_msg.begin(), old_msg.end());
    uint8_t *p = &vec[0];
    Wire->write( p, vec.size() );
    Wire->endTransmission();
  }

  display_text[index] = msg;
  display_size[index] = size;

  Wire->beginTransmission(ARDUINO_I2CADDR);
  Wire->write( TXT_CMD );
  Wire->write( x );
  Wire->write( y );
  Wire->write( size );
  Wire->write( 0 );
  std::vector<uint8_t> vec(msg.begin(), msg.end());
  uint8_t *p = &vec[0];
  Wire->write( p, vec.size() );
  Wire->endTransmission();

  Wire->beginTransmission(ARDUINO_I2CADDR);
  Wire->write(0x0);  
  Wire->endTransmission();
}

void ARDUINO_DISP::render_page() {

  led_on( 1, (bool)OxApp::system_status->get_val( LED_1 ) );
  led_on( 2, (bool)OxApp::system_status->get_val( LED_2 ) );
  led_on( 3, (bool)OxApp::system_status->get_val( LED_3 ) );  

  if ( OxApp::manual_int_vals->get_val( DISP_CMD ) != 0 ) {

    if (OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) < 0)
      OxApp::manual_int_vals->set_val( DISP_PAGE_NO, 0 );

    if (OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) > MAX_PAGES)
      OxApp::manual_int_vals->set_val( DISP_PAGE_NO, 0 );

    Wire->beginTransmission(ARDUINO_I2CADDR);
    Wire->write(CLEAR_CMD);  
    Wire->endTransmission();

    OxApp::manual_int_vals->set_val( DISP_CMD,0 );
  }

  if ( OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) > MAX_PAGES - 1 ) {
    OxApp::manual_int_vals->set_val( DISP_PAGE_NO, 0 );
  }
  if ( OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) < 0 ) {
    OxApp::manual_int_vals->set_val( DISP_PAGE_NO, MAX_PAGES - 1);
  }

  Polar polar;
  
  std::string tmp_str;
  std::stringstream ss;

  switch( OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) ) {

  case 0:
    write_string( 20, 0, 1, OX_VERSION + " p1");
    // Display the date and time
    OxApp::get_time_str( tmp_str );
    write_string( 0, 10, 1, tmp_str );
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
                        ) << " " << std::setprecision(0) <<
    Conv::rad2deg(static_cast<double>(OxApp::manual_double_vals->get_val(VARIATION)));
    write_string( 0, 40, 1, ss.str() );

    ss.str(std::string()); // clear
    ss.precision(1);
    // Show TAS
    ss << "TAS: " << std::fixed <<
      Conv::knots(OxApp::algo_press->get_val(AIRSPEED));
    write_string( 0, 50, 1, ss.str() );
    
    ss.str(std::string()); // clear
    ss.precision(0);
    ss << "RPY: " << std::fixed <<
      Conv::rad2deg(OxApp::algo_mad_euler->get_val(ROLL)) <<
      "," <<
      std::fixed <<
      Conv::rad2deg(OxApp::algo_mad_euler->get_val(PITCH)) <<
      "," <<
      std::fixed <<
      Conv::rad2deg(OxApp::algo_mad_euler->get_val(YAW));
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
    break;

  case 1:
    write_string( 20, 0, 1, OX_VERSION + " p2");
    // Display the date and time
    OxApp::get_time_str( tmp_str );
    write_string( 0, 10, 1, tmp_str );
    ss.str(std::string()); // clear
    ss.precision(0);
    ss << "TE: " <<  std::fixed <<
      Conv::feet(OxApp::algo_press->get_val(TE_ALTITUDE)) << " f";
    write_string( 0, 20, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "AL: " <<  std::fixed <<
      Conv::feet(OxApp::algo_press->get_val(ALTITUDE)) << " f";
    write_string( 0, 30, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "SP: " <<  std::fixed <<
      Conv::knots(OxApp::algo_press->get_val(AIRSPEED)) << " k";
    write_string( 0, 40, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "TAS: " <<  std::fixed <<
      Conv::knots(OxApp::algo_press->get_val(TAS)) << " k";
    write_string( 0, 50, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "GS: " <<   std::fixed <<
      Conv::knots(OxApp::l_gps_fix->get_val(SPEED)) << " k";
    write_string( 0, 60, 1, ss.str() );
    ss.str(std::string()); // clear
    if ( OxApp::algo_press->get_val(AIRSPEED) > 20.0 ) {
      ss << "LD: " <<  std::fixed <<
        fabs(OxApp::algo_press->get_val(AIRSPEED)  /
             polar.sink_rate(OxApp::algo_press->get_val(AIRSPEED))) ;
    } else {
      ss << "LD: " <<  "~";
    }
    write_string( 0, 70, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "> " <<  OxApp::KEYBOARD_BUFFER->get_str();
    write_string( 0, 80, 1, ss.str() );
    break;

  case 2:
    write_string( 20, 0, 1, OX_VERSION + " p3");
    ss.str(std::string());
    ss << "    ";
    write_string( 0, 10, 1, ss.str() );
    ss.str(std::string());
    ss << "ALT, MAC, PITCH";
    write_string( 0, 20, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "VAR, SHUTDOWN";
    write_string( 0, 30, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "SHUTDOWN";
    write_string( 0, 40, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "OUTPUT, CAL";
    write_string( 0, 50, 1, ss.str() );    
    ss.str(std::string()); // clear
    ss << "RESTART";
    write_string( 0, 60, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "STOP, PAGE";
    write_string( 0, 70, 1, ss.str() );
    ss.str(std::string()); // clear
    ss << "> " <<  OxApp::KEYBOARD_BUFFER->get_str();
    write_string( 0, 80, 1, ss.str() );
    break;    
  }

}
