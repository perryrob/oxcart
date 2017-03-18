
#include "trivial_log.h"
#include "algo/turbulence.h"
#include <cmath>

Turbulence::Turbulence() : OxAlgo("Turbulence",10) {
  data = new double[NUM_SAMPLES*2];
}

void Turbulence::run_algo() {


  if( q_data.size() == NUM_SAMPLES * 2) {
    q_data.pop_front();
    q_data.pop_front();
    q_data.push_back(  OxApp::algo_misc_rate->get_val(LOAD_FACTOR) );
    q_data.push_back(  0.0 );
  } else {
    q_data.push_back(  OxApp::algo_misc_rate->get_val(LOAD_FACTOR) );
    q_data.push_back(  0.0 );
    return;
  }

  for (unsigned int i = 0; i < q_data.size(); ++i ) {
    data[i] = q_data[i];
  }
  
  unsigned long n,mmax,m,j,istep,i,isign;
  double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;

  //isign -> 1 to calculate FFT and -1 to calculate Reverse FFT
  isign = 1;
  //the complex array is real+complex so the array
  //as a size n = 2* number of complex samples
  // real part is the data[index] and the complex part is the data[index+1]
  n=NUM_SAMPLES * 2;
  //binary inversion (note that the indexes
  //start from 0 witch means that the
  //real part of the complex is on the even-indexes
  //and the complex part is on the odd-indexes
  j=0;
  for (i=0;i<n/2;i+=2) {
    if (j > i) {
      //swap the real part
      SWAP(data[j],data[i]);
      //swap the complex part
      SWAP(data[j+1],data[i+1]);
      // checks if the changes occurs in the first half
      // and use the mirrored effect on the second half
      if((j/2)<(n/4)){
        //swap the real part
        SWAP(data[(n-(i+2))],data[(n-(j+2))]);
            //swap the complex part
        SWAP(data[(n-(i+2))+1],data[(n-(j+2))+1]);
      }
    }
    m=n/2;
    while (m >= 2 && j >= m) {
      j -= m;
      m = m/2;
    }
    j += m;
  }
  //Danielson-Lanzcos routine
  mmax=2;
  //external loop
  while (n > mmax) {
    istep = mmax<<  1;
    theta=isign*(2*M_PI/mmax);
    wtemp=sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=sin(theta);
    wr=1.0;
    wi=0.0;
    //internal loops
    for (m=1;m<mmax;m+=2) {
      for (i= m;i<=n;i+=istep) {
        j=i+mmax;
        tempr=wr*data[j-1]-wi*data[j];
        tempi=wr*data[j]+wi*data[j-1];
        data[j-1]=data[i-1]-tempr;
        data[j]=data[i]-tempi;
        data[i-1] += tempr;
        data[i] += tempi;
      }
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
    }
    mmax=istep;
  }
  amplitude = q_data[0];
  frequency = 0.0;
  for (unsigned int i = 1; i < q_data.size(); ++i ) {
    if (data[i] > amplitude )  {
      frequency = (double)i /2.0;
      amplitude = data[i];
    }
  }
}
