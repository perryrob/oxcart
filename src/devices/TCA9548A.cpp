
#include "devices/TCA9548A.h"

const uint8_t TCA9548A::ADDRESS = 0x70;

void TCA9548A::rw_device() {
  Wire->beginTransmission(TCA9548A::ADDRESS);
  Wire->write(channel);
  Wire->endTransmission();
}
