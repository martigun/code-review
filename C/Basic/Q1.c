/* CS261- Assignment 1 - Q.1*/
/* Name:
* Date:
* Solution description:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
	/*Allocate memory for ten students*/
	struct student* s_ptr = malloc(sizeof(struct student[10]));
	
	/*return the pointer*/
	return s_ptr;
	
}

int value_is_in_array(int value, struct student* students, int size){

	//cycle through current size
	for (int i = 0; i < size; i++){

		//return 1 if the value is found
		if (value == students[i].id) return 1;
	}

	//return 0 if not
	return 0;
}

void generate(struct student* students){
	/*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	
	for (int i = 0; i < 10; i++){
		int rand_id, rand_score;
		
		//create id
		rand_id = (rand() % 10) + 1;
			
		//re-create id if value is already used
		while (value_is_in_array(rand_id,students,i)) rand_id = (rand() % 10) + 1;
						
		//create score
		rand_score = rand() % 101;

		//assign id and score
		students[i].id = rand_id;
		students[i].score = rand_score;

	}
}

void output(struct student* students){
	/*Output information about the ten students in the format:
	ID1 Score1
	ID2 score2
	ID3 score3
	...
	ID10 score10*/

	for (int i = 0; i < 10; i++){
		printf("%d", students[i].id);
		printf(" ");
		printf("%d", students[i].score);
		printf("\n");
	}
}

void summary(struct student* students){
	/*Compute and print the minimum, maximum and average scores of the ten students*/
	

	int min_score = 100, max_score = 0;

	double avg_score, tot_score=0;

	for (int i = 0; i < 10; i++){
		//re-set min
		if (students[i].score < min_score) min_score = students[i].score;

		//re-set max
		if (students[i].score > max_score) max_score = students[i].score;

		//cast current
		avg_score = (double)students[i].score;
		//add to total
		tot_score = tot_score + avg_score;
				
	}

	//calc average
	avg_score = tot_score / 10.0;

	//output these calcs
	printf("\n");
	printf("Min score: %d",min_score);
	printf("\n");
	printf("Max score: %d", max_score);
	printf("\n");
	printf("Avg score: %f", avg_score);
	printf("\n");
}

void deallocate(struct student* stud){
	/*Deallocate memory from stud*/
	free(stud);

}

int main(int argc, const char * argv[]){
	struct student* stud = NULL;

	/*call allocate*/
	stud = allocate();

	/*call generate*/
	srand(time(0));
	generate(stud);
	
	/*call output*/
	output(stud);

	/*call summary*/
	summary(stud);

	/*call deallocate*/
	deallocate(stud);

	return 0;
}
