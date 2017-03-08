/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "gpsd_shm.h"


GPSD_SHM::GPSD_SHM() : gpsmm("localhost",DEFAULT_GPSD_PORT), streaming(false) {
  streaming = stream(WATCH_ENABLE|WATCH_JSON) != NULL;
}

GPSD_SHM::~GPSD_SHM() {}
