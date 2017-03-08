/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <boost/interprocess/managed_shared_memory.hpp>

bip::managed_shared_memory * OxApp::shm = 0;

NamedStore<int32_t> * OxApp::l_pressure = new NamedStore<int32_t>(
                                                         L_PRESSURE_SIZE);
NamedStore<float> * OxApp::l_temp = new NamedStore<float>(L_TEMP_SIZE);
NamedStore<double> * OxApp::l_accel = new NamedStore<double>(L_ACCEL_SIZE);
NamedStore<double> * OxApp::l_gyro = new NamedStore<double>(L_GYRO_SIZE);
NamedStore<double> * OxApp::l_mag = new NamedStore<double>(L_MAG_SIZE);

NamedStore<double> * OxApp::l_gps_fix = new NamedStore<double>(L_GPS_FIX_SIZE);

NamedStore<double> * OxApp::algo_mad_euler = new NamedStore<double>(
                                                           ALGO_MAD_EULER_SIZE);
NamedStore<double> * OxApp::algo_mad_quat = new NamedStore<double>(
                                                           ALGO_MAD_QUAT_SIZE);
NamedStore<double> * OxApp::algo_press = new NamedStore<double>(ALGO_PRESS_SIZE);
NamedStore<double> * OxApp::algo_press_rate = new NamedStore<double>(
                                                          ALGO_PRESS_RATE_SIZE);

NamedStore<double> * OxApp::algo_misc_rate = new NamedStore<double>(
                                                         ALGO_MISC_RATE_SIZE);

NamedStore<double> * OxApp::manual_double_vals = new NamedStore<double>(
                                                          MANUAL_DOUBLE_VALS);
NamedStore<uint16_t> * OxApp::manual_int_vals = new NamedStore<uint16_t>(
                                                            MANUAL_INT_VALS);

NamedStore<char> * OxApp::GPRMC = new NamedStore<char>(GPS_BUFF_SIZE);
NamedStore<char> * OxApp::GPGGA = new NamedStore<char>(GPS_BUFF_SIZE);

NamedStore<char> * OxApp::KEYBOARD_BUFFER = new NamedStore<char>(
                                                       KEYBOARD_BUFF_SIZE);

NamedStore<int8_t> * OxApp::system_status = new NamedStore<int8_t>(STATUS_SIZE);

bip::managed_shared_memory * OxApp::create() {
  //Create or open shared memory segment.
  if (OxApp::shm == 0) {

    OxApp::shm = new bip::managed_shared_memory(bip::open_or_create,
                                                MEM_NAME.c_str(),
                                                MEM_SIZE*sizeof(std::size_t));

    delete l_pressure;
    delete l_temp;
    delete l_accel;
    delete l_gyro;
    delete l_mag;
    
    delete l_gps_fix;

    delete algo_mad_euler;
    delete algo_mad_quat;
    delete algo_press;
    delete algo_press_rate;

    delete manual_double_vals;
    delete manual_int_vals;

    delete GPRMC;
    delete GPGGA;

    delete algo_misc_rate;
    delete KEYBOARD_BUFFER;

    delete system_status;
    
    l_pressure = new NamedStore<int32_t>( "BMP085.pressure", OxApp::shm, 
                                          L_PRESSURE_SIZE );
    l_temp = new NamedStore<float>( "BMP085.temp", OxApp::shm, L_TEMP_SIZE );
    l_accel = new NamedStore<double>( "LSM6.accel", OxApp::shm, L_ACCEL_SIZE );
    l_gyro = new NamedStore<double>( "LSM6.gyro", OxApp::shm, L_GYRO_SIZE );
    l_mag = new NamedStore<double>( "LIS3MDL.mag", OxApp::shm, L_MAG_SIZE );
    
    l_gps_fix = new NamedStore<double>( "GPS.fix", OxApp::shm, L_GPS_FIX_SIZE );

    algo_mad_euler = new NamedStore<double>( "ALGO.mad_euler", OxApp::shm, 
                                             ALGO_MAD_EULER_SIZE );
    algo_mad_quat = new NamedStore<double>( "ALGO.mad_quat", OxApp::shm,
                                            ALGO_MAD_QUAT_SIZE );
    algo_press = new NamedStore<double>( "ALGO.pressure", OxApp::shm,
                                         ALGO_PRESS_SIZE );
    algo_press_rate = new NamedStore<double>("ALGO.pressure_rate",OxApp::shm,
                                             ALGO_PRESS_RATE_SIZE);

    algo_misc_rate = new NamedStore<double>("ALGO.misc_rate",OxApp::shm,
                                            ALGO_MISC_RATE_SIZE);

    GPRMC = new NamedStore<char>("GPS.NMEA.gprmc",OxApp::shm,GPS_BUFF_SIZE,0);
    GPGGA = new NamedStore<char>("GPS.NMEA.gpgga",OxApp::shm,GPS_BUFF_SIZE,0);

    manual_double_vals = new NamedStore<double>("manual_double_vals",
                                                OxApp::shm,MANUAL_DOUBLE_VALS);

    manual_int_vals = new NamedStore<uint16_t>("manual_int_vals",
                                                OxApp::shm,MANUAL_INT_VALS);

    KEYBOARD_BUFFER = new NamedStore<char>("KEYBOARD_BUFFER",OxApp::shm,
                                           KEYBOARD_BUFF_SIZE,0);

    system_status = new NamedStore<int8_t>("status",OxApp::shm,STATUS_SIZE);

  }
  return OxApp::shm;
}
uint64_t OxApp::get_time_ms() {
     // Timestamp the data in milliseconds
    b::chrono::system_clock::time_point now = b::chrono::system_clock::now();
    b::chrono::nanoseconds sec =  now.time_since_epoch();
    b::chrono::milliseconds milliSecs = 
      b::chrono::duration_cast<b::chrono::milliseconds>(sec);
    return (uint64_t)milliSecs.count();
  }
void OxApp::get_time_str(std::string & s) {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%m/%d  %H:%M:%S");
  s.assign( oss.str() );
}
/************************************************************
 * Careful calling destroy, since it nukes the entire shared
 * memory pool. This should only be called when all apps are
 * shut down that want to access it.
 */
void OxApp::destroy() {

  delete l_pressure;
  delete l_temp;
  delete l_accel;
  delete l_gyro;
  delete l_mag;
  
  delete l_gps_fix;

  delete algo_mad_euler;
  delete algo_mad_quat;
  delete algo_press;
  delete algo_press_rate;

  delete algo_misc_rate;
  
  delete manual_double_vals;
  delete manual_int_vals;


  delete GPRMC;
  delete GPGGA;

  delete KEYBOARD_BUFFER;

  delete system_status;

  if (OxApp::shm != 0) {
    bip::shared_memory_object::remove( MEM_NAME.c_str() );
    delete OxApp::shm;
    OxApp::shm = 0;
  }
}


