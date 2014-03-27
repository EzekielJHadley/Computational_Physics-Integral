#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zekelib.c"


main(void)
{
      //warning the code is hardwired for the range of [0,1]
      int p=1, i, n=1;
      int N = pow(4,p)+1;
      double twoPi = 8.0*atan(1.0);
      printf("pi = %.8f\n", twoPi/2.0);
      double err, h;
      FILE *tape, *file;
      tape = fopen("prob1a", "wt");
      file = fopen("prob1b", "wt");
      if(tape == NULL || file ==NULL)
            printf("ERROR: files did not open\n");
      //makre sure you can allocate the space
      double *func = (double *)malloc(N * sizeof(double));
      double *funcp = (double *)malloc(N * sizeof(double));
      double *exact = (double *)malloc(N * sizeof(double));


      if (NULL == func || NULL == funcp || NULL == exact)
      {
            printf("Malloc did not work\n");
      }
      else if(0 == func || 0 == funcp || 0 == exact)
      {
            printf("malloc kidna worked\n");
      }
      else
      {     
           // printf("Malloc worked\n");
            for(p=1; p<=14; p++)
            {
                  printf("p is now %i\n", p);
                  //set the new number of 
                  N = pow(4,p) + 1;
                  //set the new spaceing
                  h = 1/((double)(N));
                  printf("h = %.8e\n", h);
                  if(p!=1)
                  {
                        //allocate space for the variables
                        //then check to make sure it worked
                        free(func);
                        free(funcp);
                        free(exact); 
                        func = (double *)malloc(N * sizeof(double));
                        funcp = (double *)malloc(N * sizeof(double));
                        exact = (double *)malloc(N * sizeof(double));
                        if (NULL == func || NULL == funcp || NULL == exact)
                        {
                              printf("ERROR: malloc did not work\n");
                              break;
                        }
                        else if(0 == func || 0 == funcp || 0 == exact)
                        {
                              printf("ERROR: malloc kinda worked\n");
                              break;
                        }
                  }
                  //set up the two functions
                  for(i=0; i<N; i++)
                  {
                        func[i] = sin(twoPi*n*i*h);
                        exact[i] = twoPi*n*cos(twoPi*n*i*h);
                  }
                  //take the derivative
                  diffCent(func, funcp, N, h);
                  //find error between the exact and the calculated
                  err = error(funcp, exact, N);
                  //print the output            
                  fprintf(tape, "%.8e   %.8e\n", err, h);
            }
      }
      // now set N =32 and varry n = 1, 2, 3, 8, 16, 32 ,64
      //allocate space for the variables
      //then check to make sure it worked
      printf("\nWe are not on part b\n");
      N = 32;
      h = 1/(double)(N);
      free(func);
      free(funcp);
      free(exact); 
      func = (double *)malloc(N * sizeof(double));
      funcp = (double *)malloc(N * sizeof(double));
      exact = (double *)malloc(N * sizeof(double));
      if (NULL == func || NULL == funcp || NULL == exact)
      {
            printf("ERROR: malloc did not work\n");
      }
      else if(0 == func || 0 == funcp || 0 == exact)
      {
            printf("ERROR: malloc kinda worked\n");
      }
      for(n=1; n<=64; n = 2*n)
      {
            printf("n is now %i\n", n);
            //now set up the two functions for this set
            for(i=0; i<N; i++)
            {
                  func[i] = sin(twoPi*n*i*h);
                  exact[i] = twoPi*n*cos(twoPi*n*i*h);
            }
            //taket he derivative
            diffCent(func, funcp, N, h);
            //no determine the error
            err = error(funcp, exact, N);
            //now print to file
            fprintf(file, "%.8e  %i\n", err, n);
            
      }

      free(func);
      free(funcp);
      free(exact);
      fclose(tape);
      fclose(file);
      return 0;
}
