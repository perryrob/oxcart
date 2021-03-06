/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <time.h>
#include <unistd.h>
#include "arduino_core.h"


unsigned  long millis(){
  struct timespec tt;
  clock_gettime(CLOCK_MONOTONIC, &tt);
  return  tt.tv_nsec/1000000+ tt.tv_sec * 1000;
}
void delay( long ms ) {
  usleep( ms * 1000 );
}
