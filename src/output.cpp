
#include "output.h"
#include "oxapp.h"
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

Output::Output(unsigned int mode, unsigned int level) : _mode(mode),
                                                        _level(level) 
{
  if (_mode == FILE_MODE ) {
    static plog::RollingFileAppender<plog::CsvFormatter> rollingAppender(
         BONE_PATH.c_str(),
         MAX_FILE_SIZE,
         500);
    plog::init(plog::info, &rollingAppender);
  }
  if (_mode == CONSOLE_MODE) {
    static plog::ColorConsoleAppender<plog::CsvFormatter> consoleAppender;
    plog::init(plog::info, &consoleAppender);
  }
}

void Output::threaded_task(){

  while( keep_running ) {

    LOG_INFO << "EULER" << S << OxApp::algo_mad_euler->get_val(ROLL) << S <<  
      OxApp::algo_mad_euler->get_val(GPS_ROLL) << S <<
      OxApp::algo_mad_euler->get_val(PITCH) << S <<  
      OxApp::algo_mad_euler->get_val(YAW);

    LOG_INFO << "QUAT" << S << OxApp::algo_mad_quat->get_val(A) << S <<  
      OxApp::algo_mad_quat->get_val(B) << S <<
      OxApp::algo_mad_quat->get_val(C) << S <<  
      OxApp::algo_mad_quat->get_val(D);

    LOG_INFO << "RATE" << S << OxApp::algo_press_rate->get_val(PRESSURE_TE) <<
      S << OxApp::algo_press_rate->get_val(PRESSURE_TE_ALTITUDE) <<
      S << OxApp::algo_press_rate->get_val(PRESSURE_AIRSPEED) <<
      S << OxApp::algo_press_rate->get_val(PRESSURE_TAS) <<
      S << OxApp::algo_press_rate->get_val(PRESSURE_ALTITUDE) <<
      S << OxApp::algo_misc_rate->get_val(GPS_ACCELERATION) <<
      S << OxApp::algo_misc_rate->get_val(PITCH_RATE) <<
      S << OxApp::algo_misc_rate->get_val(LOAD_FACTOR) ;

    LOG_INFO << "ACCEL" << S << OxApp::l_accel->get_val(X) << S <<
      OxApp::l_accel->get_val(Y) << S <<
      OxApp::l_accel->get_val(Z);

    LOG_INFO << "GRYO" << S << OxApp::l_gyro->get_val(X) << S <<
      OxApp::l_gyro->get_val(Y) << S <<
      OxApp::l_gyro->get_val(Z);

    LOG_INFO << "MAG" << S << OxApp::l_mag->get_val(X) << S <<
      OxApp::l_mag->get_val(Y) << S <<
      OxApp::l_mag->get_val(Z);

    LOG_INFO << "PRESSURE" << S << OxApp::l_pressure->get_val(BMP_TE) <<
      S << OxApp::l_pressure->get_val(BMP_PITOT) <<
      S << OxApp::l_pressure->get_val(BMP_STATIC);

    LOG_INFO << "ALT_TEMP" << S << OxApp::algo_press->get_val(ALTITUDE) <<
      S << OxApp::l_temp->get_val(BMP_STATIC);
    
    LOG_INFO << "GPS" <<
      S << OxApp::l_gps_fix->get_val(LONGITUDE) <<
      S << OxApp::l_gps_fix->get_val(LATITUDE) <<
      S << OxApp::l_gps_fix->get_val(GPS_ALTITUDE) <<
      S << OxApp::l_gps_fix->get_val(SPEED) <<
      S << OxApp::l_gps_fix->get_val(VERT_SPEED) <<
      S << OxApp::l_gps_fix->get_val(TRACK) <<
      S << OxApp::l_gps_fix->get_val(TRACK_CHANGE) <<
      S << OxApp::l_gps_fix->get_val(MODE);
      
    LOG_INFO << "AIRDATA" <<
      S << OxApp::algo_press->get_val(AIRSPEED) <<
      S << OxApp::algo_press->get_val(TAS);

    b::this_thread::sleep(b::posix_time::milliseconds(10));
  }

}

void Output::run(){
  keep_running = true;
  thr = new b::thread(b::bind(&Output::threaded_task, this));
}
void Output::stop(){
  keep_running = false;
}

Output::~Output(){
  thr->join();
  delete thr;
  thr = 0;
}
