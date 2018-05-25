#include "final_support.h"

#define BACKPACK_CAPACITY 4

void check_shelf(room* &current_room, bool& casserole_made){

	//return if there is already casserole on the hallway shelf
	if (current_room->get_casserole() == true){
		cout << "There is some tuna-fish casserole on this shelf!" << endl;
		return;
	}

	//return if the casserole hasn't been made
	if (casserole_made == false){
		cout << "This shelf is empty. You don't have the right food to put on this shelf." << endl;
		cout << "You have a feeling that you should put tuna-fish casserole on this shelf..." << endl;
		return;
	}
	
	//else, you get the option to place the casserole!
	cout << "Would you like to place some casserole on this shelf?(y/n)" << endl;
	string user_input = get_user_choice("yn");

	//return if user decides not to
	if (user_input == "n"){
		cout << "You did not put tuna-fish casserole on the shelf." << endl;
		cout << "You immediately get a strange feeling of regret..." << endl;
		return;
	}

	//If user does..
	current_room->set_casserole_true();
	cout << "You have put some tuna-fish casserole on this shelf!" << endl;
	cout << "You get a feeling this was a good decision!" << endl;
}
void print_backpack(const vector<string> &backpack){

	//print empty if backback is empty
	if (backpack.empty() == true) {
		cout << "~~ Backback is empty. ~~" << endl;
		return;
	}

	//backpack is not empty
	cout << "~~~ Backpack Contents ~~~" << endl;
	cout << endl;
	for (unsigned int i = 0; i < backpack.size(); i++){
		cout << "(" << (i + 1) << ") " << backpack[i] << endl;
	}
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
}
void drop_item(room* &current_room, vector<string> &backpack){
	string room_item = current_room->get_item();
	string user_input;

	//cannot drop if backback is empty
	if (backpack.empty() == true) { 
		cout << "Backback is empty. No items to drop." << endl;
		return;
	}

	//cannot drop if there is something else in the room
	if (room_item != "nothing"){
		cout << "Cannot drop item in this room. " << endl;
		cout << "There is already " << room_item << " in this room." << endl;
		cout << "You must go to a room with nothing on the floor" << endl;
		cout << "If you'd like to drop an item." << endl;
		return;
	}
	
	//ask user which item to drop
	cout << "Which item would you like to drop?" << endl;
	cout << endl;
	print_backpack(backpack);
	getline(cin, user_input);
	while (int_is_not_between(user_input, 1, backpack.size())){
		cout << "Invalid input. Please re-enter:" << endl;
		getline(cin, user_input);
	}

	//convert item to int
	int drop_item = atoi(user_input.c_str());
	drop_item = drop_item - 1;

	//set user input to the drop item
	user_input = backpack[drop_item];

	//cannot drop tuna-fish casserole
	if (user_input == "tuna-fish casserole"){
		cout << "You cannot drop the casserole." << endl;
		cout << "Try leaving some on a shelf instead." << endl;
		return;
	}

	//set current room item to this item
	current_room->set_item(backpack[drop_item]);

	//erase the item from your pack
	backpack.erase(backpack.begin() + drop_item);
	
	//message user
	cout << "You have dropped " << user_input << "." << endl;

}
void go_next_room(room* &current_room, room* &next_room){
	string user_input;

	//prompt user
	cout << endl;
	cout << "Which way would you like to go?" << endl;
	cout << "(n) North" << endl;
	cout << "(e) East" << endl;
	cout << "(s) South" << endl;
	cout << "(w) West" << endl;
	cout << endl;

	//get the user's direction
	user_input = get_user_choice("nesw");

	//set next room to the ptr specified by the user
	next_room = current_room->get_room_ptr(user_input);

	//if next room is null, print the wall text, else, move to the next room
	if (next_room == NULL){
		cout << "You ran into a wall. You are still in the same room." << endl;
	} else {
		current_room = next_room; //change current room into the next room
		cout << "You carefully step into the next room over..." << endl;
	}

}
void look_down(room* &current_room, vector<string> &backpack){
	string user_input;

	//set room item as the item on the floor
	string room_item = current_room->get_item();
	cout << "You look down and see " << room_item << "." << endl;

	//return if the item is nothing
	if (room_item == "nothing") return;

	//ask user if he want to pick it up
	cout << "Would you like to pick the item up?(y/n)" << endl;
	user_input = get_user_choice("yn");

	//return if user says no
	if (user_input == "n") return;

	//return if pack is full
	if (backpack.size() == BACKPACK_CAPACITY){
		cout << "Your backpack is full. Cannot pick up this item." << endl;
		cout << "You must drop an item from your backback if you want this item." << endl;
		cout << "Items cannot be dropped in this room, since there is already an item here." << endl;
		return;
	}

	//Finish the process
	backpack.push_back(room_item); //add to vector
	current_room->set_item("nothing"); //set item in room to nothing
	cout << "The item " << room_item << " has been added to your backpack." << endl;
	
}
void load_oven(vector<string> &backpack,bool& casserole_made){

	//wrong if not 4 elements
	if (backpack.size() != BACKPACK_CAPACITY){
		cout << "These ingredients aren't correct!" << endl;
		cout << "Cannot load them into the oven." << endl;
		cout << "Tip: Read the recipe" << endl;
		return;
	}

	//wrong if not one of the four ingredients
	for (unsigned int i = 0; i < backpack.size(); i++){
		if (backpack[i] != "tuna fish" && backpack[i] != "cheese" &&
		backpack[i] != "noodles" && backpack[i] != "soup") {
			cout << "These ingredients aren't correct!" << endl;
			cout << "Cannot load them into the oven." << endl;
			cout << "Tip: Read the recipe" << endl;
			return;
		}
	}

	//if correct, clear backback and load with tuna-fish casserole
	cout << "The ingredients are correct!" << endl;
	cout << "You have made tuna-fish casserole!" << endl;
	cout << "It is now in your backpack." << endl;
	backpack.clear();
	backpack.push_back("tuna-fish casserole");
	casserole_made = true;
	
}
bool victory_conditions_met(vector<room*> &hallways){

	//go through each of the objects in the vector
	for (unsigned int i = 0; i < hallways.size(); i++){

		//if casserole is false in any of the hallways, return zero
		if (hallways[i]->get_casserole() == false) return 0;

	}

	//otherwise, return true
	return 1;

}
void print_victory(){

	cout << "!  !  !  !  !  !  !  !  !  !" << endl;
	cout << "The zombies from both sides of the mansion have" << endl;
	cout << " followed your tuna-casserole baits into the courtyard!" << endl;
	cout << "Hearing the commotion, you rush to the courtyard to see what is happening." << endl;
	cout << "You watch as the zombies destroy each other." << endl;
	cout << "The mansion is now zombie free! You have won!" << endl;
	cout << "Congratulations!" << endl;
	cout << "!  !  !  !  !  !  !  !  !  !" << endl;
	
}
void zombie_game(){
	
	//make pointers to current room and next room
	room *current_room, *next_room = NULL;

	//set up vector of hallways to check for victory
	vector<room*> hallways;

	//create a stringvector backpack
	vector<string> backpack;
	//vector<string> backpack{ "a", "b", "c", "d" };//for testing
	
	//set up the map and set current room
	final_setup(current_room, hallways);
	
	//set other variables
	int turn_number = 0;
	bool game_continues = true, casserole_made = false;
	string user_input, valid_chars;

	while (game_continues){

		//clear console and increment turn number
		turn_number++;
		clear_console();

		//display standard and derived hud for user- return valid character choices
		valid_chars = current_room->display_standard_hud(turn_number);
		valid_chars = valid_chars + current_room->display_derived_hud();

		//get the user's choice
		user_input = get_user_choice(valid_chars);
		
		if (user_input == "g") go_next_room(current_room, next_room); //Go to the next room
		if (user_input == "b") print_backpack(backpack); //Look in my backpack
		if (user_input == "r") drop_item(current_room, backpack); //Drop item
		if (user_input == "d") look_down(current_room, backpack);	//Look down
		if (user_input == "o") load_oven(backpack,casserole_made); //Load oven
		if (user_input == "s") check_shelf(current_room, casserole_made); //check shelf
		
		//Press enter to start loop over
		cout << endl;
		cout << "Press Enter to continue..." << endl;
		getline(cin, user_input);

		//check for victory
		if (victory_conditions_met(hallways)){
			print_victory();
			game_continues = false;
		}	
	}
}
void print_game_goal(){
	cout << "The goal is to lure the zombies into the courtyard, using cooked" << endl;
	cout << "tuna-fish casserole. Use the map to help navigate the mansion." << endl;
	cout << endl;
	cout << "To achieve victory in this game, you must do the following..." << endl;
	cout << "1. Navigate the mansion and add the following items to you backpack:" << endl;
	cout << "     a) tuna-fish" << endl;
	cout << "     b) noodles" << endl;
	cout << "     c) cheese" << endl;
	cout << "     d) soup" << endl;
	cout << "   Disgregard all the other items in the mansion." << endl;
	cout << "2. After gathering the 4 items above, head to the kitchen." << endl;
	cout << "   Once in the kichen, load the items into the oven to make the" << endl;
	cout << "   tuna-fish casserole." << endl;
	cout << "3. Now that the casserole is baked and in your backpack, put some" << endl;
	cout << "   casserole on all the shelves in the hallways. There are seven (7)" << endl;
	cout << "   shelves in total." << endl;
	cout << endl;
	cout << "Once the casserole is on the shelves, the zombies will both be lured" << endl;
	cout << "into the courtyard and destory each other, allowing you to be safe!" << endl;

}
int main(){

	bool keep_playing = true;
	string user_input;

	while (keep_playing){

		cout << "---**  Zombie Mansion Game  **---" << endl;
		cout << "Welcome to the Zombie Mansion Game!" << endl;
		cout << "Would you like see the goal of the game?(y/n)" << endl;
		user_input = get_user_choice("yn");
		cout << endl;
		if (user_input == "y") print_game_goal();
		cout << "Press Enter to start the game..." << endl;
		getline(cin, user_input);
		
		//run the game
		zombie_game();

		//prompt user
		cout << endl;
		cout << "Would you like to play again?(y/n)" << endl;
		user_input = get_user_choice("yn");
		if (user_input == "n") keep_playing = false;
	}
	
	return 0;
}