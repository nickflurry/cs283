#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "csapp.h"

typedef struct sockaddr_in Server;
#define	MAXLINE	 8192

int createSocket_d();
void Bind_(int socket_d, Server server);
void getfile(int fd);
void serve(int con_d, char *fname, int fsize);
void get_filetype(char *filename, char *filetype);


void main(int argc, char const *argv[])
{	
	int socket_d, c, con_d;
    Server client;


	int port = atoi(argv[1]);
    socket_d = createSocket_d();

	Server server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	Bind_(socket_d,server);
	listen(socket_d, 3);

    while (1) { //// This starts the infinite listen loop.
        c = sizeof(struct sockaddr_in);
        con_d = Accept(socket_d, (struct sockaddr *) &client, (socklen_t*)&c);
        getfile(con_d);
        Close(con_d);
    }
	/* code */
}

int createSocket_d(){
    int socket_d = socket(AF_INET, SOCK_STREAM,0);
        if (socket_d == -1){
            printf("Could not create socket");
        }
    return socket_d; 
}

void Bind_(int socket_d, Server server){
	if( bind(socket_d,(struct sockaddr *)&server , sizeof(server)) < 0){
    	printf("%s\n","bind failed");
        exit(-4);
	}
	printf("%s\n","bind done");
}

void getfile(int fd){
    rio_t rio; 
    char buf[MAXLINE],method[MAXLINE], uri[MAXLINE], version[MAXLINE];;
    char filename[MAXLINE]; 
    struct stat sbuf;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    printf("%s\n", buf); 
    sscanf(buf, "%s %s %s", method, uri, version); 
   
    strcpy(filename, ".");                           
   	strcat(filename, uri); 
    
    stat(filename, &sbuf);
    puts(uri);
    puts(filename); 
    
    serve(fd,filename,sbuf.st_size);
    
    return;
}

void serve(int con_d, char *fname, int fsize){
    int f_fd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];

//    get_filetype(fname, filetype); 
    sprintf(buf, "HTTP/1.0 200 OK\r\n");    
    sprintf(buf, "%sServer: My Awesome Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, fsize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(con_d,buf,strlen(buf));

    f_fd = Open(fname, O_RDONLY, 0); 
    srcp = malloc(fsize); 
    Rio_readn(f_fd, srcp, fsize); 
    Close(f_fd);
    Rio_writen(con_d, srcp,fsize); 
    free(srcp); 


}

void get_filetype(char *filename, char *filetype) {
    if (strstr(filename, ".html"))
	strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
	strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
	strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mpg"))
    strcpy(filetype, "video/mpg");
    else
	strcpy(filetype, "text/plain");
}  
