#ifndef __oxapp_h__
#define __oxapp_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>
#include <gps.h>
#include "named_store.h"
#include "ns.h"

static const std::string MEM_NAME="OXCART_V1"; 
static const unsigned int MEM_SIZE=64000;

typedef b::posix_time::ptime Time;
typedef b::posix_time::time_duration TimeDuration;

struct local_raw_sensor_t {

  int32_t c1_pressure,c2_pressure,c3_pressure; //BMP085
  float c1_temp,c2_temp,c3_temp; //BMP085
  int16_t accel_x,accel_y,accel_z; //LSM6
  int16_t gyro_x,gyro_y,gyro_z; //LSM6
  int16_t mag_x,mag_y,mag_z; //LIS3MDL  

  /**
     GPS Stuff
     timestamp_t time;	 Time of update 
  int    mode;	 Mode of fix 
  MODE_NOT_SEEN	0	 mode update not seen yet 
  MODE_NO_FIX	1	 none 
  MODE_2D  	2	 good for latitude/longitude 
  MODE_3D  	3	 good for altitude/climb too 
    double ept;		 Expected time uncertainty 
    double latitude;	 Latitude in degrees (valid if mode >= 2) 
    double epy;  	 Latitude position uncertainty, meters 
    double longitude;	 Longitude in degrees (valid if mode >= 2) 
    double epx;  	 Longitude position uncertainty, meters 
    double altitude;	 Altitude in meters (valid if mode == 3) 
    double epv;  	 Vertical position uncertainty, meters 
    double track;	 Course made good (relative to true north) 
    double epd;		 Track uncertainty, degrees 
    double speed;	 Speed over ground, meters/sec 
    double eps;		 Speed uncertainty, meters/sec 
    double climb;        Vertical speed, meters/sec 
    double epc;		 Vertical speed uncertainty 
  **/

  gps_fix_t fix;

};

typedef struct local_raw_sensor_t local_raw_sensor_t;

struct remote_raw_sensor_t {

  int16_t accel_x,accel_y,accel_z;
  int16_t gyro_x,gyro_y,gyro_z; 
  int16_t mag_x,mag_y,mag_z;

};


class OxApp  {

public:

  OxApp(){};

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

  static NamedStore<int32_t> *l_pressure;
  static NamedStore<float> *l_temp;
  static NamedStore<float> *l_alt;
  static NamedStore<int16_t> *l_accel;
  static NamedStore<int16_t> *l_gyro;
  static NamedStore<int16_t> *l_mag;
  
  static NamedStore<double> *l_gps_fix;
  static NamedStore<uint64_t> *l_gps_time;
  static NamedStore<int> *l_gps_mode;
  
  ~OxApp(){};
  
private:
  
  static bip::managed_shared_memory * shm;

};

#endif
