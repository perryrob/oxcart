#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "oxapp.h"

#include <signal.h>

#include "trivial_log.h"

#include <iostream>

using namespace std;

static bool KEEP_GOING = true;

void control_c(int s) {
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){

  init_production_log();

  OxApp::create();

  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  uint64_t i2c_last_time=0;
  double sampling_rate=(double)OxApp::get_time_ms();

  
  while( KEEP_GOING ) {    
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
        OxApp::algo_misc_rate->get_val(PITCH_RATE) <<" pitch rate m/s^2" << 
        endl << "-----------------------" << endl;
      
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
      cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
    }
    
    b::this_thread::sleep(b::posix_time::milliseconds(5));
  }
  cout << endl;
}
