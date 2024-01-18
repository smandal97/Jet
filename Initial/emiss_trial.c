
#include "../paul.h"

void setICparams( struct domain * theDomain ){
}


void initial( double * prim , double * x ){

   double r  = x[0];
   double rho = 1.e-5;

   double A = 1.0;
   double cs = 1e-3;
   
   if(r<6.e-6) rho = A;
   double Pp = rho*cs*cs;

   prim[RHO] = rho;
   prim[PPP] = Pp;
   prim[UU1] = 0.0;
   prim[UU2] = 0.0;

   int q;
   for( q=NUM_C ; q<NUM_Q ; ++q ) prim[q] = 0.0;
}


