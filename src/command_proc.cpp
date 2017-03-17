/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "command_proc.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

void CommandProc::init() {
  buffer = "";
  OxApp::KEYBOARD_BUFFER->set_str(buffer.c_str(),buffer.size());
  CMD=DO_NOTHING;
}
void CommandProc::process_event( struct input_event &ev ) {
  // Key Released
  if ( ev.value == 1 ){
    char c = key_mapper.get_char_from_code( (uint8_t)ev.code );
    BOOST_LOG_TRIVIAL( debug ) << evval[ev.value] << " " <<
      (int)ev.code << " " << c;
    if ( (uint8_t)c == 0 ) {
      uint8_t cmd = key_mapper.get_action_from_code( (uint8_t)ev.code );
      cmd_pressed = cmd;
      switch( cmd ) {
      case  KEY_BACKSPACE:
        // Remove text from bufer
        if ( buffer.size() > 0) {
          buffer.pop_back();
        }
        break;
      case KEY_ESC:
        // Cancel
        BOOST_LOG_TRIVIAL(info) << "KEY_ESC";
        OxApp::system_status->set_val( LED_3,0 );
        buffer = "";
        CMD=DO_NOTHING;
        break;
      case KEY_ENTER:
        BOOST_LOG_TRIVIAL(info) << "KEY_ENTER";
        process_command();
        break;
      default:
        BOOST_LOG_TRIVIAL(info) << "DEFAULT_CMD";
        process_command();
        break;
      } 
    } else {
      /**
       * push text into the buffer
       */
      buffer.push_back(c);
    }
    OxApp::KEYBOARD_BUFFER->set_str(buffer.c_str(),buffer.size()+1);
    BOOST_LOG_TRIVIAL(debug) << OxApp::KEYBOARD_BUFFER->get_str();
  }
}
void CommandProc::process_command() {

  std::string cmd_string( OxApp::KEYBOARD_BUFFER->get_str() );

  /**
   * Figure out the keyed in command mode
   */ 
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "ALT" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "SET_ALT";
    OxApp::system_status->set_val( LED_3,1 );
    CMD=SET_ALT;
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "MAC" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "SET_MAC";
    OxApp::system_status->set_val( LED_3,1 );
    CMD=SET_MAC;
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "PITCH" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "PITCH";
    OxApp::system_status->set_val( LED_3,1 );
    CMD=SET_PITCH;
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "VAR" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "VAR";
    OxApp::system_status->set_val( LED_3,1 );
    CMD=SET_VARIATION;
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "SHUTDOWN" ) == 0 ) {
    OxApp::system_status->set_val( LED_3,1 );
    BOOST_LOG_TRIVIAL(info) << "SHUTDOWN";
    system("sudo systemctl halt");
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "REBOOT" ) == 0 ) {
    OxApp::system_status->set_val( LED_3,1 );
    BOOST_LOG_TRIVIAL(info) << "REBOOT";
    system("sudo systemctl reboot");
  }
  if(cmd_pressed == KEY_ENTER && cmd_string.compare( "OUTPUT" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "OUTPUT";
    if ( OxApp::system_status->get_val( OUTPUT) == 1 ) 
      OxApp::system_status->set_val( OUTPUT,0 );
    else
      OxApp::system_status->set_val( OUTPUT,1 );
  }
   if(cmd_pressed == KEY_ENTER && cmd_string.compare( "CAL" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "CAL";
    system("/home/perryr/oxcart/bin/ox.sh cal");
   }
   if(cmd_pressed == KEY_ENTER && cmd_string.compare( "RESTART" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "RESTART";
    system("/home/perryr/oxcart/bin/ox.sh  restart");
   }

   if(cmd_pressed == KEY_ENTER && cmd_string.compare( "STOP" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "STOP";
    system("/home/perryr/oxcart/bin/ox.sh  stop");
   }
   if(cmd_pressed == KEY_ENTER && cmd_string.compare( "PAGE" ) == 0 ) {
    BOOST_LOG_TRIVIAL(info) << "PAGE";
    OxApp::system_status->set_val( LED_3,1 );
    CMD=PAGE;
  }
  /**
   * Now process page up or arrow actions based on the command.
   */
  if (CMD == SET_ALT ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "SET_ALT + 33.86388 Pa";
      OxApp::manual_double_vals->set_val( SEA_LEVEL_PRESSURE,
              OxApp::manual_double_vals->get_val(SEA_LEVEL_PRESSURE) +
                                          33.86388 );
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "SET_ALT - 33.86388 Pa";
      OxApp::manual_double_vals->set_val( SEA_LEVEL_PRESSURE,
            OxApp::manual_double_vals->get_val(SEA_LEVEL_PRESSURE) -
                                          33.86388 );
      break;
    }
  }
  if (CMD == SET_PITCH ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "SET_PITCH + 1";
      OxApp::manual_double_vals->set_val( PITCH_ADJUSTMENT,
           OxApp::manual_double_vals->get_val(PITCH_ADJUSTMENT) +
                                          1.0 );
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "SET_PITCH - 1";
      OxApp::manual_double_vals->set_val( PITCH_ADJUSTMENT,
            OxApp::manual_double_vals->get_val(PITCH_ADJUSTMENT) -
                                          1.0 );
      break;
    }
  }
  if (CMD == SET_MAC ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "SET_MCREADY + 0.5";
      OxApp::manual_double_vals->set_val( MCREADY,
                    OxApp::manual_double_vals->get_val(MCREADY) +
                                          0.5 );
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "SET_MCREADY - 0.5";
      OxApp::manual_double_vals->set_val( MCREADY,
            OxApp::manual_double_vals->get_val(MCREADY) -
                                          0.5 );
      if ( OxApp::manual_double_vals->get_val(MCREADY) < 0.0 ) {
        OxApp::manual_double_vals->set_val( MCREADY, 0.0 );
      }
      break;
    }
  }
  if (CMD == SET_VARIATION ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "SET_VARATION + 1";
      OxApp::manual_double_vals->set_val( VARIATION,
                    OxApp::manual_double_vals->get_val(VARIATION) +
                                          0.008726646259971648 );
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "SET_VARIATION - 1";
      OxApp::manual_double_vals->set_val( VARIATION,
            OxApp::manual_double_vals->get_val(VARIATION) -
                                          0.008726646259971648 );

      break;
    }
  }
  if (CMD == PAGE ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "PAGE + 1";
      OxApp::manual_int_vals->set_val( DISP_PAGE_NO,
              OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) + 1);
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "PAGE - 1";
            OxApp::manual_int_vals->set_val( DISP_PAGE_NO,
              OxApp::manual_int_vals->get_val( DISP_PAGE_NO ) - 1);

      break;
    }
  }  
}
