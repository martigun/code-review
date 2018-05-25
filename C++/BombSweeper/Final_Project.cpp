/**************************************************
*  Author: Gunnar Martin
*  Date:
*  Description:
*  **********************************************/

/*Libraries*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> //time()

/*Using Statments*/
using std::string;
using std::cout;
using std::cin;
using std::endl;

/*Constants*/
#define BOMBSWEEPER_KEY "1"
#define INSTRUCTIONS_KEY "2"
#define INT_DB_KEY "3"
#define QUIT_KEY "4"

/***Function Prototypes***/
/*Non-Bombsweeper Prototypes*/
	void clear_console();
	bool menu_entry_invalid(string user_input);
	string get_menu_entry();
	void display_main_menu(string user_name);
	void instructions();
	int do_factorial(int n);
	void the_integer_encyclopedia();

/* Bombsweeper Prototypes */
	//Get User Rows and Cols
		bool user_int_invalid(string user_input);
		int get_user_cols();
		int get_user_rows();
	//Generate Number Board
		void zero_number_array(int **number_array, int cols, int rows);
		void add_bombs_to_number_array(int **number_array, int cols, int rows, int bombs);
		void add_nbrs_to_number_array(int **number_array, int cols, int rows);
		void fill_number_array(int **number_array, int cols, int rows, int &cells, int &bomb_count);
	//Display Progress Board for user
		void cout_2d_array(int **number_array, int cols, int rows);
		void cout_2d_array(char **prog_array, int cols, int rows);
		void add_data_to_print_array(char **print_array, char **prog_array, int cols, int rows, int COL_SHIFT, int ROW_SHIFT);
		void add_rc_titles(char **print_array, int cols, int rows);
		void add_rc_labels(char **print_array, int cols, int rows, int COL_SHIFT, int ROW_SHIFT);
		void display_progress_array(char **prog_array, int cols, int rows, int bomb_count);
		void display_bomb_count(int bomb_count);
		void display_flags_left(char **prog_array, int cols, int rows, int bomb_count);
	//Update Progress Board
		void zero_progress_array(char **print_array, int cols, int rows);
		void flag_progress(char **prog_array, int user_choice);
		void step_progress(char **prog_array, int **number_array, int user_choice, bool &hit_a_bomb, int cols, int rows);
		void reveal_progress(char **prog_array, int **number_array, int cols, int rows);
	//User Interaction during game
		int letter_lookup(char letter);
		bool col_out_of_range(char user_col, int cols);
		bool choice_is_invalid(string user_input, int cols, int rows, char **prog_array);
		int convert_to_code(string user_input);
		int get_user_choice(int cols, int rows, string &user_choice_string, char **prog_array);
		char get_flag_or_step();
	//Evaluate Winning conditions
		int count_safe_cells(char **prog_array, int cols, int rows);
	//The Bombsweeper application
		void bombsweeper();

