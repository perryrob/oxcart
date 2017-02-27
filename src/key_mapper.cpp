
#include "key_mapper.h"
#include "trivial_log.h"

char KeyMapper::get_char_from_code( uint8_t code ) {
switch(code) {
 case KEY_1:
    BOOST_LOG_TRIVIAL(debug) << "KEY_1";
    return '1';
 case KEY_2:
    BOOST_LOG_TRIVIAL(debug) << "KEY_2";
    return '2';
 case KEY_3:
    BOOST_LOG_TRIVIAL(debug) << "KEY_3";
    return '3';
 case KEY_4:
    BOOST_LOG_TRIVIAL(debug) << "KEY_4";
    return '4';
 case KEY_5:
    BOOST_LOG_TRIVIAL(debug) << "KEY_5";
    return '5';
 case KEY_6:
    BOOST_LOG_TRIVIAL(debug) << "KEY_6";
    return '6';
 case KEY_7:
    BOOST_LOG_TRIVIAL(debug) << "KEY_7";
    return '7';
 case KEY_8:
    BOOST_LOG_TRIVIAL(debug) << "KEY_8";
    return '8';
 case KEY_9:
    BOOST_LOG_TRIVIAL(debug) << "KEY_9";
    return '9';
 case KEY_0:
    BOOST_LOG_TRIVIAL(debug) << "KEY_0";
    return '0';
 case KEY_MINUS:
    BOOST_LOG_TRIVIAL(debug) << "KEY_MINUS";
    return '-';
 case KEY_EQUAL:
    BOOST_LOG_TRIVIAL(debug) << "KEY_EQUAL";
    return '=';
 case KEY_Q:
    BOOST_LOG_TRIVIAL(debug) << "KEY_Q";
    return 'Q';
 case KEY_W:
    BOOST_LOG_TRIVIAL(debug) << "KEY_W";
    return 'W';
 case KEY_E:
    BOOST_LOG_TRIVIAL(debug) << "KEY_E";
    return 'E';
 case KEY_R:
    BOOST_LOG_TRIVIAL(debug) << "KEY_R";
    return 'R';
 case KEY_T:
    BOOST_LOG_TRIVIAL(debug) << "KEY_T";
    return 'T';
 case KEY_Y:
    BOOST_LOG_TRIVIAL(debug) << "KEY_Y";
    return 'Y';
 case KEY_U:
    BOOST_LOG_TRIVIAL(debug) << "KEY_U";
    return 'U';
 case KEY_I:
    BOOST_LOG_TRIVIAL(debug) << "KEY_I";
    return 'I';
 case KEY_O:
    BOOST_LOG_TRIVIAL(debug) << "KEY_O";
    return 'O';
 case KEY_P:
    BOOST_LOG_TRIVIAL(debug) << "KEY_P";
    return 'P';
 case KEY_LEFTBRACE:
    BOOST_LOG_TRIVIAL(debug) << "KEY_LEFTBRACE";
    return '[';
 case KEY_RIGHTBRACE:
    BOOST_LOG_TRIVIAL(debug) << "KEY_RIGHTBRACE";
    return ']';
 case KEY_A:
    BOOST_LOG_TRIVIAL(debug) << "KEY_A";
    return 'A';
 case KEY_S:
    BOOST_LOG_TRIVIAL(debug) << "KEY_S";
    return 'S';
 case KEY_D:
    BOOST_LOG_TRIVIAL(debug) << "KEY_D";
    return 'D';
 case KEY_F:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F";
    return 'F';
 case KEY_G:
    BOOST_LOG_TRIVIAL(debug) << "KEY_G";
    return 'G';
 case KEY_H:
    BOOST_LOG_TRIVIAL(debug) << "KEY_H";
    return 'H';
 case KEY_J:
    BOOST_LOG_TRIVIAL(debug) << "KEY_J";
    return 'J';
 case KEY_K:
    BOOST_LOG_TRIVIAL(debug) << "KEY_K";
    return 'K';
 case KEY_L:
    BOOST_LOG_TRIVIAL(debug) << "KEY_L";
    return 'L';
 case KEY_SEMICOLON:
    BOOST_LOG_TRIVIAL(debug) << "KEY_SEMICOLON";
    return ';';
 case KEY_APOSTROPHE:
    BOOST_LOG_TRIVIAL(debug) << "KEY_APOSTROPHE";
    return '\'';
 case KEY_BACKSLASH:
    BOOST_LOG_TRIVIAL(debug) << "KEY_BACKSLASH";
    return '\\';
 case KEY_Z:
    BOOST_LOG_TRIVIAL(debug) << "KEY_Z";
    return 'Z';
 case KEY_X:
    BOOST_LOG_TRIVIAL(debug) << "KEY_X";
    return 'X';
 case KEY_C:
    BOOST_LOG_TRIVIAL(debug) << "KEY_C";
    return 'C';
 case KEY_V:
    BOOST_LOG_TRIVIAL(debug) << "KEY_V";
    return 'V';
 case KEY_B:
    BOOST_LOG_TRIVIAL(debug) << "KEY_B";
    return 'B';
 case KEY_N:
    BOOST_LOG_TRIVIAL(debug) << "KEY_N";
    return 'N';
 case KEY_M:
    BOOST_LOG_TRIVIAL(debug) << "KEY_M";
    return 'M';
 case KEY_COMMA:
    BOOST_LOG_TRIVIAL(debug) << "KEY_COMMA";
    return ',';
 case KEY_DOT:
    BOOST_LOG_TRIVIAL(debug) << "KEY_DOT";
    return '.';
 case KEY_SLASH:
    BOOST_LOG_TRIVIAL(debug) << "KEY_SLASH";
    return '/';
 case KEY_SPACE:
    BOOST_LOG_TRIVIAL(debug) << "KEY_SPACE";
    return ' ';
  }
  return 0;
}
uint8_t KeyMapper::get_action_from_code( uint8_t code ) {

  switch(code) {
 case KEY_ESC:
    BOOST_LOG_TRIVIAL(debug) << "KEY_ESC";
    return code;
    break;
 case KEY_ENTER:
    BOOST_LOG_TRIVIAL(debug) << "KEY_ENTER";
    return code;
    break;
 case KEY_BACKSPACE:
    BOOST_LOG_TRIVIAL(debug) << "KEY_BACKSPACE";
    return code;
    break;
  case KEY_F1:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F1";
    return code;
    break;
 case KEY_F2:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F2";
    return code;
    break;
 case KEY_F3:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F3";
    return code;
    break;
 case KEY_F4:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F4";
    return code;
    break;
 case KEY_F5:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F5";
    return code;
    break;
 case KEY_F6:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F6";
    return code;
    break;
 case KEY_F7:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F7";
    return code;
    break;
 case KEY_F8:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F8";
    return code;
    break;
 case KEY_F9:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F9";
    return code;
    break;
 case KEY_F10:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F10";
    return code;
    break;
 case KEY_F11:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F11";
    return code;
    break;
 case KEY_F12:
    BOOST_LOG_TRIVIAL(debug) << "KEY_F12";
    return code;
    break;
 case KEY_NUMLOCK:
    BOOST_LOG_TRIVIAL(debug) << "KEY_NUMLOCK";
    return code;
    break;
  case KEY_HOME:
        BOOST_LOG_TRIVIAL(debug) << "KEY_HOME";
        return code;
        break;
  case KEY_UP:
        BOOST_LOG_TRIVIAL(debug) << "KEY_UP";
        return code;
        break;
  case KEY_PAGEUP:
        BOOST_LOG_TRIVIAL(debug) << "KEY_PAGEUP";
        return code;
        break;
  case KEY_LEFT:
        BOOST_LOG_TRIVIAL(debug) << "KEY_LEFT";
        return code;
        break;
  case KEY_RIGHT:
        BOOST_LOG_TRIVIAL(debug) << "KEY_RIGHT";
        return code;
        break;
  case KEY_END:
        BOOST_LOG_TRIVIAL(debug) << "KEY_END";
        return code;
        break;
  case KEY_DOWN:
        BOOST_LOG_TRIVIAL(debug) << "KEY_DOWN";
        return code;
        break;
  case KEY_PAGEDOWN:
        BOOST_LOG_TRIVIAL(debug) << "KEY_PAGEDOWN";
        return code;
        break;
  case KEY_INSERT:
        BOOST_LOG_TRIVIAL(debug) << "KEY_INSERT";
        return code;
        break;
  case KEY_DELETE:
        BOOST_LOG_TRIVIAL(debug) << "KEY_DELETE";
        return code;
        break;
  case KEY_MUTE:
        BOOST_LOG_TRIVIAL(debug) << "KEY_MUTE";
        return code;
        break;
  case KEY_VOLUMEDOWN:
        BOOST_LOG_TRIVIAL(debug) << "KEY_VOLUMEDOWN";
        return code;
        break;
  case KEY_VOLUMEUP:
        BOOST_LOG_TRIVIAL(debug) << "KEY_VOLUMEUP";
        return code;
        break;
  case KEY_POWER:
        BOOST_LOG_TRIVIAL(debug) << "KEY_POWER";
        return code;
        break;
  case KEY_PAUSE:
        BOOST_LOG_TRIVIAL(debug) << "KEY_PAUSE";
        return code;
        break;
  case KEY_STOP:
        BOOST_LOG_TRIVIAL(debug) << "KEY_STOP";
        return code;
        break;
  }
  return 0;
}
