/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __OXAPP_H__
#define __OXAPP_H__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/chrono/system_clocks.hpp>

#include <string>
#include <gps.h>
#include "named_store.h"
#include "ns.h"

static const std::string OX_VERSION="OX 1.01"; 

static const std::string MEM_NAME="OXCART_V1"; 
static const unsigned int MEM_SIZE=64000;

// Dimensional sizes
static const unsigned int L_TEMP_SIZE=3;
static const unsigned int L_ACCEL_SIZE=3;
static const unsigned int L_GYRO_SIZE=3;
static const unsigned int L_MAG_SIZE=3;
static const unsigned int GPS_BUFF_SIZE=1024;
static const unsigned int KEYBOARD_BUFF_SIZE=1024;

static const unsigned int X=0;
static const unsigned int Y=1;
static const unsigned int Z=2;

static const unsigned int V=0;

// ALGO.pressure
static const unsigned int ALGO_PRESS_SIZE=6;
static const unsigned int TE=0;
static const unsigned int AIRSPEED=1;
static const unsigned int TAS=2;
static const unsigned int ALTITUDE=3;
static const unsigned int TE_ALTITUDE=4;
static const unsigned int LOCAL_RHO=5;

// ALGO.press_rate
static const unsigned int ALGO_PRESS_RATE_SIZE=5;
static const unsigned int PRESSURE_TE=0;
static const unsigned int PRESSURE_AIRSPEED=1;
static const unsigned int PRESSURE_TAS=2;
static const unsigned int PRESSURE_ALTITUDE=3;
static const unsigned int PRESSURE_TE_ALTITUDE=4;

//BMP085.pressure
static const unsigned int L_PRESSURE_SIZE=3;
static const unsigned int BMP_TE=0;
static const unsigned int BMP_PITOT=1;
static const unsigned int BMP_STATIC=2;

// ALGO.mad_euler
static const unsigned int ALGO_MAD_EULER_SIZE=4;
static const unsigned int ROLL=0;
static const unsigned int GPS_ROLL=1;
static const unsigned int PITCH=2;
static const unsigned int YAW=3;

// ALGO.mad_quat
static const unsigned int ALGO_MAD_QUAT_SIZE=4;
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
static const unsigned int L_GPS_FIX_SIZE=10;
static const unsigned int LONGITUDE=0;
static const unsigned int LATITUDE=1;
static const unsigned int GPS_ALTITUDE=2;
static const unsigned int SPEED=3;
static const unsigned int VERT_SPEED=4;
static const unsigned int TRACK=5;
static const unsigned int TRACK_CHANGE=6;
static const unsigned int TIME=7;
static const unsigned int MODE=8;
static const unsigned int STATUS=9;

//ALGO.misc_rate
static const unsigned int ALGO_MISC_RATE_SIZE=3;
static const unsigned int GPS_ACCELERATION=0;
static const unsigned int PITCH_RATE=1;
static const unsigned int LOAD_FACTOR=2;

//GPS.NMEA

//manual_double_vals
static const unsigned int MANUAL_DOUBLE_VALS=4;
static const unsigned int MCREADY=0;
static const unsigned int WING_LOADING=1;
static const unsigned int SEA_LEVEL_PRESSURE=2;
static const unsigned int PITCH_ADJUSTMENT=3;

//manual_int_vals
static const unsigned int MANUAL_INT_VALS=3;
static const unsigned int DISP_PAGE_NO=0;
static const unsigned int DISP_CMD=1;
static const unsigned int SYS_CMD=2;


// status
static const unsigned int STATUS_SIZE=11;
static const unsigned int GPS_STAT=0;
static const unsigned int LSM6_STAT=1;
static const unsigned int LIS3MDL_STAT=2;
static const unsigned int KOBO_STAT=3;
static const unsigned int OXCART_D_STAT=4;
static const unsigned int OXALGOS_STAT=5;
static const unsigned int OXCLIENT_STAT=6;
static const unsigned int LED_1=7;
static const unsigned int LED_2=8;
static const unsigned int LED_3=9;
static const unsigned int OUTPUT=10;

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
  static void get_time_str(std::string &s);


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
  static NamedStore<double> *manual_double_vals;
  static NamedStore<uint16_t> *manual_int_vals;

  static NamedStore<char> *GPRMC;
  static NamedStore<char> *GPGGA;
  static NamedStore<char> *KEYBOARD_BUFFER;

  static NamedStore<int8_t> *system_status;

  ~OxApp(){};
  
private:

  static bip::managed_shared_memory * shm;

};

#endif