//Functions outside of Bombsweeper
void clear_console(){
	//Adds 50 new lines, effectively clearing the console
	const int LINES_TO_CLEAR = 50;
	for (int i = 0; i < LINES_TO_CLEAR; i++){
		cout << endl;
	}
}
bool menu_entry_invalid(string user_input){
	//valides the user's menu entry
	if (user_input == BOMBSWEEPER_KEY) return 0;
	if (user_input == INSTRUCTIONS_KEY) return 0;
	if (user_input == INT_DB_KEY) return 0;
	if (user_input == QUIT_KEY) return 0;

	return 1;
}
string get_menu_entry(){
	//gets the user's menu entry
	string user_input;
	string nothing_string;

	getline(cin, user_input);
	while (menu_entry_invalid(user_input)){
		cout << endl << "Your menu entry was invalid." << endl;
		cout << "Please enter only the integer associated " << endl;
		cout << "with the menu choice you'd like." << endl;
		cout << "Do not use any spaces, parenethesis or special characters." << endl << endl;
		cout << "Press Enter to continue..." << endl;
		getline(cin, nothing_string);

		display_main_menu(user_input);
		getline(cin, user_input);
	}

	return user_input;
}
void display_main_menu(string user_name){
	//Displays the main menu of the program
	cout << "**** GAME MENU ****" << endl;
	cout << "Hello" << user_name << "!" << endl;
	cout << "Welcome to the game menu!" << endl << endl;
	cout << "Enter the integer that corresponds " << endl;
	cout << "with the menu choice you'd like below: " << endl << endl;
	cout << "(" << BOMBSWEEPER_KEY << ") Play Bombsweeper" << endl;
	cout << "(" << INSTRUCTIONS_KEY << ") Read Bombsweeper Instructions" << endl;
	cout << "(" << INT_DB_KEY << ") The Integer Encyclopedia" << endl;
	cout << "(" << QUIT_KEY << ") Quit Program" << endl;
	cout << endl << endl;
}
void instructions(){
	//prints the instructions for bombsweeper
	string user_input;

	clear_console();

	cout << "---- * BOMBSWEEPER * ----" << endl << endl;
	cout << "This game is based on the game Minesweeper." << endl;
	cout << "The goal is to step on all of the boxes that" << endl;
	cout << "don't have bombs in them, until all the 'safe' " << endl;
	cout << "boxes have been uncovered." << endl << endl;
	cout << "After stepping on a safe box, that box will" << endl;
	cout << "display a number that describes how many bombs" << endl;
	cout << "are adjacent to that box. If you step on a box" << endl;
	cout << "that has no adjacent bombs, then all of the" << endl;
	cout << "adjcent boxes will reveal their adjacent bomb" << endl;
	cout << "count. Use the clues to navigate the field." << endl << endl;
	cout << "Good luck! (press any key to continue)" << endl;

	getline(cin, user_input);

}
int do_factorial(int n){
	//returns the factorial of the integer n

	//---------------------------------------------
	//	Requirement #17: Demonstrate Recursion
	//---------------------------------------------
	if (n == 0) return 0;

	if (n == 1){
		return 1;
	}
	else {
		return do_factorial(n - 1)*n;
	}

}
void the_integer_encyclopedia(){
	//Displays some facts about a few integers
	string keep_running = "y";
	string empty_string = "";

	while (keep_running == "y"){
		clear_console();

		//---------------------------------------------
		//	Requirement #22: Demonstrate Class and Object
		//---------------------------------------------
		class an_integer {
		public:
			int squared;
		};

		//---------------------------------------------
		//	Requirement #21: Demonstrate bitwise operators
		//---------------------------------------------
		struct this_integer{
			string name;
			double div_by_two;
			int mult_by_five;
			int factorial;
		};

		this_integer four;
		four.div_by_two = 4.0 / 2.0;
		four.factorial = do_factorial(4);
		four.mult_by_five = 4 * 5;

		//---------------------------------------------
		//	Requirement #24: Demonstrate a pointer to a struct
		//---------------------------------------------
		this_integer *ptr_four;
		ptr_four = &four;

		an_integer two_three[2];
		two_three[0].squared = 2 * 2;
		two_three[1].squared = 3 * 3;

		//---------------------------------------------
		//	Requirement #23: Demonstrate a pointer to an array (two_three is an array of objects)
		//---------------------------------------------
		//---------------------------------------------
		//	Requirement #25: Demonstrate a pointer to an object (two_three is an array of objects)
		//---------------------------------------------
		an_integer *ptr_two_three[2];

		ptr_two_three[0] = &two_three[0];
		ptr_two_three[1] = &two_three[1];

		cout << "---- # INTEGER ENCYCLOPEDIA # ----" << endl << endl;
		cout << "Welcome to the integer encyclopedia." << endl;
		cout << "Home of almost everything you want to know" << endl;
		cout << "about some of your favorite integers." << endl;
		cout << "Press any key when you're ready for some knowledge!" << endl;
		getline(cin, empty_string);

		cout << "** The number TWO **" << endl << endl;
		cout << "Squared is: " << ptr_two_three[0]->squared << endl;

		cout << endl;

		cout << "** The number THREE **" << endl << endl;
		cout << "Squared is: " << ptr_two_three[1]->squared << endl;

		cout << endl;

		cout << "** The number FOUR **" << endl << endl;
		cout << "Divided by two is: " << ptr_four->div_by_two << endl;
		cout << "Factorial is: " << ptr_four->factorial << endl;
		cout << "Multiplied by 5 is: " << four.mult_by_five << endl;


		cout << endl;

		cout << "Additional Fun Facts:" << endl;
		//---------------------------------------------
		//	Requirement #06: Demonstrate bitwise operators
		//---------------------------------------------
		cout << "The bitwise operation AND of 10 & 25 is: " << (10 & 25) << endl;
		cout << "The bitwise operation OR of 10 | 25 is: " << (10 | 25) << endl;
		cout << "The bitwise operation exclusive OR of 10 ^ 25 is: " << (10 ^ 25) << endl;

		cout << "Run this program again?" << endl;
		cout << "Enter 'y' to keep playing or any other key to quit: ";

		getline(cin, keep_running);

	}
}

