#include <pthread.h>
#include <inttypes.h>
#include <stdlib.h>   
#include <stdio.h>
#define NUMTHRDS 4
#define VECLEN 100000
   pthread_t callThd[NUMTHRDS];
   double *array_a;
   double *array_b;
   double big_sum;
   int veclen;

   // I don't think this will be needed since arrays are global 
   // stuct won't need to be passed
   typedef struct s_dvec{
   double ax;
   double bx;
   double ay;
   double by; 
   } dvec;
   

    void *dotprod(void *arg)
    {
     /* ... */
     double * x = array_a;
     double * y = array_b;
     int i;
     /* ... */
     long mysum = 0;
     for (i=0; i<NUMTHRDS*VECLEN ; i++)
      {
       mysum += (x[i] * y[i]);
      }
     /* ... */
     int * bigsum = (int *)  mysum;
     pthread_exit(bigsum);
     /* ... */
    }
   int main (int argc, char *argv[])
    {
     long i;
     double *a, *b;
     void *status;
     a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
     b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
     for (i=0; i<VECLEN*NUMTHRDS; i++)
      {
       a[i]=1;
       b[i]=a[i];
      }
     veclen = VECLEN;
     array_a = a;
     array_b = b;
     big_sum = 0;
     /* ... */
     /* create threads */
     /* ... */
     void * sum; 
     for(i=0;i<NUMTHRDS;i++)
      {
       /* Each thread works on a different set of data.
          The offset is specified by 'i'. The size of
          the data for each thread is indicated by VECLEN.
       */
          pthread_create(&callThd[i],NULL,dotprod,NULL);
          pthread_join(callThd[i],&sum); 
          big_sum += (intptr_t) sum;
      }
     /* Wait on the other threads */
     /* ... */
     printf ("Sum = %f \n", big_sum);
     free (a);
     free (b);
    }
