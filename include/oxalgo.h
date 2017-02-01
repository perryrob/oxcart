#ifndef __OX_ALGO_H__
#define __OX_ALGO_H__

#include <string>

class OxAlgo {

public:

 OxAlgo( const std::string &name, const uint64_t interval) : name(name),
    interval(interval), last_run(0) {}

  inline std::string const & get_name() { return name; }

  bool run_it();
  
  virtual void run_algo() = 0;

  
protected:

  OxAlgo() {}
  virtual ~OxAlgo(){}

private:
  const std::string name;
  uint64_t interval; // in milliseconds
  uint64_t last_run;
};

#endif
