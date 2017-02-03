#include "oxapp.h"
#include "algo/MadgwickAHRS.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[] ) {

  Madgwick mw;

  for( uint64_t i = 0; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *2.0,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               360.0 / 9.5 * 3.14159 /180.0,
               25.7);
  }
  double roll60 = mw.getRoll();
  double gps60 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *2.0,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               -360.0 / 9.5 * 3.14159 /180.0,
               25.7);
  }
  double mroll60 = mw.getRoll();
  double mgps60 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *1.414,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               360.0 / 16.5 * 3.14159 /180.0,
               25.7);
  }
  double roll45 = mw.getRoll();
  double gps45 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *1.414,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               -360.0 / 16.5 * 3.14159 /180.0,
               25.7);
  }
  double mroll45 = mw.getRoll();
  double mgps45 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *1.2,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               360.0 / 28.6 * 3.14159 /180.0,
               25.7);
  }
  double roll30 = mw.getRoll();
  double gps30 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *1.2,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               -360.0 / 28.6 * 3.14159 /180.0,
               25.7);
  }
  double mroll30 = mw.getRoll();
  double mgps30 = mw.getGPSRoll();
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( -1.21869,
               0.0852967,
               9.8056 *1.0,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               0.0,
               25.7);
  }
  cerr << mw.getRoll() << " " << mw.getGPSRoll() << " " << 0 << endl;
  cerr << roll30  << " " << gps30 << " " << 30 << endl;
  cerr << mroll30  << " " << mgps30 << " " << -30 << endl;
  cerr << roll45  << " " << gps45 << " " << 45 << endl;
  cerr << mroll45  << " " << mgps45 << " " << -45 << endl;
  cerr << roll60  << " " << gps60 << " " << 60 << endl;
  cerr << mroll60  << " " << mgps60 << " " << -60 << endl;
  assert( fabs(mw.getRoll() - mw.getGPSRoll()) < 1.0 );
  assert( fabs( roll30 - gps30 ) < 1.0 );
  assert( fabs( mroll30 - mgps30 ) < 1.0 );
  assert( fabs( roll45 - gps45 ) < 1.0 );
  assert( fabs( mroll45 - mgps45 ) < 1.0 );
  assert( fabs( roll60 - gps60 ) < 1.0 );
  assert( fabs( mroll60 - mgps60) < 1.0 );

  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( 0.0,
               0.0,
               0.0,
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               0.0,
               25.7);
  }
  cerr << mw.getRoll() << " " << mw.getGPSRoll() << " " << 0 << endl;
  assert( fabs(mw.getRoll() - mw.getGPSRoll()) < 1.0 );
  mw.reset();
  for( uint64_t i = 1000; i < 5000; i = i + 100) {
    mw.begin( i );
    mw.update( 1.2,
               0.0852967,
               sqrt(9.8056 * 9.8056 + 2.5 * 2.5),
               -0.0105374,
               0.00137445,
               0.00503964,
               0.770681,
               -0.46273,
               -0.15551,
               0.0,
               25.7,
               2.5); // sent in from GPS
  }
  cerr << mw.getRoll() << " " << mw.getGPSRoll() << " " << mw.getPitch() << endl;
  assert( mw.getPitch() < - 7.5 );
  return 0;
}
