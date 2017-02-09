
#include "algo/polar.h"
#include <cmath>

void Polar::calc_poly() {

//http://www.bragitoff.com/2015/09/c-program-for-polynomial-fit-least-squares/

int i,j,k;
double x[N],y[N];

 for (i=0;i<N;i++)
   x[i] = POLAR[i][0];
 for (i=0;i<N;i++)
   y[i] = POLAR[i][1];

 double X[2*n+1];                        

 for (i=0;i<2*n+1;i++) {
    X[i]=0;
    for (j=0;j<N;j++)
      X[i]=X[i]+pow(x[j],i);
 }
 double B[n+1][n+2]; 

 for (i=0;i<=n;i++)
   for (j=0;j<=n;j++)
     B[i][j]=X[i+j];   

 double Y[n+1];    

 for (i=0;i<n+1;i++) {    
     Y[i]=0;
     for (j=0;j<N;j++)
       Y[i]=Y[i]+pow(x[j],i)*y[j];
 }
 for (i=0;i<=n;i++)
   B[i][n+1]=Y[i]; 

 n=n+1; 

 for (i=0;i<n;i++)
   for (k=i+1;k<n;k++)
     if (B[i][i]<B[k][i])
       for (j=0;j<=n;j++) {
             double temp=B[i][j];
             B[i][j]=B[k][j];
             B[k][j]=temp;
        }

 for (i=0;i<n-1;i++)
   for (k=i+1;k<n;k++) {
        double t=B[k][i]/B[i][i];
        for (j=0;j<=n;j++)
            B[k][j]=B[k][j]-t*B[i][j];
        }
 for (i=n-1;i>=0;i--){
     a[i]=B[i][n];
     for (j=0;j<n;j++)
       if (j!=i) 
         a[i]=a[i]-B[i][j]*a[j];
       a[i]=a[i]/B[i][i];
     }
     /**
     std::cout<<"\nThe values of the coefficients are as follows:\n";
     for (i=0;i<n;i++)
       std::cout<<"x^"<<i<<"="<<a[i]<<std::endl;
     std::cout<<"\nHence the fitted Polynomial is given by:\ny=";
     for (i=0;i<n;i++)
       std::cout<<" + ("<<a[i]<<")"<<"x^"<<i;
     std::cout<<"\n";
     for(double as=19.0; as < 70; as+=1.0) {
        double sr =  a[0]  + a[1] * as + a[2] * as * as + a[3] * as * as *as ;
        std::cout <<  as << " " << sr << " " << fabs(as / sr) << std::endl;
      }
     */
}
