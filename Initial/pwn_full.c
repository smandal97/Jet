
#include "../paul.h"

static double T_MIN = 0.0; 
static double delta = 0.0;

void setICparams( struct domain * theDomain ){
   T_MIN = theDomain->theParList.t_min;
   delta = theDomain->theParList.Explosion_Energy;
}
 
void initial( double * prim , double * x ){

   double m = 0.0;
   double n = 7.0;
   double s = 0.0; 

   double r  = x[0];
   double t  = T_MIN;

   double g = 1.0;
   double q = 1.0;

   double rho1 = pow(r/t/g,-n)*pow(t,-3.);
   double rho2 = q*pow(r,-s);

   double R0 = pow( pow(t,n-3.)*pow(g,n)/q , 1./(n-s) );

   double rho = rho1+rho2;
   if(r<5e-2) rho = pow(5e-2/t/g,-n)*pow(t,-3.);
   double X   = rho1*rho1/(rho1*rho1+rho2*rho2);
   double v   = (r/t)*X;

   if( X < 0.5 ){
      X = 0.0;
   }else{
      X = 1.0;
   }

   double k = 50.0;
   double th = x[1];
   double ptb = delta*sin(k*log(r))*sin(k*th);

   double v0 = pow( r , (s-3.)/(n-3.) );
   if( v0 > r/t ) v0 = r/t;
   double Mach = 30.; //1e3;
   double cs = v0/Mach;

   double Pmin = rho*cs*cs;

   prim[RHO] = rho*exp(0.*ptb);
   prim[PPP] = Pmin;
   prim[UU1] = v;
   prim[UU2] = 0.0;

   if( NUM_N > 0 ) prim[NUM_C] = X;

}
