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

  if ( ev.value == 1 ) {
    printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
  }
  // Key Released
  if ( ev.value == 1 ){
    char c = key_mapper.get_char_from_code( (uint8_t)ev.code );
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

  /**
   * Now process page up or arrow actions based on the command.
   */
  if (CMD == SET_ALT ) {
    switch (cmd_pressed) {
    case KEY_UP:
      BOOST_LOG_TRIVIAL(info) << "SET_ALT + 170 Pa";
      OxApp::manual_double_vals->set_val( SEA_LEVEL_PRESSURE,
              OxApp::manual_double_vals->get_val(SEA_LEVEL_PRESSURE) +
                                          170.0 );
      break;
    case KEY_DOWN:
      BOOST_LOG_TRIVIAL(info) << "SET_ALT - 170 Pa";
      OxApp::manual_double_vals->set_val( SEA_LEVEL_PRESSURE,
            OxApp::manual_double_vals->get_val(SEA_LEVEL_PRESSURE) -
                                          170.0 );
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
}
