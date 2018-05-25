#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

#include "support.h"
#define NEW_LINES 50

bool is_not_posint(string user_input){
	//Return 0 if it is a posititve integer or zero

	//Invalid if empty
	if (user_input == "") return 1;

	//Invalid if any character is outside of 0-9
	for (unsigned int i = 0; i < user_input.length(); i++){
		if (user_input.at(i) < '0' || user_input.at(i) > '9') return 1;
	}

	//Otherwise is okay
	return 0;

}
void clear_console(){
	for (int i = 0; i < NEW_LINES; i++){
		cout << endl;
	}
}
bool is_not_alphanumeric(string user_input){
	//is not alpha, numeric
	//empty string is not anu
	if (user_input == "") return 1;

	//for each character
	for (unsigned int i = 0; i < user_input.length(); i++){
		bool char_is_okay = 0;

		char chr = user_input.at(i);

		if (chr >= 'a'&&chr <= 'z') char_is_okay = 1;
		if (chr >= 'A'&&chr <= 'Z') char_is_okay = 1;
		if (chr >= '0'&&chr <= '9') char_is_okay = 1;

		//if the char was never set to okay, then it's invalid
		if (char_is_okay == 0) return 1;

	}

	//if the string is not empty and each char passes the test
	//then the string is valid
	return 0;
}
bool is_not_posdec(string user_input){
	//Return 0 if it is a posititve decimal

	//Invalid if empty
	if (user_input == "") return 1;

	//Invalid if there are more than 1 periods
	int pd_count = 0;
	for (unsigned int i = 0; i < user_input.length(); i++){
		if (user_input.at(i) == '.') pd_count = pd_count + 1;
	}
	if (pd_count > 1) return 1;

	//Invalid if any character is outside of 0-9 and not a dot
	for (unsigned int i = 0; i < user_input.length(); i++){
		char chr = user_input.at(i);
		if ((chr < '0' || chr > '9') && chr != '.') return 1;
	}

	//Otherwise is okay
	return 0;

}
bool is_not_yn(string user_input){
	//Return 0 if it is a y or an n

	//Invalid if length is not 1
	if (user_input.length() != 1) return 1;

	//Invalid if 1st char is not y or n
	if (user_input.at(0) != 'y' && user_input.at(0) != 'n') return 1;

	return 0;

}
string upper(string user_input){
	//Returns a string variable that is the upper case of user_input

	//Return nothing if empty string
	if (user_input == "") return "";

	string s = user_input;
	char this_char;
	int temp_int;

	//For each letter in the input
	for (unsigned int i = 0; i < s.length(); i++){

		//if the letter is between a and z
		if (s.at(i) >= 'a'&& s.at(i) <= 'z'){

			//get the corresponding int for this letter
			temp_int = char_lookup(s.at(i));

			//Take 32 away from that int
			temp_int = temp_int - 32;

			//set this char to that into
			this_char = temp_int;

			//switch out the char
			s.at(i) = this_char;
		}

	}

	return s;
}
int char_lookup(char letter_input){
	//Looks up the char code for any letter or number
	char this_char;

	for (int i = 47; i < 123; i++){
		this_char = i;

		if (this_char == letter_input){
			return i;
		}
	}

	return 0;
}
string return_only_uppers(string user_input){
	
	//Return nothing if empty string
	if (user_input == "") return "";

	string new_s;

	//Strip out everything but the A to Z chars
	//For each char
	for (unsigned int i = 0; i < user_input.length(); i++){
		//If the char is between A and Z
		if (user_input.at(i) >= 'A' && user_input.at(i) <= 'Z'){
			//add it to the new string
			new_s = new_s + user_input.at(i);
		}
	}

	return new_s;
}
string return_upper_alpha(){
	return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}
bool is_not_alpha(string user_input){
	//Checks to make sure each character is in the alphabet

	//empty string is not
	if (user_input == "") return 1;

	//for each character
	for (unsigned int i = 0; i < user_input.length(); i++){
		bool char_is_okay = 0;

		char chr = user_input.at(i);

		if (chr >= 'a'&&chr <= 'z') char_is_okay = 1;
		if (chr >= 'A'&&chr <= 'Z') char_is_okay = 1;

		//if the char was never set to okay, then it's invalid
		if (char_is_okay == 0) return 1;

	}

	//if the string is not empty and each char passes the test
	//then the string is valid
	return 0;
}
bool int_is_not_between(string user_input, int min, int max){

	if (is_not_posint(user_input)) return 1; //invalid if not pos int

	int temp_int = atoi(user_input.c_str());
	if (temp_int<min || temp_int>max) return 1; //invalid if ouside range

	return 0;


}
int get_user_posint(){
	string user_input;

	getline(cin, user_input);
	while (is_not_posint(user_input)){
		cout << "Invalid entry. Please re-enter:" << endl;
		getline(cin, user_input);
	}

	return atoi(user_input.c_str());


}
bool is_not_valid_char(const string& valid_chars, const string& user_input){
	if (user_input.length() != 1) return 1;

	//return zero if the user input is not found
	if (valid_chars.find(user_input.at(0)) == string::npos) return 1;

	return 0;

}
string get_user_choice(const string& valid_chars){
	string user_input;

	getline(cin, user_input);
	while (is_not_valid_char(valid_chars, user_input)){
		cout << "Invalid input. Please re-enter:" << endl;
		getline(cin, user_input);
	}

	return user_input;
}

