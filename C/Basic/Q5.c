/* CS261- Assignment 1 - Q.5*/
/* Name:
* Date:
* Solution description:
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
	return ch - 'a' + 'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
	return ch - 'A' + 'a';
}

void sticky(char* word){
	/*Convert to sticky caps*/

	char curr_char = word[0];
	int i = 0;
	int flip = 1;

	while (curr_char != '\0'){

		//if greater than Z, it is lower case
		if (curr_char > 'Z'){
			//do nothing
		} else{
			curr_char = toLowerCase(curr_char);
		}
		
		//flip every other char
		if (flip == 1) curr_char = toUpperCase(curr_char);

		word[i] = curr_char;

		i++;
		curr_char = word[i];
		flip = flip *-1;
	}
}

int main(int argc, const char * argv[]){
	/*Read word from the keyboard using scanf*/
	char str[80];

	printf("Enter a word: ");
	scanf("%40s", str);

	/*Call sticky*/
	sticky(&str);

	/*Print the new word*/
	printf("Finish New Word: \n");
	printf("%s", str);
	printf("\n");

	return 0;
}
