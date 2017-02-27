
#include "blue_comm.h"
#include "trivial_log.h"

BlueComm::BlueComm(std::string &address, int channel ):sock(0),_is_open(false) {
  this->address = address;
  
  if(hci_devinfo(0, &di) < 0)  {
    BOOST_LOG_TRIVIAL(error) << "HCI device info failed";
  }

  laddr.rc_family = AF_BLUETOOTH;
  laddr.rc_bdaddr = di.bdaddr;
  laddr.rc_channel = 0;

  raddr.rc_family = AF_BLUETOOTH;
  str2ba(this->address.c_str(),&raddr.rc_bdaddr);
  raddr.rc_channel = channel;

}
bool BlueComm::open() {

  if( (sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
    BOOST_LOG_TRIVIAL(error) << "Socket OPEN failed.";
      _is_open = false;
  } else {
    BOOST_LOG_TRIVIAL(debug) << "open success";
  }

  if(bind(sock, (struct sockaddr *)&laddr, sizeof(laddr)) < 0) {
    BOOST_LOG_TRIVIAL(error) << "Socket BIND failed.";
    _is_open = false;
  } else {
    BOOST_LOG_TRIVIAL(debug) << "bind success";
  }

  if(connect(sock, (struct sockaddr *)&raddr, sizeof(raddr)) < 0) {
    BOOST_LOG_TRIVIAL(error) << "Socket connect failed: " << address ;
    _is_open = false;
  } else {
    _is_open = true;
  }
  
  if(! _is_open) {
    BOOST_LOG_TRIVIAL(error) << "Attempting to reconnect(open)";
    close( sock );
    if (this->open() ) {
      BOOST_LOG_TRIVIAL(error) << "Reconnected!";
    }
  } 
  _is_open = true;
  return _is_open;

}
bool BlueComm::close_it() {
  close( sock );
  if (_is_open) {
    shutdown( sock, SHUT_RDWR );
    sock=0;
    _is_open = false;
    return true;
  }
  return false;
}
int BlueComm::read( char * buffer ){

  int bytes_rec=-1;

  if(_is_open) {
    bytes_rec = recv(sock, buffer, sizeof buffer, 0);
    if( bytes_rec < 0) {
      BOOST_LOG_TRIVIAL(error) << "Reconnect attempt...(read) ";
      // close and try to reconnect
      open();
      return read( buffer ); // try again for at least MAX_ATTEMPTS
    } 
  }
  return bytes_rec;

}
int BlueComm::has_data(){

  if(_is_open) {
    return recv( sock, 0, 0, MSG_PEEK );
  }
  return -1;
}
int BlueComm::write( std::string &msg) {

  int bytes_sent=-1;

  if(_is_open) {
    bytes_sent = send(sock,msg.c_str(),msg.size(),0);
    if( bytes_sent < 0) {
      BOOST_LOG_TRIVIAL(error) << "Reconnect attempt....(write)" ;
      open();
      return write( msg ); // try again for at least MAX_ATTEMPTS
    } 
  }
  return bytes_sent;
}
BlueComm::~BlueComm(){
  close_it();
}


