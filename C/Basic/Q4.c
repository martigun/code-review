

/* CS261- Assignment 1 - Q.4*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>
#include <stdlib.h>


struct student{
	int id;
	int score;
};

void sort_students(struct student* students, int n){
	/*Sort the n students based on their score*/

	/*Sort the given array number , of length n*/

	for (int i = 0; i < n; i++){ //go through each member of the array
		int index_of_next_smallest = i;
		int next_smallest = students[i].score;

		for (int j = (i + 1); j < n; j++){ //cycle through all the members in front of it
			if (students[j].score < students[index_of_next_smallest].score){ //if the member is smaller than the current smallest
				next_smallest = students[j].score; //set next smallest
				index_of_next_smallest = j; //set index of next smallest
			}
		}

		int temp, temp_id;
		temp = students[i].score;
		students[i].score = students[index_of_next_smallest].score;
		students[index_of_next_smallest].score = temp;

		temp_id = students[i].id;
		students[i].id = students[index_of_next_smallest].id;
		students[index_of_next_smallest].id = temp_id;

	}

}

int value_is_in_the_array(int value, struct student* students, int size){

	//cycle through current size
	for (int i = 0; i < size; i++){

		//return 1 if the value is found
		if (value == students[i].id) return 1;
	}

	//return 0 if not
	return 0;
}

int main(int argc, const char * argv[]){
	/*Declare an integer n and assign it a value.*/
	int n = 20;

	/*Allocate memory for n students using malloc.*/
	struct student* students = malloc(n* sizeof(struct student));

	/*Generate random IDs and scores for the n students, using rand().*/
	srand(time(0));
	for (int i = 0; i < n; i++){
		int rand_id, rand_score;

		//create id
		rand_id = (rand() % n) + 1;

		//re-create id if value is already used
		while (value_is_in_the_array(rand_id, students, i)) rand_id = (rand() % n) + 1;

		//create score
		rand_score = rand() % 101;

		//assign id and score
		students[i].id = rand_id;
		students[i].score = rand_score;

	}

	/*Print the contents of the array of n students.*/
	printf("Original List: \n");
	for (int i = 0; i < n; i++){
		printf("%d", students[i].id);
		printf(" ");
		printf("%d", students[i].score);
		printf("\n");
	}

	/*Pass this array along with n to the sort() function*/
	sort_students(students, n);

	/*Print the contents of the array of n students.*/
	printf("Sorted List: \n");
	for (int i = 0; i < n; i++){
		printf("%d", students[i].id);
		printf(" ");
		printf("%d", students[i].score);
		printf("\n");
	}

	return 0;
}



