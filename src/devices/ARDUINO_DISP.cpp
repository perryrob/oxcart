#include "oxapp.h"
#include "devices/ARDUINO_DISP.h"
#include "devices/TCA9548A.h"
#include <math.h>
#include <string>
#include "trivial_log.h"

ARDUINO_DISP::ARDUINO_DISP()  : OxI2CDevice( "ARDUINO_DISP") {}
/*
void BMP085::write8(uint8_t a, uint8_t d) {
  Wire->beginTransmission(I2CADDR); // start transmission to device 
  Wire->write(a); // sends register address to read from
  Wire->write(d);  // write data
  Wire->endTransmission(); //end transmission
}
*/
void ARDUINO_DISP::rw_device() {
  BOOST_LOG_TRIVIAL(debug) << "start rw_device()";

  Wire->beginTransmission(I2CADDR); // start transmission to device
  Wire->write(LED_1_ON);
  Wire->endTransmission();

  Wire->beginTransmission(I2CADDR);
  Wire->write(LED_2_ON);
  Wire->endTransmission();

  Wire->beginTransmission(I2CADDR);
  Wire->write(LED_3_ON);
  Wire->endTransmission();

  Wire->beginTransmission(I2CADDR);
  Wire->write(LED_1_OFF);
  Wire->endTransmission();

  Wire->beginTransmission(I2CADDR);
  Wire->write(LED_2_OFF);
  Wire->endTransmission();

  Wire->beginTransmission(I2CADDR);
  Wire->write(LED_3_OFF);  
  Wire->endTransmission();
  
  BOOST_LOG_TRIVIAL(debug) << "end rw_device()";
}
