#include <math.h>
#include "oxapp.h"
#include "devices/GPS.h"
#include "trivial_log.h"

#include <string.h>
#include <termios.h>
#include <errno.h>


void GPS::NMEA() {

  char serbuf[255];
  char buf[4096];
  unsigned int flags;
  fd_set fds;

  struct gps_data_t gpsdata;
  struct fixsource_t source;

  std::string buff_str;
    
  flags = WATCH_ENABLE;
  flags |= WATCH_RAW;
  
  gpsd_source_spec(NULL, &source);
  
  if (gps_open(source.server, source.port, &gpsdata) != 0) {
    BOOST_LOG_TRIVIAL(error) << "gpspipe: could not connect to gpsd" ;
    return;
  }
  
  gps_stream(&gpsdata, flags, source.device);

  bool have_GPRMC = false;
  bool have_GPGGA = false;
  
  for (;(have_GPGGA == have_GPRMC) && ! have_GPGGA;) {
    int r = 0;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&fds);
    FD_SET(gpsdata.gps_fd, &fds);
      
    errno = 0;

    r = select(gpsdata.gps_fd+1, &fds, NULL, NULL, &tv);

    if (r == -1 && errno != EINTR) {
      BOOST_LOG_TRIVIAL(error) << "gpspipe: select error: " << r;
      break;
    } else if (r == 0)
      continue;
    
    /* reading directly from the socket avoids decode overhead */
    errno = 0;
    r = (int)read(gpsdata.gps_fd, buf, sizeof(buf));
    
    if (r > 0) {
      int i = 0;
      int j = 0;
      for (i = 0; i < r; i++) {
        char c = buf[i];
        if (j < (int)(sizeof(serbuf) - 1)) {
          serbuf[j++] = buf[i];
        }

        buff_str.append(1,c);
        
        if (c == '\n') {
          std::string lookup_s;
          if (buff_str.find("GPRMC") == 1) {
            OxApp::GPRMC->set_str(buff_str.c_str(),buff_str.length());
            have_GPRMC = true;
          }
          if (buff_str.find("GPGGA") == 1) {
            OxApp::GPGGA->set_str(buff_str.c_str(),buff_str.length());
            have_GPGGA = true;
          }
          buff_str.clear();
        }
      }
    } else {
      if (r == -1) {
		if (errno == EAGAIN)
          continue;
		else {
          BOOST_LOG_TRIVIAL(error) <<  "gpspipe: read error " << r;
            break;
        }
      } 
    }
  }
  close(gpsdata.gps_fd);
}

void GPS::rw_device() {

  
  if (!gpsd_shm->waiting(5000000)) {
    BOOST_LOG_TRIVIAL(debug) << "waiting return";
    return;
  }

  new_gps_data = gpsd_shm->read();

  if ( new_gps_data == 0 ) return;

  OxApp::l_gps_fix->set_val(STATUS,new_gps_data->status);
  
  bool new_update = false;

  if (new_gps_data->set & LATLON_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "LATLON_SET";
    OxApp::l_gps_fix->set_val(LONGITUDE,new_gps_data->fix.longitude);
    OxApp::l_gps_fix->set_val(LATITUDE,new_gps_data->fix.latitude);
  }
  if (new_gps_data->set & ALTITUDE_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "ALTITUDE_SET";
    OxApp::l_gps_fix->set_val(GPS_ALTITUDE,new_gps_data->fix.altitude);
    OxApp::l_gps_fix->set_val(VERT_SPEED,new_gps_data->fix.climb);
  }
  if (new_gps_data->set & SPEED_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "SPEED_SET";
    OxApp::l_gps_fix->set_val(SPEED,new_gps_data->fix.speed);
  }
  if (new_gps_data->set & TRACK_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "TRACK_SET";
    // Assume that the track change will be less than 180 deg / sec
    double track_change = OxApp::l_gps_fix->get_val( TRACK ) -
      new_gps_data->fix.track * M_PI / 180.0;
      if (track_change >= M_PI) {
        track_change = M_PI - track_change;
      }
      if (track_change <= - M_PI) {
        track_change = track_change - M_PI;
      }
      track_change = track_change / ( OxApp::get_time_ms() - OxApp::l_gps_fix->get_time( TRACK ) ) * 1000.0 ; // ms -> seconds
    OxApp::l_gps_fix->set_val(TRACK_CHANGE,track_change * M_PI / 180.0);
    OxApp::l_gps_fix->set_val(TRACK,new_gps_data->fix.track * M_PI / 180.0);
  }
  if (new_gps_data->set & TIME_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "TIME_SET";
    OxApp::l_gps_fix->set_val(TIME,new_gps_data->fix.time);
  }
  if (new_gps_data->set & MODE_SET) {
    new_update = true;
    BOOST_LOG_TRIVIAL(debug) << "MODE_SET";
    OxApp::l_gps_fix->set_val(MODE,new_gps_data->fix.mode);
  }

  if (new_update) {
     NMEA();
  }

  BOOST_LOG_TRIVIAL(debug) << "read success";
}




