
#include "oxapp.h"
#include "devices/GPS.h"
#include "trivial_log.h"

void GPS::rw_device() {

  
  if (!gpsd_shm->waiting(5000000)) {
    BOOST_LOG_TRIVIAL(debug) << "waiting return";
    return;
  }
  new_gps_data = gpsd_shm->read();

  if ( new_gps_data == 0 ) return;    

  BOOST_LOG_TRIVIAL(debug) << "read success";
  
  if (new_gps_data->set & ONLINE_SET) {

    BOOST_LOG_TRIVIAL(debug) << "ONLINE_SET";
    if (new_gps_data->set & LATLON_SET) {
      BOOST_LOG_TRIVIAL(debug) << "LATLON_SET";
      OxApp::l_gps_fix->set_val(LONGITUDE,new_gps_data->fix.longitude);
      OxApp::l_gps_fix->set_val(LATITUDE,new_gps_data->fix.latitude);
    }
    if (new_gps_data->set & ALTITUDE_SET) {
      BOOST_LOG_TRIVIAL(debug) << "ALTITUDE_SET";
      OxApp::l_gps_fix->set_val(GPS_ALTITUDE,new_gps_data->fix.altitude);
      OxApp::l_gps_fix->set_val(VERT_SPEED,new_gps_data->fix.climb);
    }
    if (new_gps_data->set & SPEED_SET) {
      BOOST_LOG_TRIVIAL(debug) << "SPEED_SET";
      OxApp::l_gps_fix->set_val(SPEED,new_gps_data->fix.altitude);
    }
    if (new_gps_data->set & TRACK_SET) {
      BOOST_LOG_TRIVIAL(debug) << "TRACK_SET";
      OxApp::l_gps_fix->set_val(TRACK,new_gps_data->fix.track);
    }
    if (new_gps_data->set & TIME_SET) {
      BOOST_LOG_TRIVIAL(debug) << "TIME_SET";
      OxApp::l_gps_fix->set_val(TIME,new_gps_data->fix.time);
    }
    if (new_gps_data->set & MODE_SET) {
      BOOST_LOG_TRIVIAL(debug) << "MODE_SET";
      OxApp::l_gps_fix->set_val(MODE,new_gps_data->fix.mode);
    }
  }
}




