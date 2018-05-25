#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */



int compare(TYPE left, TYPE right){

	//cast two type struct data variables using left and right
	struct data * left_node = (struct data *)left;
	struct data * right_node = (struct data *)right;

	//set the number member to variables in this function
	int left_nbr = left_node->number;
	int right_nbr = right_node->number;

	//if left < right return -1
	if (left_nbr < right_nbr) return -1;

	//if left > right return 1
	if (left_nbr > right_nbr) return 1;

	//if left = right return 0
	return 0;

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval){

	//cast a type stuct data using curval
	struct data * this_node = (struct data *)curval;

	//print this integer
	printf("%d", this_node->number);


}


