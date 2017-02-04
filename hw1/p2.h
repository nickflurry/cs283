#ifndef p2
#define p2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node
{
	struct node * next;
	int val; 
} node_i;


int pow2_to_b(int n, int dec);
void push_i(node_i * head, int val);
void printList(node_i * head);
void freeList(node_i * head);

#endif