#include "libraries.h"
#include "functions.h"
#include "structs.h"

// function for creating nodes
struct Node* createNode(void){
  struct Node* node = calloc(1, sizeof(struct Node));  
  node->pid = 0;
  return node;
}
  
// setup our linked list struct
struct LL* createLL(void){
  struct LL* linked = calloc(1, sizeof(struct LL));
  linked->head = NULL;
  linked->tail = NULL;
  return linked;
}

// function for adding nodes to our linked list
struct Node* addNode(struct LL* linked, struct Node* node){  
  
  if(linked->head == NULL){
    linked->head = node;
    linked->tail = node;
  }
  else{
    linked->tail->next = node; 
    linked->tail = node;
  }
  
  return node;
}


// function for removing nodes from out linked list 
void removeNode(struct LL* linked, struct Node* node){
  
  struct Node* current = linked->head;
  struct Node* previous;
    
  // check to see if the head is the node to be removed
  if(current){
    if(current->pid == node->pid){
      linked->head = linked->head->next;
      free(current);
    }
  }
  else{
    return;
  }
  
  // iterate until the next node is either null or our node
  while(current->next){
    previous = current;
    current = current->next;
    if(current->pid == node->pid){
      previous->next = current->next;
      free(current);
    }
  }
}


// function for printing our linked list
void printLL(struct LL* linked){
  struct Node* current = linked->head;
  
  while(current){
    printf("%d ", current->pid);
    current = current->next;
  }
  return;
  
}


void freeLL(struct LL* linked){
  // free everything in our linked list.
  
  while(linked->head){
    
    // save the current node
    struct Node* current = linked->head;
    
    // move forward
    linked->head = linked->head->next;
    
    // free the struct
    free(current);

  }
  // free the linked list
  free(linked);
  return;
}