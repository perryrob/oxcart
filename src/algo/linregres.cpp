/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "algo/linregres.h"
#include <numeric>
#include <limits>
#include "trivial_log.h"

LinRegres::LinRegres( double x_window_ms ): last_p(0.0),last_x(0.0),
                                            x_window_ms(x_window_ms),
                                            a(0.0),q(0.0),r(0.0),h(0.0),
                                            use_filter(false) {}

double LinRegres::slope() {


  if( ! ready() ) return std::numeric_limits<double>::quiet_NaN();

  double avgX = std::accumulate(x_que.begin(), x_que.end(), 0.0) / x_que.size();
  double avgY = std::accumulate(y_que.begin(), y_que.end(), 0.0) / y_que.size();
  
  double numerator = 0.0;
  double denominator = 0.0;

  for(unsigned int i=0; i<x_que.size(); ++i){
    numerator += (x_que[i] - avgX) * (y_que[i] - avgY);
    denominator += (x_que[i] - avgX) * (x_que[i] - avgX);
  }

  double current_slope = numerator / denominator;

  if (use_filter) {
    // http://stackoverflow.com/questions/33384112/kalman-filter-one-dimensional-several-approaches
    last_x = a * last_x;
    last_p = a * last_p * a + q;
    
    double y = current_slope - h*last_x;
    double kg = last_p * h / ( h * last_p * h  + r );

    last_x = last_x + kg * y;
    last_p = (1.0 - kg * h) * last_p;

    return last_x;

  } else {
    return current_slope;
  }
}

void  LinRegres::set_filter(double a,double q,double r,double h){
  this->a=a;
  this->q=q;
  this->r=r;
  this->h=h;
  use_filter = true;
}

bool LinRegres::ready() {
  return (x_que.size() > 1) && ((x_que.back() - x_que.front()) >= x_window_ms);
}

bool LinRegres::update( const double &X, const double &Y) {

  while(ready()) {
    x_que.pop_front();
    y_que.pop_front();
  }
  x_que.push_back( X );
  y_que.push_back( Y );

  return ready();

}
