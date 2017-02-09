#include <cassert>
#include <cstring>
#include <iostream>
#include "algo/polar.h"

using namespace std;

int main(int argc, char *argv[] ) {
  Polar p;
  p.calc_poly();
  assert( (1 + p.sink_rate(34)) < 0.1 );

  cerr << p.sink_rate(0.0) << endl;

  return 0;
}
