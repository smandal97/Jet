
#include "../paul.h"

static double T_MIN = 0.0; 
static double rho   = 0.0;

void setICparams( struct domain * theDomain ){
   T_MIN = theDomain->theParList.t_min;
   rho = 1.;
}
 
void initial( double * prim , double * x ){

   double r  = x[0];
   double t  = T_MIN;

   double rho,v;
   v = r/t;
   rho = 5e-2 * pow(t,-3.);

   prim[RHO] = rho;
   prim[PPP] = 1e-6*rho;
   prim[UU1] = v;//1./(t/r+7e-1);
   prim[UU2] = 0.0;

   if( NUM_N > 0 ) prim[NUM_C] = 0.;

}
