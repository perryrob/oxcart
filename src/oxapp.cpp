#include "oxapp.h"
#include <boost/interprocess/managed_shared_memory.hpp>

bip::managed_shared_memory * OxApp::shm = 0;

NamedStore<int32_t> * OxApp::l_pressure = new NamedStore<int32_t>(3);
NamedStore<float> * OxApp::l_temp = new NamedStore<float>(3);
NamedStore<double> * OxApp::l_accel = new NamedStore<double>(3);
NamedStore<double> * OxApp::l_gyro = new NamedStore<double>(3);
NamedStore<double> * OxApp::l_mag = new NamedStore<double>(3);

NamedStore<double> * OxApp::l_gps_fix = new NamedStore<double>(9);

NamedStore<double> * OxApp::algo_mad_euler = new NamedStore<double>(4);
NamedStore<double> * OxApp::algo_mad_quat = new NamedStore<double>(4);
NamedStore<double> * OxApp::algo_press = new NamedStore<double>(5);
NamedStore<double> * OxApp::algo_press_rate = new NamedStore<double>(5);

NamedStore<double> * OxApp::algo_misc_rate = new NamedStore<double>(2);

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

    delete algo_misc_rate;
    
    l_pressure = new NamedStore<int32_t>( "BMP085.pressure", OxApp::shm, 3 );
    l_temp = new NamedStore<float>( "BMP085.temp", OxApp::shm, 3 );
    l_accel = new NamedStore<double>( "LSM6.accel", OxApp::shm, 3 );
    l_gyro = new NamedStore<double>( "LSM6.gyro", OxApp::shm, 3 );
    l_mag = new NamedStore<double>( "LIS3MDL.mag", OxApp::shm, 3 );
    
    l_gps_fix = new NamedStore<double>( "GPS.fix", OxApp::shm, 9 );

    algo_mad_euler = new NamedStore<double>( "ALGO.mad_euler", OxApp::shm, 4 );
    algo_mad_quat = new NamedStore<double>( "ALGO.mad_quat", OxApp::shm, 4 );
    algo_press = new NamedStore<double>( "ALGO.pressure", OxApp::shm, 5 );
    algo_press_rate = new NamedStore<double>("ALGO.pressure_rate",OxApp::shm,5);

    algo_misc_rate = new NamedStore<double>("ALGO.misc_rate",OxApp::shm,2);
  }
  return OxApp::shm;
}
uint64_t OxApp::get_time_ms() {
     // Timestamp the data in milliseconds
    b::chrono::system_clock::time_point now = b::chrono::system_clock::now();
    b::chrono::nanoseconds sec =  now.time_since_epoch();
    b::chrono::milliseconds milliSecs = b::chrono::duration_cast<b::chrono::milliseconds>(sec);
    return (uint64_t)milliSecs.count();
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
  
  if (OxApp::shm != 0) {
  bip::shared_memory_object::remove( MEM_NAME.c_str() );
  delete OxApp::shm;
  OxApp::shm = 0;
  }
}


