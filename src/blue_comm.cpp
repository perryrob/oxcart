
#include "blue_comm.h"

BlueComm::BlueComm(std::string &address, int channel):sock(0),_is_open(false) {

  if(hci_devinfo(0, &di) < 0)  {
    perror("HCI device info failed");
  }

  laddr.rc_family = AF_BLUETOOTH;
  laddr.rc_bdaddr = di.bdaddr;
  laddr.rc_channel = 0;

  raddr.rc_family = AF_BLUETOOTH;
  str2ba(address.c_str(),&raddr.rc_bdaddr);
  raddr.rc_channel = channel;  

}
bool BlueComm::open() {

  _is_open = true;

  if( (sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
      perror("socket");
      _is_open = false;
  }

  if(bind(sock, (struct sockaddr *)&laddr, sizeof(laddr)) < 0) {
    perror("bind");
    _is_open = false;
  }

  return _is_open;

}
bool BlueComm::close() {

  if (_is_open) {
    shutdown( sock, SHUT_RDWR );
    sock=0;
    _is_open = false;
    return true;
  }
  return false;
}
int BlueComm::read( char * buffer ){

  if(_is_open) {
    return recv(sock, buffer, sizeof buffer, 0);
  }
  return -1;
}
int BlueComm::has_data(){

  if(_is_open) {
    return recv( sock, 0, 0, MSG_PEEK );
  }
  return -1;
}
int BlueComm::write( std::string &msg) {

  if(_is_open) {
    return send(sock,msg.c_str(),msg.size(),0);
  }
  return -1;
}
BlueComm::~BlueComm(){
  close();
}


