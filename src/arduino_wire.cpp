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
#include "trivial_log.h"
#include "arduino_wire.h"
#include <sstream>

char * ArduinoWire::i2c_bus = 0;

const char * hex( uint8_t v) {
  std::ostringstream convert;
  convert << "0x" << std::uppercase << std::hex << (int)v;
  return convert.str().c_str();
}

ArduinoWire::ArduinoWire(): fd(0), txAddress(0), activeDevice(false), is_master(true), funcs(0) {}


ArduinoWire::ArduinoWire(const char* bus): fd(0), txAddress(0), activeDevice(true), is_master(true), funcs(0){
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
    BOOST_LOG_TRIVIAL(error) << "Could not open i2c device. " << this->fd ;
  } 

  if (ioctl(this->fd, I2C_SLAVE, address) < 0) {
    BOOST_LOG_TRIVIAL(error) << 
      "Could not communicate with slave device at address: "<< hex(txAddress) ;
  }
  if (funcs == 0) {
    if (ioctl(this->fd, I2C_FUNCS, &funcs) < 0) {
      BOOST_LOG_TRIVIAL(info) << 
        "Could not get I2C funcs "<< hex(txAddress) ;
    }
    if (!(funcs & I2C_FUNC_SMBUS_QUICK)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_QUICK "<< hex(txAddress) ;
    }
    if (!(funcs & I2C_FUNC_SMBUS_BYTE)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_BYTE "<< hex(txAddress) ;      
    }
    if (!(funcs & I2C_FUNC_SMBUS_BYTE_DATA)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_BYTE_DATA "<< hex(txAddress) ;      
    }
    if (!(funcs & I2C_FUNC_SMBUS_WORD_DATA)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_WORD_DATA "<< hex(txAddress) ;      
    }
    if (!(funcs & I2C_FUNC_SMBUS_BLOCK_DATA)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_BLOCK_DATA "<< hex(txAddress) ;      
    }
    if (!(funcs & I2C_FUNC_SMBUS_I2C_BLOCK)) {
      BOOST_LOG_TRIVIAL(info) << 
        "NO I2C_FUNC_SMBUS_I2C_BLOCK "<< hex(txAddress) ;      
    }
  }
  begin(address);
}

size_t ArduinoWire::write(const uint8_t data){
  if (txBuffer.size() == 32 ) {
    BOOST_LOG_TRIVIAL(error) << "Over 32 bytes in buffer, ignoring the rest!";
  }
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

  BOOST_LOG_TRIVIAL(debug)  <<  "Address: " << hex(this->txAddress);

  if ( txBuffer.size() == 0 ) return 0;

  if ( txBuffer.size() == 1 ) {
    if (funcs & I2C_FUNC_SMBUS_QUICK) {
      res = i2c_smbus_write_quick(this->fd, txBuffer[0] );
    } else {
      res = i2c_smbus_write_byte(this->fd, txBuffer[0] );
    }
    if (res == 0) {
      BOOST_LOG_TRIVIAL(debug)  << "i2c_smbus_write_byte " << hex(txBuffer[0]);
      bytes_written = 1; // Just the control register
    } else {
      int errsv = errno;
      BOOST_LOG_TRIVIAL(error)  << "Byte not written...retcode : "<< res << " " 
                                <<  errsv ;
      return -1;
    }
  }
  else if ( txBuffer.size() == 2 ) {
    res = i2c_smbus_write_byte_data(this->fd, txBuffer[0], txBuffer[1]);
    if (res == 0) {
      BOOST_LOG_TRIVIAL(debug)  << "i2c_smbus_write_byte_data" <<
        hex(txBuffer[0]) <<
        " " << hex(txBuffer[1]);
      bytes_written = 2;
    }
    else {
      BOOST_LOG_TRIVIAL(error) <<"Byte(s) not written...retcode : "<< res;
      return -1;
    }
  } else {
    uint8_t buff[32];
    for (unsigned int i=1; i < txBuffer.size(); ++i ) {
      buff[i-1] = txBuffer[i];
      BOOST_LOG_TRIVIAL(debug)  << "..." << hex(txBuffer[i]);
    }
    res = i2c_smbus_write_i2c_block_data(this->fd,txBuffer[0],txBuffer.size()-1,
                                         buff);
    if (res == 0) {
      BOOST_LOG_TRIVIAL(debug) <<"i2c_smbus_write_i2c_block_data" << 
        hex(txBuffer[0]);
      bytes_written = txBuffer.size();
    }
    else {
      int errsv = errno;
      BOOST_LOG_TRIVIAL(error) << "block Byte(s) not written...retcode : "<< 
        res << " " << errsv ;
      return -1;
    }
  }
  if (txBuffer.size() > 0 && bytes_written != (int)txBuffer.size() ) {
    BOOST_LOG_TRIVIAL(error) << "Transmission fail: txBufferLength: "<< 
      txBuffer.size()<<"\t transmitted: "<< bytes_written ;
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
      BOOST_LOG_TRIVIAL(error) << "read not OK: "<< (int)res ;
      return -1;
    }
    
	if (releaseBus) {
	}
    
    return rxBuffer.size();
}

int ArduinoWire::available(){
  return rxBuffer.size();
}

uint8_t ArduinoWire::read(){
  if (rxBuffer.size()==0) {
    BOOST_LOG_TRIVIAL(error) << "No more data.";
    return 0;
  }
  uint8_t ret_val=rxBuffer[0];

  rxBuffer.pop_front();
  return ret_val;
}




