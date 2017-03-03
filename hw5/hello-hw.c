   #include <pthread.h>
   #include <stdlib.h>
   #include <stdio.h>  
   #include <string.h>
   #define NUM_THREADS 8
   char *messages[NUM_THREADS];
   
   typedef struct  s_sst{
       int sum;
       char txt[30];
       int tid;
   } sst; 

   void *PrintHello(void *threadarg)
    {
     int taskid, sum;
     char hello_msg[9];
     /* ... */
     sst * info = (sst *)threadarg; 
     strcpy(hello_msg,info->txt); 
     sum = info->sum; 
     taskid = pthread_self(); 
     /* ... */
     printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
     pthread_exit(NULL);
    }

   int main(int argc, char *argv[])
    {
     pthread_t threads[NUM_THREADS];
     pthread_attr_t attr;
     pthread_attr_init(&attr); 
     sst * threadinfo = malloc(sizeof(sst)); 
     int rc, t, sum;
     sum=0;
     
     messages[0] = "Hello-0";
     messages[1] = "Hello-1";
     messages[2] = "Hello-2";
     messages[3] = "Hello-3";
     messages[4] = "Hello-4";
     messages[5] = "Hello-5";
     messages[6] = "Hello-6";
     messages[7] = "Hello-7";
     for(t = 0; t < NUM_THREADS; t++)
      {
       sum = sum + t;
       /* ... */
       printf("Creating thread %d\n", t);
       
      threadinfo->sum = sum;  
      strcpy(threadinfo->txt,messages[t]);
      pthread_create(&threads[t],NULL, PrintHello, threadinfo);
      pthread_join(threads[t], NULL);
       /* ... */
      }
     pthread_exit(NULL);
    }
