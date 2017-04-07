#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char const *argv[])
{
	pthread_t tid;
	int num = atoi(argv[1]);
	int i; 
	for(i=0;i< num;i++){
		Pthread_create(&tid, NULL, thread, NULL);
		Pthread_join(tid, NULL);
	}
	exit(0);
}

void *thread(void *vargp) /* Thread routine */
{
	printf("Hello, world!\n");
	return NULL;
}