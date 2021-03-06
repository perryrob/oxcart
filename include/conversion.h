/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/
#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <cmath>

class Conv {

 public:
  static inline double knots( double mps ) {
    return 1.943842816446084 * mps;
  }

  static inline double knots2ms( double k ) {
    return k / 1.943842816446084;
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

  static inline double rad2deg( double m ) {
    return m * 180.0 / M_PI;
  }
  static inline double deg2rad( double m ) {
    return m * M_PI / 180.0 ;
  }  

};
#endif
