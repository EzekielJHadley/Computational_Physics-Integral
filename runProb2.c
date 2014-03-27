#include<stdio.h>
#include<math.h>
#include"zekelib.c"

double quad(double);

int main(void)
{
      int N, Nmax = pow(2, 27);
      double a=0, b=10;
      double output1, output2, output3, exact = 1-cos(10);
      double error1, error2, error3;
      FILE *file;
      file = fopen("integral", "wt");
      fprintf(file, "#N \t trapazoid \t\t adaptive trapazoid \t\tsimpson's\n");
      for (N = 2; N<=Nmax; N *= 2)
      {
            output1 = intgTrap(&sin, a, b, N);
            output2 = intgAdaptTrap(&sin, a, b, -19);
            output3 = intgSimp(&sin, a, b, N);

            error1 = fabs(output1 - exact) / fabs(exact);
            error2 = fabs(output2 - exact) / fabs(exact);
            error3 = fabs(output3 - exact) / fabs(exact);
            fprintf(file, "%i \t %.8e \t %.8e \t %.8e\n", N, error1, error2, error3);
      }
      return 0;
}

double quad(double x)
{
      double output;
      output = (x-5)*(x-5);

      return output;
}
