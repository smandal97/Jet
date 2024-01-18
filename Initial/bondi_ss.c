
#include "../paul.h"

static double mdot = 0.0;
static double G    = 0.0;
static double M    = 0.0;
static double K    = 0.0;
static double gam  = 0.0;

void setICparams( struct domain * theDomain ){
   mdot = 1.0; //4.*M_PI*1e1;
   G    = 1.0;
   M    = 1.0;
   K    = 1e-2;
   gam  = theDomain->theParList.Adiabatic_Index;
}

void initial( double * prim , double * x ){

   double r   = x[0];
   double vr  = -sqrt(2.*G*M/r);
   double rho = mdot/4./M_PI/r/r/fabs(vr);
   double Pp  = K*pow(rho,gam);

   prim[RHO] = rho;
   prim[PPP] = Pp;
   prim[UU1] = vr;
   prim[UU2] = 0.0;

}
