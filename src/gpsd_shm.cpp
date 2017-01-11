
#include "gpsd_shm.h"


GPSD_SHM::GPSD_SHM() : gpsmm("localhost",DEFAULT_GPSD_PORT), streaming(false) {
  streaming = stream(WATCH_ENABLE|WATCH_JSON) != NULL;
}

GPSD_SHM::~GPSD_SHM() {}
