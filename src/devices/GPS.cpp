
#include "oxapp.h"
#include "devices/GPS.h"

void GPS::rw_sensor() {
  bip::managed_shared_memory * shm = OxApp::get_shared_mem();
  if (shm == 0) {

    if (!gpsd_shm->waiting(5000000)) {
      return;
    }

    new_gps_data = gpsd_shm->read();

    if ( new_gps_data == 0 ) return;    


  }
}




