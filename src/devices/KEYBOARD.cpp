/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxapp.h"
#include "devices/KEYBOARD.h"
#include "trivial_log.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

/***
https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
*/
KEYBOARD::KEYBOARD(const char * dev) {
  device = dev;
  failed = true;
  command_proc.init();
}
void KEYBOARD::open_keyboard() {
  bool not_reported = true;
  do {
    device_fd = open(device.c_str(), O_RDONLY);
    if (device_fd == -1) {
      OxApp::system_status->set_val( LED_2,1 );
      if ( not_reported ) {
        BOOST_LOG_TRIVIAL(error) << "Cannot open: " <<
          device << " "<< strerror(errno);
        not_reported = false;
      }
      failed = true;
    } else {
      failed = false;
      break;
    }
    if (OxApp::system_status->get_val( OXCLIENT_STAT ) >= SHUTTING_DOWN) {
      failed = false;
      keep_running = false;
      BOOST_LOG_TRIVIAL(debug) << "KEBOARD oxclient shutting down..";
      break;
    }
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  } while( failed ) ;

  FD_ZERO(&set); /* clear the set */
  FD_SET(device_fd, &set); /* add our file descriptor to the set */

  timeout.tv_sec = 1;

  BOOST_LOG_TRIVIAL(debug) << "Opened keyboard..";
  OxApp::system_status->set_val( LED_2,0 );
}
void KEYBOARD::threaded_task() {

  if (failed) open_keyboard();

  struct input_event ev;
  ssize_t n;
  
  while (keep_running) {
    rv = select(device_fd + 1, &set, NULL, NULL, &timeout);
    if(rv == -1)
      perror("select"); /* an error accured */
    else if(rv == 0) {
      FD_ZERO(&set); /* clear the set */
      FD_SET(device_fd, &set); /* add our file descriptor to the set */
      timeout.tv_sec = 1;
      continue;      
    } else
      n = read( device_fd, &ev, sizeof ev);
    if (n == (ssize_t)-1) {
      if (errno == EINTR)
        continue;
      else
        break;
    } else
      if (n != sizeof ev) {
        errno = EIO;
        break;
      }
    /**
     * Hand over to the command processor
     */
    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
      command_proc.process_event( ev );
    }
  }
}

void KEYBOARD::run() {
  keep_running = true;
  thr = new b::thread(b::bind(&KEYBOARD::threaded_task, this));
}
void KEYBOARD::stop() {
  keep_running = false;
  close(device_fd);
  thr->join();
  delete thr;
  thr = 0;

}


