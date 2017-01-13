#ifndef __oxapp_h__
#define __oxapp_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>

#include "named_store.h"
#include "ns.h"

static const std::string MEM_NAME="OXCART_V1"; 
static const unsigned int MEM_SIZE=64000;

typedef b::posix_time::ptime Time;
typedef b::posix_time::time_duration TimeDuration;

struct raw_sensor_t {

  int32_t c1_pressure,c2_pressure,c3_pressure;
  float c1_temp,c2_temp,c3_temp;
  int16_t accel_x,accel_y,accel_z;
  int16_t gyro_x,gyro_y,gyro_z;

};


class OxApp  {

public:

  OxApp(){}

  static bip::managed_shared_memory * create();
  static void destroy();
   
  static inline bip::managed_shared_memory * get_shared_mem() {
    return shm;
  }

  static inline long get_time_ms() {
    Time t(boost::posix_time::microsec_clock::local_time());
    TimeDuration dt( t.time_of_day() );
    return dt.total_milliseconds();
  }

  ~OxApp(){};
  
private:
  
  static bip::managed_shared_memory * shm;

};

#endif
