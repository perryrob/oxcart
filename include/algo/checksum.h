#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__

#include <boost/algorithm/string.hpp>
#include <sstream>
#include <string>
#include <sstream>
#include <cstring>
#include <utility>

class Checksum {

 public:
 Checksum(std::string &msg) : _msg(std::move(msg)) {}
 Checksum(std::stringstream &msg) : _msg(std::move(msg.str())){}

  uint8_t cksum();
  std::string& get_sentence();
  
  ~Checksum(){}

private:
  std::string _msg;

};


#endif