//Get User Rows and Cols***<Bombsweeper>***
bool user_int_invalid(string user_input){
	//Checks user input, to make sure it's between 4 and 16

	//---------------------------------------------
	/*	Requirement #09: Errors
	As I explained above, this function makes sure that
	the user's input is an integer between 4 and 16.
	First, the function makes sure that the input is only
	one or two chars. Next, it makes sure both of those chars are
	between 0 and 9. If I accidently had my < and > operators on those
	conditional statements backwards, that would've been a LOGIC
	error. The compiler would not have caught it, because it was 'legal',
	but the program would not be doing what I wanted. Also, on the conditional
	statement below, if I were to foget a parenthesis, the compiler
	would catch that move since it was 'illegal' and considered
	a SYNTAX error. Finally it converts the string into an
	integer. If I try to use an element of an array
	that is outside the array's range, the compiler won't catch it,
	but there will be a RUN-TIME error, since the compiler will
	try to use an element that doesn't exist. Same with dividing by zero.
	*/
	//---------------------------------------------

	//---------------------------------------------
	/*	Requirement #10: Demonstrate a debugging trick
	This sub-function checks to make sure that
	the user's entry is an integer between 4 and 16.
	If it is not, then a 1 is return and the user
	must input his number again.*/
	//---------------------------------------------

	//---------------------------------------------
	//	Requirement #11: Demonstrate a function I defined (this function)
	//---------------------------------------------

	//---------------------------------------------
	/*	Requirement #13: Demonstrates scope
	This sub-function uses the variable user_input_int, 
	which is an an int that has been converted from
	a string. This int is only used to check to see
	if the int is within a range. It has no use outside
	this function and is not avaialable outside
	this function.*/
	//---------------------------------------------

	//---------------------------------------------
	/*	Requirement #16: Demonstrate std::string
	The variable user_input in this function is a 
	std::string*/
	//---------------------------------------------

	const int RC_MIN = 4, RC_MAX = 16;

	if (user_input.length() != 1 && user_input.length() != 2) return 1;

	if (user_input.at(0)<'0' || user_input.at(0)>'9') return 1; //check first digit

	if (user_input.length() == 2){
		if (user_input.at(1)<'0' || user_input.at(1)>'9') return 1; //check second digit
	}

	int user_input_int = atoi(user_input.c_str());

	cout << user_input_int << endl;

	if (user_input_int<RC_MIN || user_input_int>RC_MAX) return 1; //check range
	
	return 0;

}
int get_user_cols(){
	//gets columns from user
	string user_input;

	cout << "Please enter an integer " << endl;
	cout << "between 4 and 16 for the number " << endl;
	cout << "of columns for your game board: " << endl;
	getline(cin, user_input);
	while (user_int_invalid(user_input)){
		cout << "Invalid entry. Please re-enter: " << endl;
		getline(cin, user_input);
	}

	return atoi(user_input.c_str());

}
int get_user_rows(){
	//gets rows from user
	string user_input;

	cout << "Please enter an integer " << endl;
	cout << "between 4 and 16 for the number " << endl;
	cout << "of rows for your game board: " << endl;
	getline(cin, user_input);
	while (user_int_invalid(user_input)){
		cout << "Invalid entry. Please re-enter: " << endl;
		getline(cin, user_input);
	}

	return atoi(user_input.c_str());
}
//Generate Number Board***<Bombsweeper>***
void zero_number_array(int **number_array, int cols, int rows){
	//Fills the number array with zeros
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			number_array[c][r] = 0;
		}
	}
}
void add_bombs_to_number_array(int **number_array, int cols, int rows, int bombs){
	//Uses the rand function to place bombs (9s) in the array in unique places
	//inside the number array
	srand(time(0));

	//---------------------------------------------
	//	Requirement #19: Demonstrate dynamically delcared array	
	//---------------------------------------------
	int *bomb_array;
	bomb_array = new int[int(bombs)];

	for (int b = 0; b < bombs; b++){
		char use_this_code;

		do {
			int c, r, code;
			use_this_code = 'y';

			//---------------------------------------------
			//	Requirement #08: Demonstrate a random number
			//---------------------------------------------
			c = rand() % cols;
			r = rand() % rows;

			code = c * 1000 + r;//create a code using the col and row

			for (int i = 0; i < b; i++){ //cycle through the existing bomb array looking for this code
				if (bomb_array[i] == code) use_this_code = 'n'; //set use to no if it's found
			}


			if (use_this_code == 'y'){ //Only if code is good
				bomb_array[b] = code; //Add to code to bomb array
				number_array[c][r] = 9; //change in number array
			}

		} while (use_this_code == 'n');
	}

}
void add_nbrs_to_number_array(int **number_array, int cols, int rows){
	//Fills in the array with the count of bombs in adjacent boxes
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			if (number_array[c][r] != 9){
				int count = 0; //set bombs around me to zero

				if (c != 0){ //If you're not in the first col
					count = count + (number_array[c - 1][r]) / 9; //Add left

					if (r != 0) count = count + (number_array[c - 1][r - 1]) / 9; //Upper Left
					if (r != rows - 1) count = count + (number_array[c - 1][r + 1]) / 9; //Lower Left
				}

				if (c != cols - 1){ //If you're not in the last col
					count = count + (number_array[c + 1][r]) / 9; //Add right

					if (r != 0) count = count + (number_array[c + 1][r - 1]) / 9; //Upper Right
					if (r != rows - 1) count = count + (number_array[c + 1][r + 1]) / 9; //Lower Right
				}

				if (r != 0) count = count + (number_array[c][r - 1]) / 9; //Add above
				if (r != rows - 1) count = count + (number_array[c][r + 1]) / 9; //Add below

				number_array[c][r] = count; //update array
			}
		}

	}

}
void fill_number_array(int **number_array, int cols, int rows, int &cells, int &bomb_count){
	//Fills out the number array
	double bombs;

	
	//---------------------------------------------
	/*	Requirement #14: Demonstrate passing mechanisms
	In this sub-function, I utilitze both pass by reference
	and by value. The column and row counts, I only needed the 
	values to pass along to other sub-functions. For the cells and
	bomb count, I wanted to actually change their value
	for when they are needed by the main function*/
	//---------------------------------------------
	cells = cols * rows; //Calculate number of cells on the board

	//Calculate the appropriate number of bombs for this size board
	bombs = (cells*cells) / 5000;
	bombs = bombs + (cells / 10) + 1;

	//---------------------------------------------
	//	Requirement #03: Demonstrate explicit type casting
	//---------------------------------------------
	bomb_count = int(bombs);

	//Fill the number board with zeros
	zero_number_array(number_array, cols, rows);

	//Add the bombs (9s) to the number board
	add_bombs_to_number_array(number_array, cols, rows, bomb_count);

	//Add the 'clue' numbers to the number board
	add_nbrs_to_number_array(number_array, rows, cols);

}
//Display Progress Board***<Bombsweeper>***
void cout_2d_array(int **number_array, int cols, int rows){
	//prints a 2D array of ints

	//---------------------------------------------
	/*	Requirement #15: Demonstrate Function Overloading
	I use the char version of this function to print out the game 
	board. This version, the integer version, I don't actually
	utilitze in my code, but I used it frequently when I was developing
	and debugging in order to see my integer array.
	
	The char version of this overloaded function is below.*/
	//---------------------------------------------

	//Prints an array of ints - was only used for debugging
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			cout << number_array[c][r];
		}
		cout << endl;
	}

}
void cout_2d_array(char **prog_array, int cols, int rows){
	//Prints a 2D array of Chars
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			cout << prog_array[c][r];
		}
		cout << endl;
	}

}
void add_data_to_print_array(char **print_array, char **prog_array, int cols, int rows, int COL_SHIFT, int ROW_SHIFT){
	// Adds the data portion to the print array
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			int mod_c = c % 2;
			int mod_r = r % 2;

			int true_c = (c - COL_SHIFT - 1) / 2;
			int true_r = (r - ROW_SHIFT - 1) / 2;

			if (c < COL_SHIFT || r < ROW_SHIFT){
				print_array[c][r] = ' '; //Place holder if not actual data
			}
			else {
				//Actual Board data
				if ((mod_c + mod_r) == 0){
					print_array[c][r] = '+';
				}
				else if ((mod_c + mod_r) == 2) {
					print_array[c][r] = prog_array[true_c][true_r];
				}
				else if (mod_c == 1) {
					print_array[c][r] = '-';
				}
				else if (mod_r == 1){
					print_array[c][r] = '|';
				}
			}

		}
	}

}
void add_rc_titles(char **print_array, int cols, int rows){
	//Adds the titles COLUMN and ROW to the print array

	//---------------------------------------------
	/*	Requirement #16: Demonstrate c-strings
	I realize that the two c-strings below aren't
	c-strings in the traditional sense, but I actually
	did use their array-like functionality to help build my game board.*/
	//---------------------------------------------
	char c_label[7] = { 'C', 'O', 'L', 'U', 'M', 'N', '\0' };
	int c_label_row = 1, c_label_col_beg = 2, c_label_col_end;
	c_label_col_end = c_label_col_beg + 5;

	char r_label[4] = { 'R', 'O', 'W', '\0' };
	int r_label_col = 0, r_label_row_beg = 3, r_label_col_end;
	r_label_col_end = r_label_row_beg + 2;

	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			//Replace the column label
			if (r == c_label_row){ //Find the row
				if (c >= c_label_col_beg && c <= c_label_col_end){ //Find the columns
					print_array[c][r] = c_label[c - c_label_col_beg]; //Set changes
				}
			}

			//Replace the row label
			if (c == r_label_col){ //find the col
				if (r >= r_label_row_beg && r <= r_label_col_end){ //find the rows
					print_array[c][r] = r_label[r - r_label_row_beg]; //set changes
				}
			}
		}
	}

}
void add_rc_labels(char **print_array, int cols, int rows, int COL_SHIFT, int ROW_SHIFT){
	//Adds the lables (A, B, C, 01, 02, 03) to the rows and columns

	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			int mod_c = c % 2;
			int mod_r = r % 2;

			int true_c = (c - COL_SHIFT - 1) / 2;
			int true_r = (r - ROW_SHIFT - 1) / 2;

			if (r > ROW_SHIFT && mod_r == 1){ //If the row is in the data rows and is an odd row..
				if (c == 2) print_array[c][r] = (true_r / 10) + 48; //48 is zero in ASCII
				if (c == 3)print_array[c][r] = (true_r % 10) + 48; //48 is zero in ASCII
			}

			if (c > COL_SHIFT && mod_c == 1){ //If the col is in the data cols and is an odd col..
				if (r == 3) print_array[c][r] = true_c + 65; //65 is 'A' in ASCII

			}

		}
	}

}
void display_progress_array(char **prog_array, int cols, int rows, int bomb_count){
	//Displays the current game board for the user

	int new_cols, new_rows;
	
	const int COL_SHIFT = 4; //Shift must be even number
	const int ROW_SHIFT = 4; //Shift must be even number

	new_cols = cols * 2 + 1 + COL_SHIFT;
	new_rows = rows * 2 + 1 + ROW_SHIFT;
	
	/* Declare the array for printing */
	char **print_array;
	print_array = new char*[new_cols];
	for (int c = 0; c < new_cols; c++){
		print_array[c] = new char[new_rows];
	}

	/* Fill the array using actual data */
	add_data_to_print_array(print_array, prog_array, new_cols, new_rows, COL_SHIFT, ROW_SHIFT);

	/*Add Column and Row Titles to the print array*/
	add_rc_titles(print_array, new_cols, new_rows);

	/*Add the Column and row lables to the print array*/
	add_rc_labels(print_array, new_cols, new_rows, COL_SHIFT, ROW_SHIFT);

	/* Print the title */
	cout << "---- * BOMBSWEEPER * ----" << endl ;

	/* Print the array */
	cout_2d_array(print_array, new_cols, new_rows);
	cout << endl;

}
void display_bomb_count(int bomb_count){
	//Displays the count of bombs on the board.
	cout << "There are " << bomb_count << " bombs on this board." << endl;

}
void display_flags_left(char **prog_array, int cols, int rows, int bomb_count){
	//Tells the user how many flags he has left
	int flags_left = bomb_count;

	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			if (prog_array[c][r] == 'F') flags_left = flags_left - 1;
		}
	}

	cout << "You have " << flags_left << " flag(s) left to use." << endl << endl;

}
//Update Progress Board***<Bombsweeper>***
void zero_progress_array(char **print_array, int cols, int rows){
	//Fill answer board
	for (int c = 0; c < cols; c++){
		for (int r = 0; r < rows; r++){
			print_array[c][r] = ' ';
		}
	}

}
void flag_progress(char **prog_array, int user_choice){
	//Toggle flag if user chooses
	int uc = user_choice / 1000;
	int ur = user_choice % 1000;

	if (prog_array[uc][ur] == ' '){
		prog_array[uc][ur] = 'F';
	} else {
		prog_array[uc][ur] = ' ';
	}
	
}
void step_progress(char **prog_array, int **number_array, int user_choice, bool &hit_a_bomb, int cols, int rows){
	//Reveal bomb, one or more boxes, depending on what is in box.
	int uc = user_choice / 1000;
	int ur = user_choice % 1000;

	if (number_array[uc][ur] == 9){
		hit_a_bomb = 1;
	} else if (number_array[uc][ur] != 0) { //If it's not zero, just reveal that number
		prog_array[uc][ur] = number_array[uc][ur] + 48; 
	} else { //If it is zero, reveal all 8 numbers around the user's choice
		prog_array[uc][ur] = number_array[uc][ur] + 48; //Reveal the number

		if (uc != 0){ //If you're not in the first col
			prog_array[uc - 1][ur] = number_array[uc - 1][ur] + 48; //Left
			if (ur != 0) prog_array[uc - 1][ur - 1] = number_array[uc - 1][ur - 1] + 48;  //Upper Left
			if (ur != rows - 1) prog_array[uc - 1][ur + 1] = number_array[uc - 1][ur + 1] + 48; //Lower Left
		}

		if (uc != cols - 1){ //If you're not in the last col
			prog_array[uc + 1][ur] = number_array[uc + 1][ur] + 48; //right
			if (ur != 0) prog_array[uc + 1][ur - 1] = number_array[uc + 1][ur - 1] + 48; //Upper Right
			if (ur != rows - 1) prog_array[uc + 1][ur + 1] = number_array[uc + 1][ur + 1] + 48; //Lower Right
		}

		if (ur != 0) prog_array[uc][ur - 1] = number_array[uc][ur - 1] + 48; //Add above
		if (ur != rows - 1) prog_array[uc][ur + 1] = number_array[uc][ur + 1] + 48; //Add above
	
	}
	
}
void reveal_progress(char **prog_array, int **number_array, int cols, int rows){
	//Reveals entire board at end of game
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			if (number_array[c][r] == 9){
				prog_array[c][r] = '*';
			} else {
				prog_array[c][r] = number_array[c][r] + 48;
			}

		}
	}

}
//User Interaction***<Bombsweeper>***
int letter_lookup(char letter){
	//Letter lookup for ASCII code
	switch (letter){
	case 'A': return 0; case 'B': return 1; case 'C': return 2; case 'D': return 3;
	case 'E': return 4; case 'F': return 5; case 'G': return 6; case 'H': return 7;
	case 'I': return 8; case 'J': return 9; case 'K': return 10; case 'L': return 11;
	case 'M': return 12; case 'N': return 13; case 'O': return 14; case 'P': return 15;
	default: return 0;
	}
}
bool col_out_of_range(char user_col, int cols){
	//cycle through the column letters and see if the user's col is good
	for (int c = 0; c < cols; c++){
		if (user_col == c + 65) return 0; 
	}

	return 1;

}
bool choice_is_invalid(string user_input, int cols, int rows, char **prog_array){
	//Checks to make sure the user's choice is valid

	//Invalid if length is not three
	if (user_input.length() != 3) return 1; 

	//Invalid if the letter is not in range
	if (col_out_of_range(user_input.at(0), cols)) return 1; 

	if (user_input.at(1)<'0' || user_input.at(1)>'9') return 1; //Check if fist char is number
	if (user_input.at(2)<'0' || user_input.at(2)>'9') return 1; //Check if second char is number

	//Convert row input to int and check for range
	int row_code = atoi(user_input.substr(1, 2).c_str());
	if (row_code>rows - 1) return 1; 

	//Check to make sure the space hasn't been selected yet
	int code = convert_to_code(user_input);
	int uc = code / 1000;
	int ur = code % 1000;
	if (prog_array[uc][ur] != ' '&&prog_array[uc][ur] != 'F') return 1;


	return 0;
}
int convert_to_code(string user_input){
	//Convert's user string input (ie B01) into an int code (ie 1001)
	int code, col_code, row_code;
	
	col_code = letter_lookup(user_input.at(0));
	col_code = col_code * 1000;

	string row_str = user_input.substr(1, 2);
	row_code = atoi(row_str.c_str());

	code = col_code + row_code;
	
	return code;
}
int get_user_choice(int cols, int rows, string &user_choice_string,char **prog_array){
	//Gets users choice for which box to act upon
	string user_input;

	cout << "Please select a row and column." << endl;
	cout << "Your choice should be the column letter " << endl;
	cout << "followed by the row number (ie 'B02'):" << endl;

	//---------------------------------------------
	//	Requirement #02: Demonstrate simple input
	//---------------------------------------------
	getline(cin, user_input);
	
	while (choice_is_invalid(user_input, cols, rows, prog_array)){
		cout << "Your selection was invalid, please re-enter:" << endl;
		getline(cin, user_input);
	}
	
	user_choice_string = user_input;
	return convert_to_code(user_input);
}
char get_flag_or_step(){
	//Gets whether the user would like to flag a box or step on it
	string user_input;

	cout << "Flag this location ('F') or step on it ('S'): ";

	getline(cin, user_input);
	//---------------------------------------------
	//	Requirement #05: Demonstrate logical operators
	//---------------------------------------------*/
	while (user_input.length() != 1 || (user_input.at(0) != 'F' && user_input.at(0) != 'S')){
		cout << "Your selection was invalid, please re-enter: ";
		getline(cin, user_input);
	}

	return user_input.at(0);
}
//Evaluate Winning conditions***<Bombsweeper>***
int count_safe_cells(char **prog_array, int cols, int rows){
	//Counts the current number of cells the user has stepped into safely
	int count = 0;
	
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			if (prog_array[c][r] >= '0'&&prog_array[c][r] <= '8'){
				count = count + 1;
			}
		}
	}

	return count;
}
//Bombsweeper Application***<Bombsweeper>***
void bombsweeper(){
	//The main game application

	//---------------------------------------------
	//	Requirement #26: Something awesome :)
	//	I'm quite proud of my bombsweeper game!
	//---------------------------------------------

	string keep_playing = "y";

	//---------------------------------------------
	//	Requirement #07: Demonstrate a loop
	//---------------------------------------------
	while (keep_playing == "y"){
		clear_console(); //clear the console

		//---------------------------------------------
		//	Requirement #01: Demonstrate simple output	
		//---------------------------------------------
		cout << "---- Welcome to Bombsweeper! ----" << endl << endl;

		int cols = get_user_cols();
		int rows = get_user_rows();

		int cells = 0, bomb_count = 0;
		int user_choice;
		string user_choice_string;

		//Initialize Answer Board and Number Board
		//---------------------------------------------
		//	Requirement #18: Demonstrate multi-dimensional array	
		//---------------------------------------------
		int **number_array; //This hold the ints of the board
		char **prog_array; //This holds the user's progress
		prog_array = new char*[cols]; //Can these be outsourced?
		number_array = new int*[cols];
		for (int c = 0; c < cols; c++){
			prog_array[c] = new char[rows];
			number_array[c] = new int[rows];
		}

		//Fill number board
		fill_number_array(number_array, cols, rows, cells, bomb_count);

		//Fill progress board with all spaces
		zero_progress_array(prog_array, cols, rows);

		bool hit_a_bomb = 0; //Set hit a bomb to zero as the default

		int safe_cells_target = cells - bomb_count; //Set safe cell target
		int safe_cells_count = 0; //Set current safe cells

		clear_console();
		while (hit_a_bomb != 1 && safe_cells_count != safe_cells_target) {
			//Display the board
			display_progress_array(prog_array, cols, rows, bomb_count);

			//Display bombs on this board
			display_bomb_count(bomb_count);

			//Display user's flags left
			display_flags_left(prog_array, cols, rows, bomb_count);

			//Get the code for the user's choice
			user_choice = get_user_choice(cols, rows,user_choice_string, prog_array);

			//Get whether the user would like to flag or step on the location
			if (get_flag_or_step() == 'S'){
				//Update the board for that step choice
				step_progress(prog_array, number_array, user_choice, hit_a_bomb, cols, rows);
			}
			else {
				//Flag the board here
				flag_progress(prog_array, user_choice);
			}

			//Count the safe cells before starting next loop
			safe_cells_count = count_safe_cells(prog_array, cols, rows);

			//clear the console
			clear_console();
		}

		reveal_progress(prog_array, number_array, cols, rows); //Update prog array for final reveal
		display_progress_array(prog_array, cols, rows, bomb_count); //Display board

		//---------------------------------------------
		//	Requirement #04: Demonstrate conditional statements
		//---------------------------------------------
		if (hit_a_bomb == 1){
			cout << "You hit a bomb at " << user_choice_string << "! Sorry!" << endl << endl;
		}
		else {
			cout << "YOU WIN! Congratuations!" << endl;
		}

		cout << "Would you like to play again?" << endl;
		cout << "Enter 'y' to keep playing or any other key to quit: ";

		getline(cin, keep_playing);

		clear_console();
	}

}

