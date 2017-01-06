/*
 * arduino_wire.h
 *
 *  Created on: Apr 4, 2016
 *      Author: mario
 *      Modified by: perryr
 */

#ifndef ARDUINOWIRE_H_
#define ARDUINOWIRE_H_

#define BUFFER_LENGTH 32
#include <unistd.h>
#include <stdint.h>
#include <cstddef>
#include <deque>

class ArduinoWire {

 private:
	int fd;               //File descriptor used to access i2c device
    static char * i2c_bus;
    
	uint8_t txAddress;
	std::deque<uint8_t> txBuffer;

	std::deque<uint8_t> rxBuffer;

	bool activeDevice;
	bool is_master;


public:
	ArduinoWire();
	ArduinoWire(const char * bus);

	/**
	 * Opens the i2c device
	 */
	void begin();
	void begin(const uint8_t deviceAddress);

	/**
	 * Begin a transmission to the I2C slave device with the given address.
	 * Subsequently, queue bytes for transmission with the write() function and
	 * transmit them by calling endTransmission().
	 *
	 * Input values:
	 * 		@param deviceAddress the address of the i2c slave device
	 */
	void beginTransmission(const uint8_t deviceAddress);

	/**
	 *
	 */
	size_t write(const uint8_t registerAddress);
	size_t write(const uint8_t * registerAddress, size_t size);

	/**
	 * Ends a transmission to the slave device
	 *
	 * Input values:
	 * 		@param releaseDevice True, sends stop message, 
     *    releasing the bus after transmission. False, sends a restart
	 * 		       keeping the connection active.
	 *
	 * @return
	 * 		byte, which indicates the status of the transmission:
	 *			0:success
	 *			1:data too long to fit in transmit buffer
	 *			2:received NACK on transmit of address
	 *			3:received NACK on transmit of data
	 *			4:other error
	 */
	int endTransmission(unsigned char = true);

	/**
	 * Used to request bytes from a slave device, given by . The bytes may 
     * then be retrieved with the available() and read() functions.
	 */
	int requestFrom(int address, unsigned int read_len, bool releaseBus = true);
	int available();
	uint8_t read();
    /**
	uint8_t* toString() {
	  return txBuffer.data();
	}
    */
    ~ArduinoWire(){
      close( fd );
      ArduinoWire::i2c_bus = 0;
    }
};

#endif /* ARDUINOWIRE_H_ */
