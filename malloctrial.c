#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp(const int *a, const int *b)
{
      if(*a==*b)
            return 0;
      else
            if(*a<*b)
                  return -1;
            else
                  return 1;
}

int main (int argc, char* argv[])
{
      int *j, i;
      int N = 5;
      int *A = (int *)malloc(N * sizeof(int));
      int B[] = {5, -3, 1, 0, -1};
      FILE *mule;
      mule = fopen("mule", "wt");
      fprintf(mule, "what the fucking hell!!\n");

      for(i=0, j = A; i<5; i++, j++)
      {
            A[i] = B[i];
            printf("%i is my value\n", A[i]);
      }
      qsort(A, N, sizeof(int), (void *)comp);
      printf("%i is the smallest\n", A[0]);
      printf("%i is the largetst\n", A[5]);

      fclose(mule);
      return 0;
}
