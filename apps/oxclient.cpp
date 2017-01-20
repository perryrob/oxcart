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

  uint64_t last_time=0;

  while( KEEP_GOING ) {
    if (last_time < OxApp::l_gyro->get_time(X) ) {
      last_time =  OxApp::l_gyro->get_time(X);
      cout << OxApp::l_gyro->get_val(X) << " " << OxApp::l_gyro->get_val(Y) << 
        " " << OxApp::l_gyro->get_val(Z) << endl;
      cout << OxApp::l_accel->get_val(X) << " " << OxApp::l_accel->get_val(Y) << 
        " " << OxApp::l_accel->get_val(Z) << endl;
      cout <<  "--------------------" << endl;
    }
    b::this_thread::sleep(b::posix_time::milliseconds(5));
  }
  cout << endl;
}
