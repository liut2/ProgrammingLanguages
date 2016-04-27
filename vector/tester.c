/*
  Tester program for vector.c
  By Dave Musicant
*/

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main()
{
    // Create an empty vector with memory capacity of 10
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    init(vector,10);

    // Insert 50 numbers into it
    for (int i=0; i < 50; i++)
    {
	insert(vector,0,i);
    }

    // Display list, both in entirety as well as one by one
    print(vector);
    //printf("\n");
    int value;
    for (int i=0; i < 50; i++)
    {
	int status = get(vector,i,&value);
	printf("Status = %i, value = %i\n",status,value);
    }

    // Delete a few values, and display again
    delete(vector,6);
    delete(vector,12);
    delete(vector,49);
    //printf("deleted not exist %d\n", delete(vector,49));
    print(vector);

    // Clean up memory
    cleanup(vector);
    free(vector);

    return 0;
}
