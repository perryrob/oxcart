#include "oxapp.h"
#include "devices/KEYBOARD.h"
#include "trivial_log.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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
  BOOST_LOG_TRIVIAL(debug) << "Opened keyboard..";

}
void KEYBOARD::threaded_task() {

  if (failed) open_keyboard();

  struct input_event ev;
  ssize_t n;
  while (keep_running) {
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
  thr->join();
  delete thr;
  thr = 0;

}


