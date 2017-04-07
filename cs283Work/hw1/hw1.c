
//Header 
#include "hw1.h"


int main(int argc, char const *argv[])
 {

  if( argc == 1 ) {
      printf("%s\n", "Expected argument:  File name");
      exit(-2);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied:   Expected File name\n");
      exit(-1); 
   }

  node_t * head;
  head = malloc(sizeof(node_t));
  if (head == NULL) {
    return 1;
  }

  node_t ** x; 
  x = malloc(sizeof(node_t *)*2); 

  char line[SIZE];
  FILE * fp = fopen(argv[1], "r");
  if (fp == NULL)
  { printf("%s\n", "File not found" );
    return 1; }
  
//Read each line of the file, and print it to screen 
  while(fgets(line, SIZE, fp) != NULL)
   {
    *x = head;
    head = push_t( x , line);
   }
   
   
   printList(head);
   
   //Clean up time
   freeList(head);
   free(x);
   fclose(fp);

 	return 0;
}


void printList(node_t * head){
  while (head != NULL ){
    printf("%s", head->txt );
    head = head->next;
  }
}


node_t * push_t(node_t ** head, char* val) {
    //created new node
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    strcpy( new_node->txt , val);
    new_node->next = *head;
    *head = new_node;
    return *head;
}

void freeList(node_t * head){
  node_t * curr;
  while ((curr = head) != NULL) { 
    head = head->next;          
    free (curr);                
  } 
  return;
}

