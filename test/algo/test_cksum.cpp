#include <cassert>
#include <cstring>
#include <iostream>
#include "algo/checksum.h"

using namespace std;

int main(int argc, char *argv[] ) {
  //$GPRMC,003300.000,A,3213.4184,N,11055.7477,W,0.01,211.62,080217,,,D*7B
  string msg("GPRMC,003300.000,A,3213.4184,N,11055.7477,W,0.01,211.62,080217,,,D");
  Checksum c(msg);
  string test( "$GPRMC,003300.000,A,3213.4184,N,11055.7477,W,0.01,211.62,080217,,,D*7B\r\n" );
  assert( c.get_sentance() == test );
  return 0;
}
