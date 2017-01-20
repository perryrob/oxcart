#ifndef __oxapp_h__
#define __oxapp_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/chrono/system_clocks.hpp>

#include <string>
#include <gps.h>
#include "named_store.h"
#include "ns.h"

static const std::string MEM_NAME="OXCART_V1"; 
static const unsigned int MEM_SIZE=64000;

typedef b::posix_time::ptime Time;
typedef b::posix_time::time_duration TimeDuration;

class OxApp  {

public:

  OxApp(){};

  static bip::managed_shared_memory * create();
  static void destroy();
   
  static inline bip::managed_shared_memory * get_shared_mem() {
    return shm;
  }

  static inline uint64_t get_time_ms() {
     // Timestamp the data in milliseconds
    b::chrono::system_clock::time_point now = b::chrono::system_clock::now();
    b::chrono::nanoseconds sec =  now.time_since_epoch();
    b::chrono::milliseconds milliSecs = b::chrono::duration_cast<b::chrono::milliseconds>(sec);
    return (uint64_t)milliSecs.count();
  }

  static NamedStore<int32_t> *l_pressure;
  static NamedStore<float> *l_temp;
  static NamedStore<float> *l_alt;
  static NamedStore<int16_t> *l_accel;
  static NamedStore<int16_t> *l_gyro;
  static NamedStore<int16_t> *l_mag;
  
  static NamedStore<double> *l_gps_fix;
  
  ~OxApp(){};
  
private:
  
  static bip::managed_shared_memory * shm;

};

#endif
