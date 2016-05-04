#include <stdio.h>
#include <stdlib.h>
#include "talloc.h"
#include "value.h"

Value *makeNullMalloc();
Value *consMalloc(Value *car, Value *cdr);

Value *makeNullMalloc() {
  Value *head = malloc(sizeof(Value));
  head->type = NULL_TYPE;
  return head;
}

Value *consMalloc(Value *car, Value *cdr) {
  Value *head = malloc(sizeof(Value));
  head->type = CONS_TYPE;
  (head->c).car = car;
  (head->c).cdr = cdr;
  return head;
}

Value *head;
// Replacement for malloc that stores the pointers allocated. It should store
// the pointers in some kind of list; a linked list would do fine, but insert
// here whatever code you'll need to do so; don't call functions in the
// pre-existing linkedlist.h. Otherwise you'll end up with circular
// dependencies, since you're going to modify the linked list to use talloc.
void *talloc(size_t size){
  if (head == NULL){
    head = makeNullMalloc();
  }
  //declare pointer type Value
  Value* car = malloc(sizeof(Value));
  car->type = PTR_TYPE;
  car->p = malloc(size);
  //cons into active list
  head = consMalloc(car, head);
  return car->p;
}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated in lists to hold those pointers.
void tfree(){
  while (head->type == CONS_TYPE) {
    if ((head->c).car->type == PTR_TYPE){
      free((head->c).car->p);
    }
    free((head->c).car);
    Value *temp = (head->c).cdr;
    free(head);
    head = temp;
  }
  free(head);
  head = NULL;
}

// Replacement for the C function "exit", that consists of two lines: it calls
// tfree before calling exit. It's useful to have later on; if an error happens,
// you can exit your program, and all memory is automatically cleaned up.
void texit(int status){
  tfree();
  exit(status);
}
