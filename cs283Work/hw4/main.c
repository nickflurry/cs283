#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include "csapp.h"

#define MAXBUF   8192 
#define MAXLINE   8192 

char *sreplace(char *orig, char *rep, char *replacetxt);
char *sinsert(char *orig, char *rep, char *replacetxt);

int main(int argc, char const *argv[])
{
  	struct dirent *dp;
  	DIR *dir;
    char fname[100];
    char dfname[100]; 
    int fd;
    char buf[MAXBUF];
    char replace[sizeof(argv[2])]; 
    char rtxt[MAXLINE];
    char find[sizeof(argv[1])];
    char find2[sizeof(argv[3])];
    strcpy(replace, argv[2]);
    strcpy(find,argv[1]);
    strcpy(find2,argv[3]);


	dir = opendir("./sub");
   	while ((dp = readdir(dir)) != NULL){
         strcpy(fname,dp->d_name);
         if(strcmp(fname,"." ) && strcmp(fname,"..") ){ //Checks its not current Dir or parent dir
         	strcpy(dfname,"./sub/");
         	strcat(dfname, fname);
         	printf("%s\n", dfname );
         	fd = Open(dfname, O_RDONLY, 0);
         	Rio_readn(fd, buf, MAXLINE);
         	Close(fd);
         	if (strstr(buf,find))
         	{
         		strcpy(rtxt, sreplace(buf,find,replace));
         		printf("%s\n", rtxt);
         		
         		rtxt[0] = '\0';
         		buf[0] = '\0';
         	} else if(strstr(buf,find2))
         	{
         		strcpy(rtxt, sinsert(buf,find2,replace));
         		printf("%s\n", rtxt );

         		rtxt[0] = '\0';
         		buf[0] = '\0';
         	}
     	}
	}
   	closedir(dir);
   
	/* code */
	return 0;
}


char *sreplace(char *orig, char *rep, char *replacetxt) {
    char *result; 
    char *insert;  
    char *tmp;    
    int len_rep;  
    int len_replacetxt; 
    int len_front; 
    int count;

    // sanity checks and initialization
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
   
    len_replacetxt = strlen(replacetxt);

    // count the number of replacements needed
    insert = orig;
    for (count = 0; tmp = strstr(insert, rep); ++count) {
        insert = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_replacetxt - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        insert = strstr(orig, rep);
        len_front = insert- orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, replacetxt) + len_replacetxt;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    
    return result;
}

char *sinsert(char *orig, char *rep, char *replacetxt) {
    char *result; 
    int len_replacetxt; 
    int len_front; 
    int count;
    char *insert;  
    char *tmp;    
    int len_rep;  
  
    
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    len_replacetxt = strlen(replacetxt);

    // count the number of replacements needed
    insert = orig;
    for (count = 0; tmp = strstr(insert, rep); ++count) {
        insert = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_replacetxt - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        insert = strstr(orig, rep);
        len_front = insert - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front +1;
        tmp = strcat(tmp, replacetxt) + len_replacetxt ;
        orig += len_front; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    
    return result;
}

