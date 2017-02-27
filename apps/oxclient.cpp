#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/program_options.hpp>
#include "oxapp.h"

#include "oxbluebus.h"
#include "oxBlueDevice.h"
#include "devices/KOBO.h"

#include "algo/polar.h"
#include "algo/checksum.h"

#include <signal.h>

#include "trivial_log.h"

#include <iostream>
#include <sstream>

using namespace std;

static bool KEEP_GOING = true;

void control_c(int s) {
  KEEP_GOING = false;
  cout << endl;
}

int main(int argc, char * argv[] ){
  // http://www.radmangames.com/programming/how-to-use-boost-program_options
  namespace po = boost::program_options; 
  po::options_description desc("Options"); 
  desc.add_options() 
    ("help,h", "Print help messages")
    ("debug,d", "Print tons of debug stuff. Essentially disable init_prod log.")
    ("destroy", "Purge shared memory")
    ("kobo,k", "Sends mesages to KOBO bluetooth default 00:06:66:73:E6:0D"); 
 
  po::variables_map vm; 

  po::store(po::parse_command_line(argc, argv, desc),  
            vm);

  if ( vm.count("help")  ) { 
      cout << "Basic Command Line Parameter App" << endl 
           << desc << endl; 
      return 0; 
  }
  if ( !vm.count("debug")  ) { 
     init_production_log();
   }
   
  OxApp::create();

  if (vm.count("destroy")  ) { 
    OxApp::destroy();
    return 0;
  }
 
  
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  uint64_t i2c_last_time=0;
  double sampling_rate=(double)OxApp::get_time_ms();

  Polar polar;
  
  while( KEEP_GOING && ! vm.count("kobo")) {    
    if (i2c_last_time < OxApp::l_gyro->get_time(X) ) {
      i2c_last_time =  OxApp::l_gyro->get_time(X);
      sampling_rate = (OxApp::get_time_ms() - i2c_last_time) *0.001 ;
      cout <<  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
      cout << "Mroll: " <<  OxApp::algo_mad_euler->get_val(ROLL) <<
        " GPS_ROLL: " << OxApp::algo_mad_euler->get_val(GPS_ROLL) <<
        " Mpitch: " << OxApp::algo_mad_euler->get_val(PITCH) <<
        " Myaw: " <<  OxApp::algo_mad_euler->get_val(YAW) << endl; 

      cout << "Quaternion: " << OxApp::algo_mad_quat->get_val(A) << " " <<
        OxApp::algo_mad_quat->get_val(B) << " " <<
        OxApp::algo_mad_quat->get_val(C) << " " <<
        OxApp::algo_mad_quat->get_val(D) << " " << endl <<
        "-------------------- " << endl;
      cout<<"TE: "<<OxApp::algo_press_rate->get_val(PRESSURE_TE) <<
        " Pa/s IAS: " <<
        OxApp::algo_press_rate->get_val(PRESSURE_AIRSPEED) << " m/s^2 TAS: " <<
        OxApp::algo_press_rate->get_val(PRESSURE_TAS) << " m/s^2 Static: " <<
        OxApp::algo_press_rate->get_val(PRESSURE_ALTITUDE) << " m/s TEa: " <<
        OxApp::algo_press_rate->get_val(PRESSURE_TE_ALTITUDE) << " m/s GPS: "<< 
        OxApp::algo_misc_rate->get_val(GPS_ACCELERATION) <<" accel m/s^2 "<< 
        OxApp::algo_misc_rate->get_val(PITCH_RATE) <<" pitch rate m/s^2 Load:"<< 
        OxApp::algo_misc_rate->get_val(LOAD_FACTOR) <<" g" << 
        endl << "-----------------------" << endl;
      cout <<  "-------------------- " << endl <<
        OxApp::GPRMC->get_str() << OxApp::GPGGA->get_str() <<
        "-----------------------" << endl;
      
      cout << "Gyros: " << OxApp::l_gyro->get_val(X) << " " << 
        OxApp::l_gyro->get_val(Y) << 
        " " << OxApp::l_gyro->get_val(Z) <<" rad/s" <<  endl;
      cout <<"Accel: " <<  OxApp::l_accel->get_val(X) << " " << 
        OxApp::l_accel->get_val(Y) << 
        " " << OxApp::l_accel->get_val(Z) << " m/s2" << endl;
      cout << "Mag: " << OxApp::l_mag->get_val(X) << " " << 
        OxApp::l_mag->get_val(Y) << 
        " " << OxApp::l_mag->get_val(Z) << " gauss" << endl;
      cout <<  "-------------------- " << endl;
      cout << "TE: " << OxApp::l_pressure->get_val(BMP_TE)<<" pa "<<
        OxApp::algo_press->get_val(TE_ALTITUDE) << " m " <<
        OxApp::l_temp->get_val(BMP_TE) << " C" << endl <<
        "pitot: " << OxApp::l_pressure->get_val(BMP_PITOT)<< " pa "<<
         OxApp::algo_press->get_val(AIRSPEED)<< " m/s "<< 
        OxApp::l_temp->get_val(BMP_PITOT) << " C" << endl <<
        "static: " << OxApp::l_pressure->get_val(BMP_STATIC)<< " pa "<<
          OxApp::algo_press->get_val(ALTITUDE) << " m " <<
          OxApp::l_temp->get_val(BMP_STATIC) << " C" << endl;
      cout <<  "-------------------- " << sampling_rate << endl;
      cout << "GPS: " << OxApp::l_gps_fix->get_val(LONGITUDE) << " " << 
        OxApp::l_gps_fix->get_val(LATITUDE) << " " << 
        OxApp::l_gps_fix->get_val(GPS_ALTITUDE) << " m " << 
        OxApp::l_gps_fix->get_val(SPEED) << " m/s " << 
        OxApp::l_gps_fix->get_val(VERT_SPEED) << " m/s " << 
        OxApp::l_gps_fix->get_val(TRACK) << " rad " <<
        OxApp::l_gps_fix->get_val(TRACK_CHANGE) << " rad/s mode:" << 
        OxApp::l_gps_fix->get_val(MODE) << endl;
      cout <<  "-------------------- " << endl;
      cout << "McReady:     " << OxApp::manual_double_vals->get_val(MCREADY) << 
        endl;
      cout << "WingLoading: " <<
        OxApp::manual_double_vals->get_val(WING_LOADING) << endl;
      cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
      stringstream PGRMZ;
      stringstream PITV3;
      stringstream PITV4;

      PGRMZ<<"PGRMZ,"<< OxApp::l_gps_fix->get_val(GPS_ALTITUDE) << "," << "f" <<
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
  
      BOOST_LOG_TRIVIAL(debug) << GPRMC;
      BOOST_LOG_TRIVIAL(debug) << GPGGA;
      BOOST_LOG_TRIVIAL(debug) << PGRMZck.get_sentence();
      BOOST_LOG_TRIVIAL(debug) << PITV3ck.get_sentence();
      BOOST_LOG_TRIVIAL(debug) << PITV4ck.get_sentence();
    }
    
    b::this_thread::sleep(b::posix_time::milliseconds(5));
  } // local client printing to screen
  
  if ( vm.count("kobo")) {
    string remote_device = "00:06:66:73:E6:0D";
    OxBluebus bus( remote_device , 1);
    KOBO kobo;

    bus.add_device( &kobo );
    bus.run();
    while( KEEP_GOING ) {
      b::this_thread::sleep(b::posix_time::milliseconds(100));      
    }
    cout << "Stop...." << endl;
    bus.stop();
  }
  return 0;
}
