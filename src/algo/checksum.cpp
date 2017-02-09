
#include "algo/checksum.h"

uint8_t Checksum::cksum() {
  uint8_t crc=0;
  for(unsigned int i=0;i<_msg.length();i++)
    crc^=(uint8_t)_msg.c_str()[i];
  return crc;
  }

std::string& Checksum::get_sentence() {
  if ( _msg[0] == '$' ) return _msg;
  std::stringstream sum;
  uint8_t csum = cksum();
  if (csum < 16) {
    sum  << "*0" << std::hex << unsigned(csum);
  } else {
    sum  << "*" << std::hex << unsigned(csum);
  }
  std::string suffix( sum.str() );
  boost::to_upper(suffix);
  _msg.append(suffix);
  _msg.append("\r\n");
  _msg.insert(0,"$");
  return _msg;
}
