 #include "csapp.h"
int main(int argc, char **argv)
{
	int  f; 
    printf("argc = %d\n" , argc); 
    int n;
	rio_t rio;
	

    if (argc > 1){
        f = Open(argv[1], O_RDONLY, 0 );
        Dup2(f, STDIN_FILENO);
    }
    
    char buf[MAXLINE];
	Rio_readinitb(&rio, STDIN_FILENO);
 	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
 		Rio_writen(STDOUT_FILENO, buf, n);

    Close(f);
}

