/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "oxi2cbus.h"

/**
#include "LSM6.h"
#include "LIS3MDL.h"
*/

int main(int argc, const char** argv) {

  const char * i2c_bus = "/dev/i2c-2";

  std::cerr << "Creating obj..";
  OxI2CBus i2c = OxI2CBus( i2c_bus );
  std::cerr << "begin...";
  i2c.begin();
  std::cerr << "endTransmission";
  i2c.endTransmission();
  std::cerr << " okdokee..." << std::endl;

  return 0;
}
