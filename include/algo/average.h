/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __AVERAGE_H__
#define __AVERAGE_H__

#include <deque>

class Average {

 public:

 Average(unsigned int size) : size(size) {}

  int get_depth() { return x_que.size(); }
  
  double get_average() {
    if ( x_que.size() < size ) return 0.0;
    return std::accumulate(x_que.begin(), x_que.end(), 0.0) /
      (double)x_que.size();
  }
  void update( double val ) {
    while( x_que.size() > size ) {
      x_que.pop_front();
    }
    x_que.push_back(val);
  }
 private:
  unsigned int size;
  std::deque<double> x_que;
  
};

#endif
