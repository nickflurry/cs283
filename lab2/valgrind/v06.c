#include <stdio.h>

int foo (x)
int x;
 {
 	x = 11; 
  if(x < 10)
   {
    printf("x is less than 10\n");
   }
 }

int main()
 {
  int y;
  foo(y);
 }
