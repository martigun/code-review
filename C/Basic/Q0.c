/* CS261- Assignment 1 - Q. 0*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
	/*Print the value pointed to by iptr*/
	
	printf("The value the pointer points to is %d", *iptr);
	printf("\n");

	/*Print the address pointed to by iptr*/

	printf("The address the pointer points to is %X", iptr);
	printf("\n");

	/*Print the address of iptr itself*/

	printf("The address iptr is %X", &iptr);
	printf("\n");

}

int main(int argc, const char * argv[]){

	/*declare an integer x*/

	int x = 8;
	
	/*print the address of x*/

	printf("The address of x is %X", &x);
	printf("\n");
	
	/*Call fooA() with the address of x*/

	fooA(&x);

	/*print the value of x*/

	printf("The value of x is %d", x);
	printf("\n");

	return 0;
}
