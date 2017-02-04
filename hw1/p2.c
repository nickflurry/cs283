#include "p2.h"

int main(int argc, char const *argv[])
{

  node_i * head; 
  head = malloc(sizeof(node_i));
  if (head == NULL){
    exit(-1);
  }
  
  if( argc == 1 ) {
    printf("%s\n", "Expected argument:  Decimal input");
    exit(-2);
 }
 else if( argc > 2 ) {
    printf("Too many arguments supplied:   Expected Decimal input\n");
    exit(-1); 
 }

  int dec = atoi(argv[1]); 

  head->val = pow2_to_b(32 , dec);
  if (head->val == 1){
    dec = dec - pow(2, 32);
  }
  

  for (int n = 31; n >= 0; n--){
     //This way causes it to be O(n^2) I could watch the tail and add from there but on modern day machines it won't mean much for this assignment. 
     if (pow2_to_b(n, dec) == 1){
      push_i(head ,1);
      dec = dec - pow(2, n);
    }else{
      push_i(head, 0);
    }

  }

  printList(head);

  freeList(head);
  free(head);

	/* code */
	return 0;
}


int pow2_to_b(int n, int dec){
	if (pow(2 , n) <= dec){
    return 1;
  } else { 
    return 0;
  }
}

void printList(node_i * head){
  int count = 0;
  while (head != NULL ){
    printf("%i", head->val);
    head = head->next;
    if(count % 8 == 0 && count != 0) { printf(" ");}
    count++;

  }
  printf("\n");
}

void push_i(node_i * head, int val) {
    node_i * curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = malloc(sizeof(node_i));
    curr->next->val = val;
    curr->next->next = NULL;
}

void freeList(node_i * head){
  node_i * curr;
  while ((curr = head) != NULL) { 
    head = head->next;          
    free (curr);                
  } 
  return;
}