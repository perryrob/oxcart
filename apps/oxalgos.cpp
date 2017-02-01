
#include "oxapp.h"
#include "oxalgothread.h"

#include "algo/MadgwickAHRS.h"


#include <signal.h>
#include "trivial_log.h"
#include <iostream>

static bool KEEP_GOING = true;

void control_c(int s) {
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){
  
  init_production_log();
 
  OxApp::create();

  OxAlgoThread algo_thread; 
  Madgwick mw;
  
  
  algo_thread.add_algo(&mw);
  algo_thread.run();
  
  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);


  while( KEEP_GOING ) {
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  }
  algo_thread.stop();
}