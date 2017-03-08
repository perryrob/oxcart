/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <cassert>
#include <cstring>
#include <iostream>
#include "algo/checksum.h"

using namespace std;

int main(int argc, char *argv[] ) {

  string msg("GPRMC,003300.000,A,3213.4184,N,11055.7477,W,0.01,211.62,080217,,,D");
  Checksum c(msg);

  cerr <<  c.get_sentence();

  string test( "$GPRMC,003300.000,A,3213.4184,N,11055.7477,W,0.01,211.62,080217,,,D*7B\r\n" );

  for(unsigned int i=0; i < msg.length(); ++i ) {
    if( msg[i] != test[i] ) {
      cerr << msg[i] << " " << test[i] << " " << i << endl;
    }
  }

  assert( c.get_sentence() == test );

  string s("PGRMZ,759.3,f,1");
  string ss("$PGRMZ,759.3,f,1*0F\r\n");
  Checksum sss(s);
  cerr << sss.get_sentence();
  assert(sss.get_sentence() == ss);

  return 0;
}
