/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "oxalgothread.h"

#include "algo/MadgwickAHRS.h"
#include "algo/total_energy.h"
#include "algo/airdata.h"
#include "algo/misc_rate.h"


#include <signal.h>
#include "trivial_log.h"
#include <iostream>

static bool KEEP_GOING = true;

void control_c(int s) {
  OxApp::system_status->set_val( OXALGOS_STAT,SHUTTING_DOWN);
  KEEP_GOING = false;
}

int main(int argc, char * argv[] ){
  
  init_production_log();
 
  OxApp::create();
  OxApp::system_status->set_val( OXALGOS_STAT,STARTING);
  if( OxApp::time_set() ){}
  /************************************************************
   * wait for oxcart_d
   */
  while(OxApp::system_status->get_val( OXCART_D_STAT ) < RUNNING) {
    if ( ! KEEP_GOING ) break;
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  }
  /************************************************************
   *
   * Initialize any shared mem values
   *
   */
  OxApp::manual_double_vals->set_val(MCREADY,0.0);
  OxApp::manual_double_vals->set_val(WING_LOADING,1.0);
  OxApp::manual_double_vals->set_val(SEA_LEVEL_PRESSURE,101325.0);
  
  OxAlgoThread algo_thread; 
  Madgwick mw;
  TotalEnergy te;
  MiscRate mr;
  Airdata a;
  
  algo_thread.add_algo(&mw);
  algo_thread.add_algo(&a);
  algo_thread.add_algo(&te);
  algo_thread.add_algo(&mr);

  algo_thread.run();
  
  struct sigaction sigIntHandler;
  
  sigIntHandler.sa_handler =  control_c;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);


  while( KEEP_GOING ) {
    OxApp::system_status->set_val( OXALGOS_STAT,RUNNING);
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  }
  OxApp::system_status->set_val( OXALGOS_STAT,SHUTDOWN);
  algo_thread.stop();
}
