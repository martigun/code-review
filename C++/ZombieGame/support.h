
#ifndef MARTIGUN_SUPPORT
#define MARTIGUN_SUPPORT

#include <string>
using std::string;

bool is_not_posint(string user_input);

bool is_not_alphanumeric(string user_input);
//Checks string and returns 1 if any character is not alpha numeric

bool is_not_posdec(string user_input);
bool is_not_yn(string user_input);
string upper(string user_input);
int char_lookup(char letter_input);
string return_only_uppers(string user_input);
string return_upper_alpha();
bool is_not_alpha(string user_input);
bool int_is_not_between(string user_input, int min, int max);
int get_user_posint();
bool is_not_valid_char(const string& valid_chars, const string& user_input);
string get_user_choice(const string& valid_chars);

void clear_console();

#endif



