
#include "oxapp.h"
#include "devices/LSM6.h"

#include <math.h>
#include <iostream>

#include "trivial_log.h"

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes
#define DS33_SA0_HIGH_ADDRESS 0b1101011
#define DS33_SA0_LOW_ADDRESS  0b1101010

#define TEST_REG_ERROR -1

#define DS33_WHO_ID    0x69

const double GRAVITY = 9.80665;

// Constructors ////////////////////////////////////////////////////////////////

LSM6::LSM6()  : OxI2CDevice( "LSM6DS33")
{
  _device = device_auto;
  callibrated = false;
  io_timeout = 0;  // 0 = no timeout
  did_timeout = false;

  a_bias.x = 0.0;
  a_bias.y = 0.0;
  a_bias.z = 0.0;
  g_bias.x = 0.0;
  g_bias.y = 0.0;
  g_bias.z = 0.0;

  a_mag = 0.0;

}

// Public Methods //////////////////////////////////////////////////////////////

// Did a timeout occur in readAcc(), readGyro(), or read() since the last call to timeoutOccurred()?
bool LSM6::timeoutOccurred()
{
  bool tmp = did_timeout;
  did_timeout = false;
  return tmp;
}

void LSM6::setTimeout(uint16_t timeout)
{
  io_timeout = timeout;
}

uint16_t LSM6::getTimeout()
{
  return io_timeout;
}

bool LSM6::init(deviceType device, sa0State sa0)
{

  // perform auto-detection unless device type and SA0 state were both specified
  if (device == device_auto || sa0 == sa0_auto)
  {
    // check for LSM6DS33 if device is unidentified or was specified to be this type
    if (device == device_auto || device == device_DS33)
    {
      // check SA0 high address unless SA0 was specified to be low
      if (sa0 != sa0_low && testReg(DS33_SA0_HIGH_ADDRESS, WHO_AM_I) == DS33_WHO_ID)
      {
        sa0 = sa0_high;
        if (device == device_auto) { device = device_DS33; }
      }
      // check SA0 low address unless SA0 was specified to be high
      else if (sa0 != sa0_high && testReg(DS33_SA0_LOW_ADDRESS, WHO_AM_I) == DS33_WHO_ID)
      {
        sa0 = sa0_low;
        if (device == device_auto) { device = device_DS33; }
      }
    }

    // make sure device and SA0 were successfully detected; otherwise, indicate failure
    if (device == device_auto || sa0 == sa0_auto)
    {
      return false;
    }
  }

  _device = device;

  switch (device) {
  case device_DS33:
    address = (sa0 == sa0_high) ? DS33_SA0_HIGH_ADDRESS : DS33_SA0_LOW_ADDRESS;
    break;
  case device_auto:
    break;
  }

  enableDefault();

  return true;
}

