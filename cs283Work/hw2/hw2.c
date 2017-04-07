#include "csapp.h" 
#include "csapp.c" 
#include <stdlib.h>

int main(){

	int fd1, fd2, fd3;

	fd1 = Open("foo.txt", O_RDONLY, 0);
	fd3 = Open("baz.txt", O_RDONLY, 0);
	fd2 = Open("bar.txt", O_RDONLY, 0);
	printf("fd2 = %d\n", fd2);
	printf("fd3 = %d\n", fd3);
	Close(fd2);
	Close(fd3);
	fd2 = Open("baz.txt", O_RDONLY, 0);
    printf("fd1 = %d\n", fd1);
    printf("fd2 = %d\n", fd2);
	exit(0);
}
