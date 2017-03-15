/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/program_options.hpp>
#include "oxapp.h"
#include "conversion.h"
#include "oxbluebus.h"
#include "oxBlueDevice.h"

#include "output.h"
#include "devices/KOBO.h"
#include "devices/KEYBOARD.h"
#include "devices/NCURSES.h"

#include "algo/polar.h"
#include "algo/linregres.h"
#include "algo/checksum.h"
#include "algo/average.h"

#include <signal.h>

#include "trivial_log.h"

#include <iostream>
#include <sstream>

using namespace std;

static bool KEEP_GOING = true;

void control_c(int s) {
  OxApp::system_status->set_val( OXCLIENT_STAT,SHUTTING_DOWN);
  BOOST_LOG_TRIVIAL(warning) << "oxalgos shutting down..." ;
  b::this_thread::sleep(b::posix_time::milliseconds(100));
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){
  // http://www.radmangames.com/programming/how-to-use-boost-program_options
  namespace po = boost::program_options; 
  po::options_description desc("Options"); 
  desc.add_options() 
    ("help,h", "Print help messages")
    ("debug,d", "Print tons of debug stuff. Essentially disable init_prod log.")
    ("info,i", "Print a little more quiet info log.")
    ("ncurses,n", "Show an ncurses display like the instrument.")
    ("verbose,v", "Show default tons  of text.")
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

  if ( vm.count("info")  ) { 
     init_info_log();
   }

  OxApp::create();
  OxApp::system_status->set_val( OXCLIENT_STAT,STARTING);
  if( OxApp::time_set() ){}
  while(OxApp::system_status->get_val( OXCART_D_STAT ) < RUNNING) {
    if ( ! KEEP_GOING ) break;
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  }
  /************************************************************
   *
   * Start the output NOTE: its start from the GUI.
   */
  Output o(FILE_MODE,BASIC_LEVEL);
  o.run();

  if (vm.count("destroy")  ) { 
    OxApp::destroy();
    return 0;
  }
  // Default is set to off
  OxApp::system_status->set_val( OUTPUT,0 );
  
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  uint64_t i2c_last_time=0;
  
  Polar polar;

  auto start_time = (double)OxApp::get_time_ms();
  auto end_time = (double)OxApp::get_time_ms();

  /************************************************************
   *
   * Start up the keyboard.
   */
  KEYBOARD k("/dev/input/event1");
  k.run();



  if( vm.count("ncurses") ) {
    NCURSES_DISP nd;
    while( KEEP_GOING ) {
      OxApp::system_status->set_val( OXCLIENT_STAT,RUNNING);
      nd.rw_device();
      b::this_thread::sleep(b::posix_time::milliseconds(100));      
    }
  }
  
  Average sampling_rate(100);  

  /************************************************************
   *
   * Verbose mode
   */
  while( KEEP_GOING && vm.count("verbose")) {
    if (OxApp::system_status->get_val( OXCLIENT_STAT ) == SHUTTING_DOWN) {
      break;
    }
    OxApp::system_status->set_val( OXCLIENT_STAT,RUNNING);
    if (i2c_last_time < OxApp::l_gyro->get_time(X) ) {
      end_time=(double)OxApp::get_time_ms();
      sampling_rate.update( (1.0 / ((end_time-start_time) * 0.001)) );
      start_time=(double)OxApp::get_time_ms();
      i2c_last_time =  OxApp::l_gyro->get_time(X);
      cout <<  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
      cout << "Mroll: " <<  OxApp::algo_mad_euler->get_val(ROLL) <<
        " GPS_ROLL: " << OxApp::algo_mad_euler->get_val(GPS_ROLL) <<
        " Mpitch: " << OxApp::algo_mad_euler->get_val(PITCH) <<
        " Myaw: " <<  OxApp::algo_mad_euler->get_val(YAW) << endl; 

      cout << "Quaternion: " << OxApp::algo_mad_quat->get_val(A) <<   " " <<
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
      cout <<
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
        Conv::knots(OxApp::algo_press->get_val(AIRSPEED)) << " kias " <<
        Conv::knots(OxApp::algo_press->get_val(TAS)) << " ktas " <<
        OxApp::l_temp->get_val(BMP_PITOT) << " C" << endl <<
        "static: " << OxApp::l_pressure->get_val(BMP_STATIC)<< " pa "<<
          OxApp::algo_press->get_val(ALTITUDE) << " m " <<
        Conv::feet(OxApp::algo_press->get_val(ALTITUDE)) << " ft " <<
          OxApp::l_temp->get_val(BMP_STATIC) << " C " <<
        OxApp::algo_press->get_val(LOCAL_RHO) << " ~" << endl;
      cout <<  "------------- " << sampling_rate.get_average() << " Hz" << endl;
      cout << "GPS: " << OxApp::l_gps_fix->get_val(LONGITUDE) << " " << 
        OxApp::l_gps_fix->get_val(LATITUDE) << " " << 
        OxApp::l_gps_fix->get_val(GPS_ALTITUDE) << " m " << 
        OxApp::l_gps_fix->get_val(SPEED) << " m/s " << 
        OxApp::l_gps_fix->get_val(VERT_SPEED) << " m/s " << 
        OxApp::l_gps_fix->get_val(TRACK) << " rad " <<
        OxApp::l_gps_fix->get_val(TRACK_CHANGE) << " rad/s mode: " << 
        OxApp::l_gps_fix->get_val(MODE) ;
      cout <<  endl << "-------------------- " << endl;
      cout << "McReady:     " << OxApp::manual_double_vals->get_val(MCREADY) << 
        endl;
      cout << "WingLoading: " <<
        OxApp::manual_double_vals->get_val(WING_LOADING) << endl;
      cout << "> " << OxApp::KEYBOARD_BUFFER->get_str() << endl;

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
  } 
  /************************************************************
   *
   * Run the KOBO portion to connect to XCSoar.
   */
  if ( vm.count("kobo")) {
    cout << "Kobo: enabled.." << endl;
    string remote_device = "00:06:66:73:E6:0D";
    OxBluebus bus( remote_device , 1);
    KOBO kobo;
    bus.add_device( &kobo );
    bus.run();
    while( KEEP_GOING ) {
      OxApp::system_status->set_val( OXCLIENT_STAT,RUNNING);
      b::this_thread::sleep(b::posix_time::milliseconds(100));      
    }
    cout << "Stop...." << endl;
    bus.stop();
  }
  /************************************************************
   *
   * Shut down sequence
   */
  BOOST_LOG_TRIVIAL(warning) << "oxalgos shut down." ;
  OxApp::system_status->set_val( OXCLIENT_STAT,SHUTDOWN);
  b::this_thread::sleep(b::posix_time::milliseconds(500));
  k.stop();
  o.stop();
  OxApp::manual_int_vals->set_val( SYS_CMD,0 );
  OxApp::system_status->set_val( LED_1,0 );
  OxApp::system_status->set_val( LED_2,0 );
  OxApp::system_status->set_val( LED_3,0 );
  return 0;
}
