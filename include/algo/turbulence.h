#ifndef __FFT_H__
#define __FFT_H__

#include "oxapp.h"
#include "oxalgo.h"
#include <deque>
#include <array>
#include "trivial_log.h"

// https://www.codeproject.com/Articles/9388/How-to-implement-the-FFT-algorithm

static const unsigned int NUM_SAMPLES = 256; // 16**2

#define SWAP(a,b)tempr=(a);(a)=(b);(b)=tempr

class Turbulence :  public OxAlgo {
  
 public:

  Turbulence(); 

  void run_algo();
  bool ready() {return  q_data.size() == NUM_SAMPLES * 2;}
  double freq() { return frequency; }
  double amp() { return amplitude; }
  
  ~Turbulence() { delete data; }
    
 private:

  std::deque<double> q_data;
  double * data;

  double frequency, amplitude;
  
};

#endif
