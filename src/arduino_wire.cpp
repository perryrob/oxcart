/*
 * ArduinoWire.cpp
 *
 * Implementation of the ArduinoWire class
 * http://stackoverflow.com/questions/9974592/i2c-slave-ioctl-purpose
 *  Created on: Apr 4, 2016
 *      Author: mario
 *      Highly modified by perryr
 */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#include "arduino_wire.h"
// #include "smbus.h"

char * ArduinoWire::i2c_bus = 0;

ArduinoWire::ArduinoWire(): fd(0), txAddress(0), activeDevice(false), is_master(true){}


ArduinoWire::ArduinoWire(const char* bus): fd(0), txAddress(0), activeDevice(true), is_master(true){
  if ( ArduinoWire::i2c_bus == 0 ) {
    ArduinoWire::i2c_bus = const_cast<char *>(bus);
  }
}

void ArduinoWire::begin(){

  txBuffer.clear();
  rxBuffer.clear();

}
void ArduinoWire::begin(const uint8_t address){
  this->begin();
  this->txAddress = address;
}
void ArduinoWire::beginTransmission(const uint8_t address){

  if (this->fd == 0) {
    this->fd = open(this->i2c_bus, O_RDWR);
  }

  if (this->fd < 0) {
    std::cerr << "Could not open i2c device. " << this->fd << std::endl;
  } 

  if (ioctl(this->fd, I2C_SLAVE, address) < 0) {
    std::cerr<<"Could not communicate with slave device at address: "<<txAddress<<std::endl;
  }
  begin(address);
}

size_t ArduinoWire::write(const uint8_t data){
  txBuffer.push_back( data );
  return 1;
}

size_t ArduinoWire::write(const uint8_t * data, size_t size){
	int res = 0;
	for (uint8_t i=0; i<size; i++) {
		res += this->write(data[i]);
	}
	return res;
}

int ArduinoWire::endTransmission(unsigned char stop){

  int bytes_written = 0; 
  int res = 0;

  if ( txBuffer.size() == 0 ) return 0;

  if ( txBuffer.size() == 1 ) {
    res = i2c_smbus_write_byte(this->fd, txBuffer[0] );
    if (res == 0) {
      bytes_written = 1; // Just the control register
    } else {
      int errsv = errno;
      std::cerr<<"Byte not written...retcode : "<< res << " " <<  errsv << std::endl;
      return -1;
    }
  }
  else if ( txBuffer.size() == 2 ) {
    res = i2c_smbus_write_byte_data(this->fd, txBuffer[0], txBuffer[1]);
    if (res == 0) {
      bytes_written = 2;
    }
    else {
      std::cerr<<"Byte(s) not written...retcode : "<< res << std::endl;
      return -1;
    }
  } else {
    uint8_t buff[32];
    for (unsigned int i=1; i < txBuffer.size(); ++i ) {
      buff[i-1] = txBuffer[i];
    }
    res = i2c_smbus_write_i2c_block_data(this->fd,txBuffer[0],txBuffer.size()-1,
                                         buff);
    if (res == 0) {
      bytes_written = txBuffer.size();
    }
    else {
      int errsv = errno;
      std::cerr<<"block Byte(s) not written...retcode : "<< res << " " << 
        errsv << std::endl;
      return -1;
    }
  }
  if (txBuffer.size() > 0 && bytes_written != (int)txBuffer.size() ) {
    std::cerr<<"Transmission fail: txBufferLength: "<<txBuffer.size()<<"\t transmitted: "<< bytes_written << std::endl;;
    return -1;
  }
  return res;
}

int ArduinoWire::requestFrom(int address, unsigned int read_len,
                             bool releaseBus){

    uint8_t reg =  txBuffer[0];
    uint8_t buff[read_len];
    uint8_t res = 0;

    res = i2c_smbus_read_i2c_block_data(this->fd,reg,read_len,buff);

    for(uint8_t i=0;i < read_len; i++) {
      rxBuffer.push_back( buff[i] );
    }
    
    if (res!=read_len) {
      std::cerr<<"read not OK: "<< (int)res <<std::endl;
      return -1;
    }
    
	if (releaseBus) {
	  close( this->fd );
      this->fd = 0;
	}
    
    return rxBuffer.size();
}

int ArduinoWire::available(){
  return rxBuffer.size();
}

uint8_t ArduinoWire::read(){
  if (rxBuffer.size()==0) {
    std::cerr<<"No more data."<<std::endl;
    return 0;
  }
  uint8_t ret_val=rxBuffer[0];

  rxBuffer.pop_front();
  return ret_val;
}




