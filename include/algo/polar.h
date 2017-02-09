#ifndef __POLAR_H__
#define __POLAR_H__

#include <math.h>

static const int DEGREE = 3;
static const int N=24;

// ASW20a m/s
double POLAR[N][2]={
  19.44442765,-1.00,
  20.83331533,-0.75,
  22.22220302,-0.69,
  23.61109071,-0.66,
  24.9999784,-0.66,
  26.38886609,-0.69,
  27.77775378,-0.73,
  29.16664147,-0.79,
  30.55552916,-0.84,
  31.94441685,-0.89,
  33.33330454,-0.96,
  34.72219222,-1.05,
  36.11107991,-1.13,
  37.4999676,-1.23,
  38.88885529,-1.32,
  40.27774298,-1.43,
  41.66663067,-1.55,
  43.05551836,-1.67,
  44.44440605,-1.79,
  45.83329374,-1.92,
  47.22218143,-2.08,
  48.61106911,-2.25,
  49.9999568,-2.45,
  51.38884449,-2.71
};

class Polar {
  
 public:
 Polar() : n(DEGREE) {}
  void calc_poly();
  inline double sink_rate( double airspeed_ms ) {
    if ( airspeed_ms  < 15.0 ) return 0.0;
    double ret_val=0;
    for(int i=0; i <=DEGREE; i++)
      ret_val +=a[i] * pow(airspeed_ms,i);
    return ret_val;
  }
  ~Polar(){}

 private:
  int n; //degree of polynomial
  double a[DEGREE+1];
  
};
#endif
