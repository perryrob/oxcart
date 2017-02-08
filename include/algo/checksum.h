#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__

#include <boost/algorithm/string.hpp>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

class Checksum {

 public:
  Checksum(std::string &msg) : _msg(msg) {};

  inline std::string &get_sentance() {

    uint8_t crc=0;
    for(unsigned int i=0;i<_msg.length();i++)
      crc^=(uint8_t)_msg.c_str()[i];
    _msg.insert(0,"$");
    std::stringstream sum;
    sum  << "*" << std::hex << unsigned(crc) << "\r\n";
    std::string suffix( sum.str() );
    boost::to_upper(suffix);
    _msg.append(suffix);
    return _msg;
  }
  
  ~Checksum(){}

private:
  std::string _msg;

};


#endif

