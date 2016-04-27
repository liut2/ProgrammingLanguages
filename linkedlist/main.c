// Tester for linked list. Note that this does not test all the functionality
// you implemented; you should enhance it significantly. We will test your
// linked list code with a different main.c.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedlist.h"
#include "value.h"

int main() {
    Value *val1 = malloc(sizeof(Value));
    val1->type = INT_TYPE;
    val1->i = 12;

    Value *val2 = malloc(sizeof(Value));
    val2->type = DOUBLE_TYPE;
    val2->d = 4.3;

    Value *val3 = malloc(sizeof(Value));
    val3->type = DOUBLE_TYPE;
    val3->d = 1.0;


    //Value *val4 = malloc(sizeof(Value));
    //val4->type = STR_TYPE;
    //val4->s = "a";

    Value *head = makeNull();
    //printf("head type is %u\n", head->type);
    head = cons(val1,head);
    head = cons(val2,head);
    head = cons(val3,head);
    //head = cons(val4,head);

    display(head);
    printf("head type is %u\n", head->type);
    printf("Length = %i\n",length(head));
    printf("Empty? %i\n",isNull(head));
    cleanup(head);
    //printf("Empty? %i\n",isNull(head));
    //printf("head type is %d\n", head->i);
    //printf("Length = %i\n",length(head));
    return 0;
}
