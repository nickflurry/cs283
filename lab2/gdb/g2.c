#include <stdio.h> 
#include <stdlib.h> 

int main () 
 {
  char * buf;
  int num;
  //num = 1 << 31;
  num = sizeof(char);
  buf = (char *) malloc(num) ;
  fgets (stdin, 1024, buf ) ;
  printf ("%s\n", buf) ;
  close(buf);
  return(1);
 }
