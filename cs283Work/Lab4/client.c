#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

     
typedef struct sockaddr_in Server;

int createSocket_d();
Server connectSocket(int socket_d, int port, char* ip);
void sendData(int socket_d, char* file, char* hostname);

int main(int argc, char  *argv[])
{
    char ip[100];
    struct hostent *host;
    struct in_addr **addr_l;
    
    if ((host = gethostbyname( argv[1] )) == NULL){
        printf("%s\n" ,"Failed to get host");
    }

    addr_l = (struct in_addr **) host->h_addr_list;

    for(int i = 0; addr_l[i] != NULL; i++){
        strcpy(ip, inet_ntoa(*addr_l[i]));
    }

	int port = atoi(argv[2]);
	port = 80;
    int socket_d = createSocket_d(); // Create Socket
    
    // Connect socket to server. 
    connectSocket(socket_d, port, ip);

    sendData(socket_d, argv[3], argv[1]);
    return 0;
}

void sendData(int socket_d, char* file, char* hostname){
    char message[1000];
    char hm[100];
    strcpy(hm, "Host: ");
    strcpy(message,"GET /");
    strcat(message, file);
    strcat(message, " HTTP/1.1\r\n");
    strcat(message, strcat(hm ,strcat(hostname, "\r\n\r\n")));
    //strcpy(message, "GET /index.html HTTP/1.1\r\nHost: www.google.com\r\n\r\n");

    printf("%s\n", message );
    if( send(socket_d, message, strlen(message), 0) < 0){
        printf("%s,\n", "Send Message Failed");
        exit(-2);
    }
    printf("%s\n", "Message Sent!");


    //Receive a reply from the server
    char server_reply[2000];
    if( recv(socket_d, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    puts(server_reply);
     
    return;
}


int createSocket_d(){
    int socket_d = socket(AF_INET, SOCK_STREAM,0);
        if (socket_d == -1){
            printf("Could not create socket");
        }
    return socket_d; 
}

Server connectSocket(int socket_d, int port, char* ip){//int socket_d, char* addr, char* file ){
    //int socket_d;
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip); //Connet to host through IP LONG
    server.sin_family = AF_INET;
    server.sin_port = htons( port );


        //Connect to remote server
    if (connect(socket_d , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("%s\n", "Error Connecting");
        exit(-1);
    }
     
    printf("%s\n","Connected!" );
    return server;
}
