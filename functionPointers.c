#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sine(double, double (*fx)(double));


int main(void)
{
      double input, output;
      input = .5;
      output = sine(input, &sin);
      printf("did it work? %f\n", output); 
}

double sine(double x, double (*fx)(double))
{
      float y;
      y = fx(x);
      return y;
}
