#ifndef __oxapp_h__
#define __oxapp_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/chrono/system_clocks.hpp>

#include <string>
#include <gps.h>
#include "named_store.h"
#include "ns.h"

static const std::string OX_VERSION="OX 1.0"; 

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

  static uint64_t get_time_ms();

  static NamedStore<int32_t> *l_pressure;
  static NamedStore<float> *l_temp;
  static NamedStore<float> *l_alt;
  static NamedStore<double> *l_accel;
  static NamedStore<double> *l_gyro;
  static NamedStore<double> *l_mag;
  
  static NamedStore<double> *l_gps_fix;

  static NamedStore<double> *algo_mad_euler;
  static NamedStore<double> *algo_mad_quat;
  static NamedStore<double> *algo_press;
  static NamedStore<double> *algo_press_rate;

  static NamedStore<double> *algo_misc_rate;

  static NamedStore<char> *GPRMC;
  static NamedStore<char> *GPGGA;


  ~OxApp(){};
  
private:
  
  static bip::managed_shared_memory * shm;

};

#endif
