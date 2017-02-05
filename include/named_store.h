#ifndef __named_store_h__
#define __named_store_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <string.h>
#include "ns.h"

/****************************************
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

  static NamedStore<double> *algo_gps_rate;
  
*/

// LSM6.accel LSM6.gyro LIS3MDL.mag
static const unsigned int X=0;
static const unsigned int Y=1;
static const unsigned int Z=2;

static const unsigned int V=0;

// ALGO.pressure
static const unsigned int TE=0;
static const unsigned int AIRSPEED=1;
static const unsigned int TAS=2;
static const unsigned int ALTITUDE=3;
static const unsigned int TE_ALTITUDE=4;

// ALGO.press_rate
static const unsigned int PRESSURE_TE=0;
static const unsigned int PRESSURE_AIRSPEED=1;
static const unsigned int PRESSURE_TAS=2;
static const unsigned int PRESSURE_ALTITUDE=3;
static const unsigned int PRESSURE_TE_ALTITUDE=4;

//BMP085.pressure
static const unsigned int BMP_TE=0;
static const unsigned int BMP_PITOT=1;
static const unsigned int BMP_STATIC=2;

// ALGO.mad_euler
static const unsigned int ROLL=0;
static const unsigned int GPS_ROLL=1;
static const unsigned int PITCH=2;
static const unsigned int YAW=3;

// ALGO.mad_quat
static const unsigned int A=0;
static const unsigned int B=1;
static const unsigned int C=2;
static const unsigned int D=3;

// Multiplexer
static const unsigned int CH1=0;
static const unsigned int CH2=1;
static const unsigned int CH3=2;
static const unsigned int CH4=3;
static const unsigned int CH5=4;
static const unsigned int CH6=5;
static const unsigned int CH7=6;
static const unsigned int CH8=7;

//GPS.fix
static const unsigned int LONGITUDE=0;
static const unsigned int LATITUDE=1;
static const unsigned int GPS_ALTITUDE=2;
static const unsigned int SPEED=3;
static const unsigned int VERT_SPEED=4;
static const unsigned int TRACK=5;
static const unsigned int TRACK_CHANGE=6;
static const unsigned int TIME=7;
static const unsigned int MODE=8;

//ALGO.misc_rate
static const unsigned int GPS_ACCELERATION=0;
static const unsigned int PITCH_RATE=1;


template <class STORE_T> class NamedStore {

public:
  NamedStore();

  NamedStore( const unsigned int &dimension );


  NamedStore( char const * name,
              bip::managed_shared_memory *shm,
              const unsigned int &dimension );

  NamedStore(const NamedStore& rhs);

  ~NamedStore();

  void set_val( unsigned int index, STORE_T val );
  STORE_T get_val( unsigned int index );
  uint64_t get_time( unsigned int index );
                
private:
  
  STORE_T *vals;
  uint64_t *times; //milliseconds
  unsigned int dimension;
  std::string name;
  bip::managed_shared_memory * shm;
  bool is_shared_mem;

};

#endif
