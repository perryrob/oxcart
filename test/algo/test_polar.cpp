/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <cassert>
#include <cstring>
#include <iostream>
#include "algo/polar.h"

using namespace std;

int main(int argc, char *argv[] ) {
  Polar p;

  assert( (1 + p.sink_rate(34)) < 0.1 );

  cerr << p.sink_rate(0.0) << endl;

  return 0;
}
