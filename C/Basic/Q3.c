/* CS261- Assignment 1 - Q.3*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>

void sort(int* number, int n){
	/*Sort the given array number , of length n*/

	for (int i = 0; i < n; i++){ //go through each member of the array
		int index_of_next_smallest = i;
		int next_smallest = number[i];

		for (int j = (i + 1); j < n; j++){ //cycle through all the members in front of it
			if (number[j] < number[index_of_next_smallest]){ //if the member is smaller than the current smallest
				next_smallest = number[j]; //set next smallest
				index_of_next_smallest = j; //set index of next smallest
			}
		}

		int temp;
		temp = number[i];
		number[i] = number[index_of_next_smallest];
		number[index_of_next_smallest] = temp;

	}
}

int main(int argc, const char * argv[]){
	/*Declare an integer n and assign it a value of 20.*/
	int n = 20;

	/*Allocate memory for an array of n integers using malloc.*/
	int *ptr;
	ptr = malloc(sizeof(int)*n);

	/*Fill this array with random numbers, using rand().*/
	srand(time(0));
	for (int i = 0; i < 20; i++) ptr[i] = (rand() % 100) + 1;

	/*Print the contents of the array.*/
	printf("Original List:\n");
	for (int i = 0; i < 20; i++) printf("%d\n",ptr[i]);

	/*Pass this array along with n to the sort() function of part a.*/
	sort(ptr, n);

	/*Print the contents of the array.*/
	printf("Sorted List:\n");
	for (int i = 0; i < 20; i++) printf("%d\n", ptr[i]);

	return 0;
}