/*
Enables the LSM6's accelerometer and gyro. Also:
- Sets sensor full scales (gain) to default power-on values, which are
  +/- 2 g for accelerometer and 245 dps for gyro
- Selects 1.66 kHz (high performance) ODR (output data rate) for accelerometer
  and 1.66 kHz (high performance) ODR for gyro. (These are the ODR settings for
  which the electrical characteristics are specified in the datasheet.)
- Enables automatic increment of register address during multiple byte access
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
void LSM6::enableDefault(void)
{
  if (_device == device_DS33)
  {
    // Accelerometer

    // 0x80 = 0b10000000
    // 0x98 = 0b10011000 4g, fast 6.66 kHz (high performance)
    
    writeReg(CTRL1_XL, 0x98);

    // Gyro

    // 0x80 = 0b010000000
    // ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (245 dps)
    writeReg(CTRL2_G, 0x80);

    // Common

    // 0x04 = 0b00000100
    // IF_INC = 1 (automatically increment register address)
    writeReg(CTRL3_C, 0x04);
  }
}

void LSM6::writeReg(uint8_t reg, uint8_t value)
{
  Wire->beginTransmission(address);
  Wire->write(reg);
  Wire->write(value);
  last_status = Wire->endTransmission();
}

uint8_t LSM6::readReg(uint8_t reg)
{
  uint8_t value;

  Wire->beginTransmission(address);
  Wire->write(reg);
  last_status = Wire->endTransmission();
  Wire->requestFrom(address, (uint8_t)1);
  value = Wire->read();
  Wire->endTransmission();

  return value;
}

// Reads the 3 accelerometer channels and stores them in vector a
void LSM6::readAcc(void)
{
  Wire->beginTransmission(address);
  // automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
  Wire->write(OUTX_L_XL);
  Wire->endTransmission();
  Wire->requestFrom(address, (uint8_t)6);

  uint16_t millis_start = millis();
  while (Wire->available() < 6) {
    if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout)
    {
      did_timeout = true;
      return;
    }
  }

  uint8_t xla = Wire->read();
  uint8_t xha = Wire->read();
  uint8_t yla = Wire->read();
  uint8_t yha = Wire->read();
  uint8_t zla = Wire->read();
  uint8_t zha = Wire->read();

  // combine high and low bytes
  a.x = (int16_t)(xha << 8 | xla);
  a.y = (int16_t)(yha << 8 | yla);
  a.z = (int16_t)(zha << 8 | zla);

  if (callibrated) {
    a.x = a.x - a_bias.x ;
    a.y = a.y - a_bias.y ;
    a.z = a.z ;// Just assume that Z is the magnitude of a_mag
  }
}

// Reads the 3 gyro channels and stores them in vector g
void LSM6::readGyro(void)
{
  Wire->beginTransmission(address);
  // automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
  Wire->write(OUTX_L_G);
  Wire->endTransmission();
  Wire->requestFrom(address, (uint8_t)6);

  uint16_t millis_start = millis();
  while (Wire->available() < 6) {
    if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout)
    {
      did_timeout = true;
      return;
    }
  }

  uint8_t xlg = Wire->read();
  uint8_t xhg = Wire->read();
  uint8_t ylg = Wire->read();
  uint8_t yhg = Wire->read();
  uint8_t zlg = Wire->read();
  uint8_t zhg = Wire->read();

  // combine high and low bytes
  g.x = (int16_t)(xhg << 8 | xlg);
  g.y = (int16_t)(yhg << 8 | ylg);
  g.z = (int16_t)(zhg << 8 | zlg);

  if (callibrated) {
    g.x = g.x - g_bias.x;
    g.y = g.y - g_bias.y;
    g.z = g.z - g_bias.z;
  }

}

// Reads all 6 channels of the LSM6 and stores them in the object variables
void LSM6::read(void)
{
  readAcc();
  readGyro();
}

void LSM6::vector_normalize(vector<float> *a)
{
  float mag = sqrt(vector_dot(a, a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}

void LSM6::callibrate() {  
  int SAMPLES = 10;

  for( int i=0; i < SAMPLES; ++i ) {
    readGyro();
    g_bias.x += g.x;
    g_bias.y += g.y;
    g_bias.z += g.z;
  }

  for( int i=0; i < SAMPLES; ++i ) {
    readAcc();
    a_bias.x += (double)a.x;
    a_bias.y += (double)a.y;
    a_bias.z += (double)a.z;
  }
  g_bias.x = (double)g_bias.x / (double)SAMPLES;
  g_bias.y = (double)g_bias.y / (double)SAMPLES;
  g_bias.z = (double)g_bias.z / (double)SAMPLES;

  a_bias.x = (double)a_bias.x / (double)SAMPLES;
  a_bias.y = (double)a_bias.y / (double)SAMPLES;
  a_bias.z = (double)a_bias.z / (double)SAMPLES;

  
  a_mag = sqrt(  a_bias.x * a_bias.x +  a_bias.y * a_bias.y  + a_bias.z * a_bias.z );

  BOOST_LOG_TRIVIAL(debug) << a_mag;

  double pitch = atan2(a_bias.x/a_mag, sqrt(a_bias.y/a_mag * a_bias.y/a_mag) + (a_bias.z/a_mag * a_bias.z/a_mag));
  double roll = atan2(a_bias.y/a_mag, sqrt(a_bias.x/a_mag * a_bias.x/a_mag) + (a_bias.z/a_mag * a_bias.z/a_mag));

  BOOST_LOG_TRIVIAL(debug) << "pitch: " << pitch  * 180.0 / M_PI;
  BOOST_LOG_TRIVIAL(debug) << "roll: " << roll  * 180 / M_PI;

  BOOST_LOG_TRIVIAL(debug) << a_mag * sin( pitch );
  BOOST_LOG_TRIVIAL(debug) << a_mag * sin( roll );

  a_bias.x -= a_mag * sin( pitch );
  a_bias.y -= a_mag * sin( roll );
  
  a_mag /= GRAVITY;
  
  BOOST_LOG_TRIVIAL(debug) << a_bias.x  ;
  BOOST_LOG_TRIVIAL(debug) << a_bias.y  ;

  callibrated = true;
}


void LSM6::rw_device() {

  if (is_device_failed()) {
    BOOST_LOG_TRIVIAL(warning) <<"Offline Device: "<< get_name();
    return;
  }

  if (! init() ) {
    BOOST_LOG_TRIVIAL(error) <<"** Device FAILED: "<<get_name();
    set_device_failed();
    return;
  }

  if (! callibrated) {
    callibrate();
  }

  readAcc();
  OxApp::l_accel->set_val(X,(double)a.x / a_mag); 
  OxApp::l_accel->set_val(Y,(double)a.y / a_mag);
  OxApp::l_accel->set_val(Z,(double)a.z / a_mag);
  readGyro();
  OxApp::l_gyro->set_val(X,(double)g.x * 8.75 / 1000.0 * M_PI / 180.0); // rad/s at 245 max dps
  OxApp::l_gyro->set_val(Y,(double)g.y * 8.75 / 1000.0 * M_PI / 180.0);
  OxApp::l_gyro->set_val(Z,(double)g.z * 8.75 / 1000.0 * M_PI / 180.0);

  
}



// Private Methods //////////////////////////////////////////////////////////////

int16_t LSM6::testReg(uint8_t address, regAddr reg)
{

  Wire->beginTransmission(address);
  Wire->write((uint8_t)reg);
  if (Wire->endTransmission() != 0)
  {
    return TEST_REG_ERROR;
  }

  Wire->requestFrom(address, (uint8_t)1);

  if (Wire->available())
  {
    return Wire->read();
  }
  else
  {
    return TEST_REG_ERROR;
  }
}
