#include <stdio.h>
#include <math.h>
#include "zekelib.c"

double fourier(double);

int main(void)
{
      double a = 0, b = 10;
      double integral, exact = 1 - cos(10);
      double error;
      int prec = -19;

      integral = intgAdaptTrap( &sin, a, b, prec);
      error = fabs(integral - exact) / fabs(exact);
      

      printf("Integral = %.8e +/- %.8e\n", integral, error);
}


double fourier(double x)
{
      double output=0;
      int n, max=100;

      for(n=1; n<max; n++)
            output += 2*pow(-1,n+1)/(double)(n)*sin(n*x);

      return output;
}
