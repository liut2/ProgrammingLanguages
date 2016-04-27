#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// Create a new NULL_TYPE value node.
Value *makeNull() {
  Value *head = malloc(sizeof(Value));
  head->type = NULL_TYPE;
  return head;
}

// Create a new CONS_TYPE value node.
Value *cons(Value *car, Value *cdr) {
  Value *head = malloc(sizeof(Value));
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
  Value *oriHead = reverse(list);
  Value *head = oriHead;
  while (head->type == CONS_TYPE) {
    printHelper((head->c).car);
    head = (head->c).cdr;
  }
  cleanup(oriHead);
}

Value *copyHelper(Value *val) {
  Value *newVal = malloc(sizeof(Value));
  switch (val->type) {
    case INT_TYPE:
      newVal->type = INT_TYPE;
      newVal->i = val->i;
      break;
    case DOUBLE_TYPE:
      newVal->type = DOUBLE_TYPE;
      newVal->d = val->d;
      break;
    case STR_TYPE:
      newVal->type = STR_TYPE;
      newVal->s = val->s;
      break;
    case NULL_TYPE:
      newVal->type = NULL_TYPE;
      break;
    default:
      break;
  }
  return newVal;
}
// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory between the original list and the new one.
//
// FAQ: What if there are nested lists inside that list?
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.
Value *reverse(Value *list) {
  Value *cur = makeNull();
  Value *oriHead = list;
  while (oriHead->type == CONS_TYPE) {
    //Value *next = cons((oriHead->c).car, cur);
    Value *next = cons(copyHelper((oriHead->c).car), cur);
    oriHead = (oriHead->c).cdr;
    cur = next;
  }
  return cur;
}

// Frees up all memory directly or indirectly referred to by list. Note that
// this linked list might consist of linked lists as items, so you'll need to
// clean them up as well.
// FAQ: What if there are nested lists inside that list?
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.
void cleanup(Value *head) {
  while (head->type == CONS_TYPE) {
    free((head->c).car);
    Value *temp = (head->c).cdr;
    free(head);
    head = temp;
  }
  free(head);
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
