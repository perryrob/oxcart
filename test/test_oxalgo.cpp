#include <cassert>
#include <string>
#include <iostream>
#include "oxalgo.h"
#include "oxapp.h"

using namespace std;

class TestAlgo : public OxAlgo {
public:

  TestAlgo( const string &name, uint64_t interval ) : OxAlgo( name,interval ),
                                                      count(0) {}

  void run_algo() {
    if (run_it()) {
      count = count + 1;
    }
  }
  int count;
  ~TestAlgo(){}
};

int main(int argc, char *argv[] ) {

  TestAlgo algo("test",100);
  uint64_t start = OxApp::get_time_ms();

  while (true) {
    if (  OxApp::get_time_ms() - start > 1000 ) break;
    algo.run_algo();
  }
  cerr << algo.count << endl;
  assert( algo.count == 11 );
  return 0;

}
