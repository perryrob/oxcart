#include "oxapp.h"
#include <boost/interprocess/managed_shared_memory.hpp>

bip::managed_shared_memory * OxApp::shm = 0;

NamedStore<int32_t> * OxApp::l_pressure = new NamedStore<int32_t>(3);
NamedStore<float> * OxApp::l_temp = new NamedStore<float>(3);
NamedStore<float> * OxApp::l_alt = new NamedStore<float>( 1);
NamedStore<int16_t> * OxApp::l_accel = new NamedStore<int16_t>(3);
NamedStore<int16_t> * OxApp::l_gyro = new NamedStore<int16_t>(3);
NamedStore<int16_t> * OxApp::l_mag = new NamedStore<int16_t>(3);

NamedStore<double> * OxApp::l_gps_fix = new NamedStore<double>(8);

bip::managed_shared_memory * OxApp::create() {
  //Create or open shared memory segment.
  if (OxApp::shm == 0) {

    OxApp::shm = new bip::managed_shared_memory(bip::open_or_create,
                                                MEM_NAME.c_str(),
                                                MEM_SIZE*sizeof(std::size_t));

    delete l_pressure;
    delete l_temp;
    delete l_alt;
    delete l_accel;
    delete l_gyro;
    delete l_mag;
    
    delete l_gps_fix;
    
    l_pressure = new NamedStore<int32_t>( "BMP085.pressure", OxApp::shm, 3 );
    l_temp = new NamedStore<float>( "BMP085.temp", OxApp::shm, 3 );
    l_alt = new NamedStore<float>( "BMP085.alt", OxApp::shm, 1 );
    l_accel = new NamedStore<int16_t>( "LSM6.accel", OxApp::shm, 3 );
    l_gyro = new NamedStore<int16_t>( "LSM6.gyro", OxApp::shm, 3 );
    l_mag = new NamedStore<int16_t>( "LIS3MDL.mag", OxApp::shm, 3 );
    
    l_gps_fix = new NamedStore<double>( "GPS.fix", OxApp::shm, 8 );
    
  }
  return OxApp::shm;
}
/************************************************************
 * Careful calling destroy, since it nukes the entire shared
 * memory pool. This should only be called when all apps are
 * shut down that want to access it.
 */
void OxApp::destroy() {

  delete l_pressure;
  delete l_temp;
  delete l_alt;
  delete l_accel;
  delete l_gyro;
  delete l_mag;
  
  delete l_gps_fix;
  
  if (OxApp::shm != 0) {
  bip::shared_memory_object::remove( MEM_NAME.c_str() );
  delete OxApp::shm;
  OxApp::shm = 0;
  }
}

