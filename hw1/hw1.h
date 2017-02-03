#ifndef wh1
#define hw1


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// Globals
#define SIZE 128


typedef struct node
{
	struct node * next;
	char txt[SIZE]; 
} node_t;


node_t * push_t(node_t ** head, char * val); 
void printList(node_t * head);
void freeList(node_t * head);




#endif