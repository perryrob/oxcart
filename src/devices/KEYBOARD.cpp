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
  buffer = "";
  OxApp::KEYBOARD_BUFFER->set_str(buffer.c_str(),buffer.size());
  OxApp::manual_int_vals->set_val( DISP_CMD,0 );
  OxApp::manual_int_vals->set_val( DISP_PAGE_NO, 0 );
}
void KEYBOARD::open_keyboard() {

  do {
    device_fd = open(device.c_str(), O_RDONLY);
    if (device_fd == -1) {
      BOOST_LOG_TRIVIAL(error) << "Cannot open: " << device << " "<< strerror(errno);
      failed = true;
    } else {
      failed = false;
      break;
    }
    b::this_thread::sleep(b::posix_time::milliseconds(500));
  } while( failed ) ;

  FD_ZERO(&set); /* clear the set */
  FD_SET(device_fd, &set); /* add our file descriptor to the set */

  timeout.tv_sec = 1;

  BOOST_LOG_TRIVIAL(debug) << "Opened keyboard..";

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
    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
      printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
      // Key Released
      if ( ev.value == 1 ){
        char c = key_mapper.get_char_from_code( (uint8_t)ev.code );
        if ( (uint8_t)c == 0 ) {
          uint8_t cmd = key_mapper.get_action_from_code( (uint8_t)ev.code );
          switch( cmd ) {
          case  KEY_BACKSPACE:
            if ( buffer.size() > 0) {
              buffer.pop_back();
            }
            break;
          case KEY_ENTER:
            OxApp::manual_int_vals->set_val( SYS_CMD, KEY_ENTER );
            break;
          case KEY_ESC:
            buffer = "";
            break;
          }
        } else {
          buffer.push_back(c);
        }
        OxApp::KEYBOARD_BUFFER->set_str(buffer.c_str(),buffer.size()+1);
        BOOST_LOG_TRIVIAL(debug) << OxApp::KEYBOARD_BUFFER->get_str();
      }
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


