
#include "blue_comm.h"
#include "trivial_log.h"

BlueComm::BlueComm(std::string &address, int channel,
                   int max_attempts):sock(0),_is_open(false),
                                     reconnect_attempts(0) {
  MAX_ATTEMPTS=max_attempts;

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

  _is_open = true;

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
    shutdown( sock, SHUT_RDWR );
    _is_open = false;
  }
  
  if(! _is_open && reconnect_attempts < MAX_ATTEMPTS) {
    close();
    BOOST_LOG_TRIVIAL(error) << "Attempting to reconnect: "<<reconnect_attempts;
    ++reconnect_attempts;
    return open();
  } else {
    reconnect_attempts = 0;
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

  int bytes_rec=-1;

  if(_is_open && reconnect_attempts < MAX_ATTEMPTS ) {
    bytes_rec = recv(sock, buffer, sizeof buffer, 0);
    if( bytes_rec < 0) {
      BOOST_LOG_TRIVIAL(error) << "Reconnect attempt: " << bytes_rec ;
      // close and try to reconnect
      close();
      open();
      ++reconnect_attempts;
      return read( buffer ); // try again for at least MAX_ATTEMPTS
    } else {
      reconnect_attempts = 0;
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

  if(_is_open && reconnect_attempts < MAX_ATTEMPTS ) {
    bytes_sent = send(sock,msg.c_str(),msg.size(),0);
    if( bytes_sent < 0) {
      BOOST_LOG_TRIVIAL(error) << "Reconnect attempt: " << bytes_sent ;
      // close and try to reconnect
      close();
      open();
      ++reconnect_attempts;
      return write( msg ); // try again for at least MAX_ATTEMPTS
    } else {
      reconnect_attempts = 0;
    }
  }
  return bytes_sent;
}
BlueComm::~BlueComm(){
  close();
}


