#include "oxapp.h"
#include "devices/ARDUINO_DISP.h"
#include "devices/TCA9548A.h"
#include <math.h>
#include <string>
#include <vector>
#include <ctime>
#include "trivial_log.h"

ARDUINO_DISP::ARDUINO_DISP()  : OxI2CDevice( "ARDUINO_DISP"), init(true) {}

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
  }

  render_page();
  
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
  case 2:
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
  case 3:
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
    display_text[index] = msg;
    display_size[index] = size;
  } else {
    std::string old_msg = display_text[index];
    uint8_t old_size =  display_size[index];
    Wire->beginTransmission(ARDUINO_I2CADDR);
    Wire->write( TXT_CMD );
    Wire->write( x );
    Wire->write( y );
    Wire->write( old_size );
    Wire->write( 0x01 );
    std::vector<uint8_t> vec(old_msg.begin(), old_msg.end());
    uint8_t *p = &vec[0];
    Wire->write( p, vec.size() );
    Wire->endTransmission();
  }
  Wire->beginTransmission(ARDUINO_I2CADDR);
  Wire->write( TXT_CMD );
  Wire->write( x );
  Wire->write( y );
  Wire->write( size );
  Wire->write( 0x00 );
  std::vector<uint8_t> vec(msg.begin(), msg.end());
  uint8_t *p = &vec[0];
  Wire->write( p, vec.size() );
  Wire->endTransmission();

}

void ARDUINO_DISP::render_page() {

  if((OxApp::get_time_ms() - OxApp::l_gps_fix->get_time(TIME)) > 5000) {
    led_on( 1, true ); 
  } else {
    led_on( 1, false ); 
  }

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

  switch( OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) ) {

  case 0:
    write_string( 30, 0, 1, OX_VERSION );
    std::string tmp_str;
    OxApp::get_time_str( tmp_str );
    write_string( 0, 10, 1, tmp_str );
    break;
    
  }

}
