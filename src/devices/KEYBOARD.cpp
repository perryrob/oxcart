
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

int main(void) {
  const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  struct input_event ev;
  ssize_t n;
  int fd;
  
  fd = open(dev, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
    return EXIT_FAILURE;
  }
  while (1) {
    n = read(fd, &ev, sizeof ev);
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
    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2)
      printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
  }
  fflush(stdout);
  fprintf(stderr, "%s.\n", strerror(errno));
  return EXIT_FAILURE;
}
*/
KEYBOARD::KEYBOARD(const char * dev) {
  device_fd = open(dev, O_RDONLY);
  if (device_fd == -1) {
    BOOST_LOG_TRIVIAL(error) << "Cannot open: " << dev<< " "<< strerror(errno);
    failed = true;
  }  
}

void KEYBOARD::threaded_task() {
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
    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2)
      printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
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


