
#include <stdio.h>

int main(int argc, char const *argv[])
{

	long x = 1; 

	int count = 0; 

	while(1){
		x = x * 2;
		count++;
		if (x == 0){
			break;
			count -- ;
		}
	}
	printf("%i\n", count);
	/* code */
	return 0;
}
