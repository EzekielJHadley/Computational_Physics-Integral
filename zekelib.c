#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int diffCent(double *,double *,int,double);
double intgTrap(double (*fp)(double), double,double, int);
double intgAdaptTrap(double (*fp)(double), double, double, int);
double intgSimp(double (*fp)(double), double, double, int);
double comp(const double *,const double *);
double fltmax(double[],int);
double delta(double[],double[],double *,int);
double error(double[],double[],int);


int diffCent(double *a, double *ap, int N, double h)
{
      int i;
      //double *j;
      
      //do this first, so that the first part
      //of the array is given a value
      ap[0] = (-((a[2]))-(a[0])*3+(a[1])*4)/(2.0*h);
      //ap++; //don't forget to go to the next memory point

      //do the central difference derivative
      //w/out the end points
      for(i=1; i<(N-1); i++) //i can increment the pointer like this because the sizes are the same
      {     
            ap[i] = ((a[i+1]) - (a[i-1]))/(2.0*h);
      }

      //now i need to find the derivative at the dn points
      //ap++;//go to the last memory point
      ap[N-1] = ((a[N-1])*3-((a[N-2]))*4+(a[N-3]))/(2.0*h);

      return 0;
}

//integration using the trapazoid rule
//i take in the function to integrate, the range of integration
//the number of steps of the function, and out put to an array
double intgTrap(double (*fp)(double), double a, double b, int N)
{
      double h = (b-a)/(double)(N);;
      double fnc[N+1], Fx=0;
      int i;
      //set up an array for the function to be integrated
      for(i=0; i<=N; i++)
      {
            fnc[i] = fp(a + i*h);
      }
      
      //now stat integrating
      for(i=0; i<=N; i++)
      {
            if(i==0)
                  Fx += .5 * fnc[0] * h;
            else if(i == N)
                  Fx += .5 * fnc[N] * h;
            else
                  Fx += fnc[i] * h;
      }
      return Fx;
}

//i will now make an addaptive trapazoid integration routine
//it uses recursion and conpares the new interval versus the old interval
//against a tollerance
double intgAdaptTrap(double (*fp)(double), double a, double b, int prec)
{
      //set up the tollerance and the output for the integral and the old value
      double TOL = pow(10, prec), output=0, old, new;
      //the old and new step size, pluss the center point
      double h1 = b-a, h2 = (b-a)/2.0, c = (a+b)/2.0;

      //now calulate the integral over the old integral
      old = h1/2.0*(fp(a) + fp(b));
      new = h2*(fp(a)/2.0 + fp(c) + fp(b)/2.0);
      if(fabs(old - new) > TOL)
      {
            output += intgAdaptTrap( fp, a, c, prec);
            output += intgAdaptTrap( fp, c, b, prec);
            return output;
      }
      else
      {
            return new;
      }
}

//now i will do a 3rd order integral using Simpson's rule
//same as the trapazoid rule input
double intgSimp(double (*fp)(double), double a, double b, int N)
{
      //make sure N is even
      if((N%2) != 0)
            N++;
      double h = (b-a)/(double)(N);;
      double fnc[N+1], Fx=0;
      int i;
      //set up an array for the function to be integrated
      for(i=0; i<=N; i++)
      {
            fnc[i] = fp(a + i*h);
      }
      
      //now stat integrating
      for(i=0; i<N; i += 2)
      {
            Fx += h/3.0*(fnc[i] + 4*fnc[i+1] + fnc[i+2]);
      }
      return Fx;
}



//this is needed for qsort to work...don't know why (magic?)
double comp(const double *a, const double *b)
{
      if(*a == *b) return 0;
      if(*a < *b) return -1;
      else return 1;
}

//i was going to use qsort, but it seems like this will be faster
//so i will jsut go through the array and do it that way
double fltmax(double A[], int size)
{     
      double max=fabs(A[0]);
      int i;

      for( i=1; i<size; i++)
      {
            //if the next number is bigger put it in max, else move along
            if(max < fabs(A[i]))
            {
                  max = fabs(A[i]); 
            }
      }
      return max;
}

double delta(double final[], double initial[], double *delta, int size)
{
      int i;
      for( i=0; i<size; i++)
      {
            delta[i] = final[i] - initial[i];
      }
      return 0;
}

double error(double comp[], double exact[], int size)
{
      double del[size], error, max, denominator;
      delta(comp, exact, &del[0], size);
      max = fltmax(del, size);
      denominator = fltmax(exact, size);
      error = max/denominator;
      return error;
}

double rootB(double (*fn)(double), double a, double b)
{
      double c = 0, TOL = .0001;
      //make sure that the end points are not zeros
      if(fabs(fn(a)) < TOL)
            return a;
      if(fabs(fn(b)) < TOL)
            return b;
      //now check that there is a zero in the interval
      //if there is an even number it will think there are none
      while( fn(a)*fn(b) > 0)
      {
            c = (a + b)/2.0;
            if( fn(a)*fn(c) < 0)
                  b = c;
            else
                  a = c;
            printf("There are zero or more than one root in between this interval.\n");
            printf("Changeing interval to %.8e, %.8e\n", a, b);
            if(fabs(a-b) < TOL)
            {
                  printf("There is no zero in that interval\n");
                  return 0;
            }
      }
      
      //now keep bisecting the interval until a zero is found
      while(1)
      {
            c = (a+b)/2.0;
            if(fabs(fn(c)) < TOL)
                  return c;
            //now determin which half the zero is in
            //and make that the new interval
            if( fn(a)*fn(c) < 0)
                  b = c;
            else
                  a = c;
      }
}

//this is the Newton-rapson method
//uses a range and a best guess
double rootNR(double (*fn)(double), double guess)
{
      double TOL = pow(10, -12);
      int N = 32, i, j=50;
      double h = 1/(double)(N), fd[N+1], fp[N+1] ;
      if(fabs(fn(guess)) < TOL)
            return guess;
      //now i need to descrettize the function
      // so i can take a derivative of it around the guess
      while(j>=0)
      {
            for(i = -N/2; i <= N/2; i++)
            {
                  fd[i + N/2] = fn(guess + i*h);
            }
            diffCent(&fd[0], &fp[0], N, h);
            //now make a new guess
            guess = guess - fn(guess)/fp[N/2];
            if(j==0)
            {
                  printf("Iteration over load, might not have a zero\n");
                  return 0;
            }
            if(fabs(fn(guess)) < TOL)
                  return guess;
            j--;
      }
}
