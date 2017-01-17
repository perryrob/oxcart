#ifndef __BLUE_COMM_H__
#define __BLUE_COMM_H__

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <string>

class BlueComm {

 public:
  
   BlueComm(): sock(0), _is_open(false){}
   BlueComm(std::string &address, int channel);

   bool open();
   bool close();
   bool is_open() { return _is_open; }
   int read( char * buffer );
   int has_data();
   int write(std::string &mesg);

 protected:
   ~BlueComm();

 private:

   int sock;
   std::string address;
   struct sockaddr_rc laddr, raddr;
   struct hci_dev_info di;
   bool _is_open;
};
#endif
