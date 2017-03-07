#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

class Conv {

 public:
  static inline double knots( double mps ) {
    return 1.943842816446084 * mps;
  }

  static inline double inches_merc( double pa ) {
    return 0.0002953 * pa;
  }

  static inline double freq_hz( uint32_t delta_ms ) {
    return 1.0 / delta_ms * 0.001;
  }

  static inline double feet( double m ) {
    return m * 3.28084;
  }

  

};
#endif
