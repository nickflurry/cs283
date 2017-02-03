#include <stdio.h>
#include <stdlib.h>
#define SIZE 128


typedef struct node
{
	struct node * next;
	char * txt; 
} node_t;

node_t * push(node_t ** head, int val); 



int main(int argc, char const *argv[])
 {
  node_t * head = NULL;
  head = malloc(sizeof(node_t));
  if (head == NULL) {
    return 1;
  }
  
  head->txt = NULL;
  head->next = NULL;
  
  char line[SIZE];
  FILE * fp = fopen("./test.txt", "r");
  if (fp == NULL)
  { return 1; }

//Read each line of the file, and print it to screen 
  while(fgets(line, SIZE, fp) != NULL)
   {
    head = push_t( **head , line);
   }
   
   printf("%s\n", "got here" );

 	return 0;
}


node_t * push_t(node_t ** head, char* val) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->txt = val;
    new_node->next = *head;
    *head = new_node;
    return head;
}