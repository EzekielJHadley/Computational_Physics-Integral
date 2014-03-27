#include <stdio.h>
#include <math.h>
#include "zekelib.c"

double enrgySym(double x)
{
      double V0 = -200;
      double output = sqrt(V0*V0 - x*x)-x*tan(x);
      return output;
}


double enrgyAnti(double x)
{
      double V0 = 5;
      double output = sqrt(V0*V0 - x*x)+x/tan(x);
      return output;
}

int main(void)
{
      double zero1, zero2;
      zero1 = rootB(&enrgySym, 6, 7.85);
      zero2 = rootNR(&enrgySym, zero1);
      printf("One of the roots is %.10e or %.2e\n", zero1, zero2);
     
      
      zero1 = rootB(&enrgySym, 22.4, 23.45);
      zero2 = rootNR(&enrgySym, zero1);
      printf("One of the roots is %.10e or %.10e\n", zero1, zero2);
 
      return 0;
}
