#include "oxapp.h"
#include "algo/linregres.h"
#include <iostream>
#include <cassert>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

using namespace std;

int main(int argc, char *argv[] ) {

  LinRegres l(300); // 300 ms time window

  int count = 0;

  for( int i = 0; i < 1000; i = i + 100 ) {
    OxApp::algo_press->set_val( TE_ALTITUDE ,i);
    cerr << l.update(OxApp::algo_press->get_time( TE_ALTITUDE ),
                     OxApp::algo_press->get_val( TE_ALTITUDE )) << " " << 
      l.get_depth() << endl;

    b::this_thread::sleep(b::posix_time::milliseconds(100));
    if( l.ready() ) {
      count += 1;
      
    }
  }
  assert( count == 7);
  assert ( l.slope() < 1.0 );
  assert ( l.slope() > 0.0 );

  count = 0;

  for( int i = 1000; i >= 0; i = i - 100 ) {
    OxApp::algo_press->set_val( TE_ALTITUDE ,i);
    cerr << l.update(OxApp::algo_press->get_time( TE_ALTITUDE ),
                     OxApp::algo_press->get_val( TE_ALTITUDE )) << " " << 
      l.get_depth() << endl;

    b::this_thread::sleep(b::posix_time::milliseconds(100));
    if( l.ready() ) {
      count += 1;
      
    }
  }

  assert( count == 11);
  assert ( l.slope() > -1.0 );
  assert ( l.slope() < 0.0 );

  return 0;
}
