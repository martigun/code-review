/* CS261- Assignment 1 - Q.2*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
	/*Set a to double its original value*/
	*a = (*a) * 2;
	
	/*Set b to half its original value*/
	*b = (*b) / 2;

	/*Assign a+b to c*/
	c = *a + *b;

	/*Return c*/
	return c;
}

int main(int argc, const char * argv[]){
	/*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5, y = 6, z = 7;
	
	/*Print the values of x, y and z*/
	printf("x is %d\n", x);
	printf("y is %d\n", y);
	printf("z is %d\n", z);

	/*Call foo() appropriately, passing x,y,z as parameters*/
	int return_val = foo(&x, &y, z);
	
	/*Print the value returned by foo*/
	printf("The value returned by foo is %d\n", return_val);

	/*Print the values of x, y and z again*/
	printf("x is %d\n", x);
	printf("y is %d\n", y);
	printf("z is %d\n", z);

	/*Is the return value different than the value of z?  Why?*/
	// The value return by foo is different that the value of z.
	// This is because we passed in z by value, instead of passing in a reference.
	// Since we passed in a value, z was copied inside of foo() and the actual value
	// held by z was never accessed and changed.

	return 0;
}


