/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <cassert>
#include <string>
#include <iostream>
#include "oxalgothread.h"
#include "oxalgo.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include "oxapp.h"

using namespace std;

class TestAlgo : public OxAlgo {
public:

  TestAlgo( const string &name, uint64_t interval ) : OxAlgo( name,interval ),
                                                      count(0) {}

  void run_algo() {
    count = count + 1;
  }
  int count;
  ~TestAlgo(){}
};

int main(int argc, char *argv[] ) {

  TestAlgo algo1("test",100);
  TestAlgo algo2("test",10);

  OxAlgoThread t;

  t.add_algo( &algo1 );
  t.add_algo( &algo2 );

  t.run();
  b::this_thread::sleep(b::posix_time::milliseconds(1000));
  t.stop();
  cerr << algo1.count << " " << algo2.count;
  assert( algo1.count == 10 );
  assert( algo2.count > 90 );
  return 0;

}
