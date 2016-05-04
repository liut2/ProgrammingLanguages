#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "talloc.h"
// Create a new NULL_TYPE value node.
Value *makeNull() {
  Value *head = talloc(sizeof(Value));
  head->type = NULL_TYPE;
  return head;
}

// Create a new CONS_TYPE value node.
Value *cons(Value *car, Value *cdr) {
  Value *head = talloc(sizeof(Value));
  head->type = CONS_TYPE;
  (head->c).car = car;
  (head->c).cdr = cdr;
  return head;
}
// Help print the value of the cell
void printHelper(Value* val) {
  switch (val->type) {
    case INT_TYPE:
      printf ("%d ", val->i);
      break;
    case DOUBLE_TYPE:
      printf ("%f ", val->d);
      break;
    case OPEN_TYPE:
    case CLOSE_TYPE:
    case STR_TYPE:
      printf ("%s ", val->s);
      break;
    case NULL_TYPE:
      printf ("null");
      break;
    default:
      break;
  }
}
// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list) {
  Value *head = list;
  while (head->type == CONS_TYPE) {
    printHelper((head->c).car);
    head = (head->c).cdr;
  }
  printf("\n");
}

// Return a new list that is the reverse of the one that is passed in. No stored
// data within the linked list should be duplicated; rather, a new linked list
// of CONS_TYPE nodes should be created, that point to items in the original
// list.
Value *reverse(Value *list) {
  Value *cur = makeNull();
  Value *oriHead = list;
  while (oriHead->type == CONS_TYPE) {
    Value *next = cons((oriHead->c).car, cur);
    oriHead = (oriHead->c).cdr;
    cur = next;
  }
  return cur;
}

// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list) {
  assert(list->type == CONS_TYPE);
  return (list->c).car;
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list) {
  assert(list->type == CONS_TYPE);
  return (list->c).cdr;
}

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value) {
  assert(value != NULL);
  return value->type == NULL_TYPE;
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value) {
  Value *oriHead = value;
  int length = 0;
  while (oriHead->type == CONS_TYPE) {
    length++;
    oriHead = (oriHead->c).cdr;
  }
  return length;
}
