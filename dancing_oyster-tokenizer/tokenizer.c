#include <stdio.h>
#include <stdlib.h>
#include "talloc.h"
#include "linkedlist.h"
#include "value.h"
#include <string.h>

/*
Value *getTypeHelper(char ch) {
  Value *val = talloc(sizeof(Value));
  if (ch == "(") {
    val->type = OPEN_TYPE;
    val->s = "(";
  }else if (ch == ")"){
    val->type = CLOSE_TYPE;
    val->s = ")";
  }else if ()
}
*/

// Read all of the input from stdin, and return a linked list consisting of the
// tokens.
void switchHelper(Value* val) {
  switch (val->type) {
    case INT_TYPE:
      printf ("%d:integer\n", val->i);
      break;
    case DOUBLE_TYPE:
      printf ("%f:double\n", val->d);
      break;
    case OPEN_TYPE:
      printf("%s:open\n", val->s);
      break;
    case CLOSE_TYPE:
      printf("%s:close\n", val->s);
      break;
    case STR_TYPE:
      printf ("%s:string\n", val->s);
      break;
    case SYMBOL_TYPE:
      printf("%s:symbol\n", val->s);
    default:
      break;
  }
}
Value *tokenize() {
  char charRead;
  Value *list = makeNull();
  charRead = fgetc(stdin);
  Value * val;
  while (charRead != EOF) {
    if (charRead == '"'){
      char* stack_str;
      charRead = fgetc(stdin);
      int i = 0;
      while (charRead != EOF && charRead != '"'){
        stack_str[i] = charRead;
        i++;
        charRead = fgetc(stdin);
      }
      stack_str[i] ='\0';
      val = talloc(sizeof(Value));
      val->type = STR_TYPE;
      //str copy
      char* str = talloc(sizeof(char) * i);
      strcpy(str, stack_str);
      val->s = str;
      list = cons(val, list);
    } else if (charRead == ';') {
      while (charRead != EOF && charRead != '\n') {
        charRead = fgetc(stdin);
      }
    } else if (charRead == '(') {
      val = talloc(sizeof(Value));
      val->type = OPEN_TYPE;
      val->s = "(";
      list = cons(val, list);
    } else if (charRead == ')') {
      val = talloc(sizeof(Value));
      val->type = CLOSE_TYPE;
      val->s = ")";
      list = cons(val, list);
    } else if (charRead != ' ' && charRead != '\n'){
      char* stack_str;
      //stack_str[0] = charRead;
      int i = 0;
      while (charRead != EOF && charRead != ' ' && charRead != '\n' && charRead != ')' && charRead != '(' && charRead != ';'){
        stack_str[i] = charRead;
        i++;
        charRead = fgetc(stdin);
      }
      stack_str[i] ='\0';
      //printf("the jiange should be correct %s\n", stack_str);
      int length = i;
      i--;
      bool zero = true;
      int dotCounter = 0;
      while (i >= 0) {
        if (stack_str[i] != '0' && stack_str[i] != '.') {
          zero = false;
        }
        if (stack_str[i] == '.') {
          dotCounter++;
        }
        i--;
      }
      //printf ("%s with counter %d", stack_str, dotCounter);
      if (zero && (dotCounter == 0)) {
        // it is zero
        val = talloc(sizeof(Value));
        val->type = INT_TYPE;
        val->i = 0;
        list = cons(val, list);
        //printf ("int :%d\n", val->i);
      } else if (zero && (dotCounter == 1)) {
        val = talloc(sizeof(Value));
        val->type = DOUBLE_TYPE;
        val->d = 0.0;
        list = cons(val, list);
        //printf ("float:%f\n", val->d);
      }
      else {
        // it is not zero
        val = talloc(sizeof(Value));
        double atoi_result = atof(stack_str);
        if (atoi_result == 0) {
          // it is a symbol
          val->type = SYMBOL_TYPE;
          //printf ("symbol:%s\n", stack_str);
          char* str = talloc(sizeof(char) * length);
          strcpy(str, stack_str);
          val->s = str;
        } else {
          // it is a number
          if (dotCounter == 0) {
            val->type = INT_TYPE;
            val->i = atoi(stack_str);
            //printf ("int :%d\n", val->i);
          } else if (dotCounter == 1) {
            val->type = DOUBLE_TYPE;
            val->d = atof(stack_str);
            //printf ("float:%f\n", val->d);
          } else {
            // it is a symbol
            val->type = SYMBOL_TYPE;
            char* str = talloc(sizeof(char) * length);
            strcpy(str, stack_str);
            val->s = str;
            //printf ("symbol:%s\n", str);
          }

        }
        list = cons(val, list);
        if (charRead == '(') {
          val = talloc(sizeof(Value));
          val->type = OPEN_TYPE;
          val->s = "(";
          list = cons(val, list);
        } else if (charRead == ')') {
          val = talloc(sizeof(Value));
          val->type = CLOSE_TYPE;
          val->s = ")";
          list = cons(val, list);
        } else if (charRead == ';') {
          while (charRead != EOF && charRead != '\n') {
            charRead = fgetc(stdin);
          }
        }
      }
    }

    charRead = fgetc(stdin);
  }

  Value *revList = reverse(list);
  return revList;
}

// Displays the contents of the linked list as tokens, with type information
void displayTokens(Value *list) {
  printf("%d\n", length(list));
  Value *head = list;
  while (head->type == CONS_TYPE) {
    switchHelper((head->c).car);
    head = (head->c).cdr;
  }
  printf("\n");
}
