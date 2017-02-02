
#ifndef __LINREGRES_H__
#define __LINREGRES_H__

#include <deque>

class LinRegres {

public:
  LinRegres( double x_window_ms );

  bool ready(); 

  int get_depth() { return x_que.size(); }

  double slope();
  double slope_per_sec() { return slope() * 1000.0; } 
  bool update(const double &X, const double &Y);

  ~LinRegres() {}

private:

  double x_window_ms;
  std::deque<double> x_que;
  std::deque<double> y_que;
  
};


#endif
