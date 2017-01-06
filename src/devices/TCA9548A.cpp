
#include "devices/TCA9548A.h"

void TCA9548A::rw_sensor() {
  Wire->beginTransmission(TCA9548A::ADDRESS);
  Wire->write(channel);
  Wire->endTransmission();
}
