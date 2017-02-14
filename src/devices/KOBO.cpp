#include "oxapp.h"
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include "devices/KOBO.h"
#include "algo/checksum.h"
#include "trivial_log.h"
#include <string>
#include <sstream>

using namespace std;

void KOBO::rw_device() {

  if( (OxApp::get_time_ms() - last_run) < interval ) return;
  last_run = OxApp::get_time_ms();

  stringstream PGRMZ;
  stringstream PITV3;
  stringstream PITV4;

  PGRMZ << "PGRMZ," << OxApp::l_gps_fix->get_val(GPS_ALTITUDE) << "," << "f" <<
    "," << "1";
  Checksum PGRMZck(PGRMZ);
  
  PITV3 << "PITV3," << OxApp::algo_mad_euler->get_val( ROLL ) << "," <<
    OxApp::algo_mad_euler->get_val( PITCH ) << "," <<
    OxApp::algo_mad_euler->get_val( YAW ) << "," <<
    OxApp::algo_press->get_val(AIRSPEED) << "," <<
    OxApp::algo_misc_rate->get_val(LOAD_FACTOR);
  Checksum PITV3ck(PITV3);

  PITV4 << "PITV4," << OxApp::algo_press_rate->get_val(PRESSURE_TE_ALTITUDE) <<
    "," << OxApp::algo_press_rate->get_val(PRESSURE_TE_ALTITUDE) - 
    polar.sink_rate( OxApp::algo_press->get_val(AIRSPEED)) << "," <<
    OxApp::algo_press_rate->get_val(PRESSURE_TE_ALTITUDE) - 
    polar.sink_rate( OxApp::algo_press->get_val(AIRSPEED)) << "," <<
    OxApp::algo_press->get_val(PRESSURE_ALTITUDE) << "," <<
    OxApp::algo_press->get_val(PRESSURE_TE_ALTITUDE) << "," <<
    OxApp::algo_press->get_val(PRESSURE_TE_ALTITUDE) ;
  Checksum PITV4ck(PITV4);

  string GPRMC( OxApp::GPRMC->get_str() );
  string GPGGA( OxApp::GPGGA->get_str() );

  if( bus->is_open() ) {
    bus->write( GPRMC );
    bus->write( GPGGA );

    bus->write( PGRMZck.get_sentence() );
    bus->write( PITV3ck.get_sentence() );
    bus->write( PITV4ck.get_sentence() );
  }

  BOOST_LOG_TRIVIAL(debug) << GPRMC;
  BOOST_LOG_TRIVIAL(debug) << GPGGA;
  BOOST_LOG_TRIVIAL(debug) << PGRMZck.get_sentence();
  BOOST_LOG_TRIVIAL(debug) << PITV3ck.get_sentence();
  BOOST_LOG_TRIVIAL(debug) << PITV4ck.get_sentence();

}
