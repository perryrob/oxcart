#include "oxapp.h"
#include "algo/MadgwickAHRS.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[] ) {

  Madgwick mw;

  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.68059,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               360.0 / 18.0 * 3.14159 /180.0,
               25.7);
  }
  assert( fabs(mw.getRoll() - 0.453841) < 0.001 );
  assert( fabs(mw.getGPSRoll() - 42.4518) < 0.001 );
  assert( fabs(mw.getPitch() + 7.18518) < 0.001 );
  assert( fabs(mw.getYaw() - 21.8464) < 0.001 );
  
  return 0;
}
