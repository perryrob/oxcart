/*
 * gpspipe
 *
 * a simple program to connect to a gpsd daemon and dump the received data
 * to stdout
 *
 * This will dump the raw NMEA from gpsd to stdout
 *      gpspipe -r
 *
 * This will dump the super-raw data (gps binary) from gpsd to stdout
 *      gpspipe -R
 *
 * This will dump the GPSD sentences from gpsd to stdout
 *      gpspipe -w
 *
 * This will dump the GPSD and the NMEA sentences from gpsd to stdout
 *      gpspipe -wr
 *
 * Original code by: Gary E. Miller <gem@rellim.com>.  Cleanup by ESR.
 *
 * This file is Copyright (c) 2010 by the GPSD project
 * BSD terms apply: see the file COPYING in the distribution root for details.
 *
 */

/* cfmakeraw() needs _DEFAULT_SOURCE */
#define _DEFAULT_SOURCE
/* daemon() needs _DEFAULT_SOURCE */
#define _DEFAULT_SOURCE


#include <time.h>               /* for time_t */
#include "gpsd/gpsd_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include "trivial_log.h"
#include <gps.h>

#include "gpsd/gpsd_config.h"
#include "gpsd/gpsdclient.h"
#include "gpsd/revision.h"

using namespace std;

/* NMEA-0183 standard baud rate */
#define BAUDRATE B4800

int main(int argc, char **argv)
{
  char buf[4096];
  char serbuf[255];
  unsigned int flags;
  fd_set fds;
  struct gps_data_t gpsdata;

  struct fixsource_t source;

  string buff_str;
    
  flags = WATCH_ENABLE;
  flags |= WATCH_RAW;
  
  gpsd_source_spec(NULL, &source);
  
  if (gps_open(source.server, source.port, &gpsdata) != 0) {
    (void)fprintf(stderr,
                  "gpspipe: could not connect to gpsd %s:%s, %s(%d)\n",
                  source.server, source.port, gps_errstr(errno), errno);
    exit(EXIT_FAILURE);
  }
  
  (void)gps_stream(&gpsdata, flags, source.device);

  for (;;) {
    int r = 0;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&fds);
    FD_SET(gpsdata.gps_fd, &fds);
      
    errno = 0;

    r = select(gpsdata.gps_fd+1, &fds, NULL, NULL, &tv);

    if (r == -1 && errno != EINTR) {
      (void)fprintf(stderr, "gpspipe: select error %s(%d)\n",
                    strerror(errno), errno);
      exit(EXIT_FAILURE);
    } else if (r == 0)
      continue;
    
    /* reading directly from the socket avoids decode overhead */
    errno = 0;
    r = (int)read(gpsdata.gps_fd, buf, sizeof(buf));
    if (r > 0) {
      int i = 0;
      int j = 0;
      for (i = 0; i < r; i++) {
        char c = buf[i];
        if (j < (int)(sizeof(serbuf) - 1)) {
          serbuf[j++] = buf[i];
        }

        buff_str.append(1,c);
        
        if (c == '\n') {
          BOOST_LOG_TRIVIAL(debug) << buff_str ;
          buff_str.clear();
        }
      }
    } else {
      if (r == -1) {
		if (errno == EAGAIN)
          continue;
		else
          (void)fprintf(stderr, "gpspipe: read error %s(%d)\n",
                        strerror(errno), errno);
		exit(EXIT_FAILURE);
      } else {
        exit(EXIT_SUCCESS);
      }
    }
  }
  exit(EXIT_SUCCESS);
}



