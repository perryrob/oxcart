/*
 * ArduinoWire.cpp
 *
 * Implementation of the ArduinoWire class
 *
 *  Created on: Apr 4, 2016
 *      Author: mario
 *      Highly modified by perryr
 */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#include "arduino_wire.h"
#include "smbus.h"

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
  
  this->fd = open(this->i2c_bus, O_RDWR);

  if (this->fd < 0) {
    std::cerr<<"Could not open i2c device."<<std::endl;
    exit(1);
  }  

  if (ioctl(this->fd, I2C_SLAVE, address) < 0) {
    std::cerr<<"Could not communicate with slave device at address: "<<txAddress<<std::endl;
    exit(1);
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

  int bytes_written = 0; // used to be set to 1 hmmmmm.
  int res = 0;

  uint8_t reg =  txBuffer[0];

  if ( txBuffer.size() == 1 ) {
    res = i2c_smbus_write_byte(this->fd, reg );
    if (res != 0) {
      std::cerr<<"Byte not written...retcode : "<< res << std::endl;
    }
  }
  else {
    for (unsigned int i=1; i < txBuffer.size(); i++) {
      res += i2c_smbus_write_byte_data(this->fd,reg, txBuffer[i]);
      if (res == 0) {
        ++bytes_written;
      }
      else {
        std::cerr<<"Byte(s) not written...retcode : "<< res << std::endl;
      }
    }
  }
  if (bytes_written != (int)txBuffer.size() ) {
    std::cerr<<"Transmission fail: txBufferLength: "<<txBuffer.size()<<"\t transmitted: "<< bytes_written << std::endl;;
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
      std::cerr<<"read not OK: "<<res<<std::endl;
    }
    
	if (releaseBus) {
	  close( this->fd );
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