//Main Function****************************************************************************************************************
int main(int argc, char *argv[]){
	string user_name = " Player 1";

	//---------------------------------------------
	//	Requirement #20: Demonstrate command line argument (user's name)
	//---------------------------------------------
	//Command line argument is the user's name
	if (argc > 1){
		user_name = "";
		for (int i = 1; i<argc; i++){ 
			user_name = user_name + " " + argv[i];
		}
	}

	//---------------------------------------------
	/* Requirement #12: Demonstrates Functional Decomposition
	Most of my functions are support function for my Bombsweeper
	program. I broke each portion of that program down in function
	and then wrote support function for each of those portions if necessary.
	In terms of function ordering, I tried to group similar functions together.
	In general, I tried to order them from least dependent on other functions at
	the top, to most depend on others at the bottom (note that main is at the bottom,
	since it's dependent on all the others)	*/
	//---------------------------------------------

	string menu_entry;
	while (menu_entry != QUIT_KEY){

		clear_console();
		
		display_main_menu(user_name); //display the menu
		menu_entry = get_menu_entry(); //get menu entry from the user

		if (menu_entry == BOMBSWEEPER_KEY){
			bombsweeper();
		} else if (menu_entry == INSTRUCTIONS_KEY) {
			instructions();
		} else if (menu_entry == INT_DB_KEY) {
			the_integer_encyclopedia();
		}

	} return 0;

}
