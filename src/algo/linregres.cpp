#include "algo/linregres.h"
#include <numeric>
#include <limits>
#include "trivial_log.h"

LinRegres::LinRegres( double x_window_ms ): x_window_ms(x_window_ms) {}

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
  return numerator / denominator;
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
