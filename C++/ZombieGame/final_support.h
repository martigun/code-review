#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::getline;

#include <cstdlib>
using std::atoi;

#include <ctime>
using std::time;

#include <vector>
using std::vector;/*       Including Libraries     */

#include "support.h"

class room{
protected:
	string address;
	room *n, *e, *s, *w;
	string room_type;
	string item;

public:
	
	//gets and sets
	string get_type(){ return this->room_type; }
	string get_item(){ return this->item; }
	string get_address(){ return this->address; }
	virtual bool get_casserole(){ return 0; };
	virtual void set_casserole_true() {};

	//get the room pointer
	room* get_room_ptr(string direction){
		if (direction == "n") return this->n;
		if (direction == "e") return this->e;
		if (direction == "s") return this->s;
		if (direction == "w") return this->w;

		return NULL;
	}

	//set room variables
	virtual void set_room_vars(room* n, room* e, room* s, room* w, const string& item){
		this->n = n;
		this->e = e;
		this->s = s;
		this->w = w;

		this->item = item;
	}

	//set item
	void set_item(const string& item){this->item = item;}

	//display standard hud
	virtual string display_standard_hud(const int& turn_nbr){
		cout << "-----------------------------------------" << endl;
		cout << "This is turn number: " << turn_nbr << endl;
		cout << "-----------------------------------------" << endl;
		this->display_welcome_text();
		cout << endl;
		cout << "The paint on the ceiling reads: " << this->address << "." << endl;
		cout << "What would you like to do?" << endl;
		cout << endl;
		cout << "(g) Go to another room" << endl;
		cout << "(b) Check my backpack" << endl;
		cout << "(r) Drop item from backpack" << endl;
		cout << "(d) Look down" << endl;

		return "gbrd";
	}

	//display welcome text
	virtual void display_welcome_text(){};

	//display derived hud
	virtual string display_derived_hud() { return ""; };
};

class bathroom :public room{
public:
	bathroom(string address){
		this->address = address;
		this->room_type = "bathroom";
	}

	virtual void display_welcome_text(){
		cout << "You are in a bathroom." << endl;
		cout << "This place stinks!" << endl;
		cout << "Is there something on the floor?" << endl;
	}
};
class bedroom :public room{
public:
	bedroom(string address){
		this->address = address;
		this->room_type = "bedroom";
	}

	virtual void display_welcome_text(){
		cout << "You are in a bedroom." << endl;
		cout << "There are silk sheets on a large waterbed." << endl;
	}
};
class courtyard :public room{
public:
	courtyard(string address){
		this->address = address;
		this->room_type = "courtyard";
	}

	virtual void display_welcome_text(){
		cout << "You are in a courtyard." << endl;
		cout << "It looks like a perfect arena " << endl;
		cout << "for two zombies to fight each other." << endl;
		cout << "If only there were a way to lure them into the courtyard..." << endl;
	}
};
class dining_room :public room{
public:
	dining_room(string address){
		this->address = address;
		this->room_type = "dining_room";
	}

	virtual void display_welcome_text(){
		cout << "You are in a dining room." << endl;
		cout << "There is a massive dining table with " << endl;
		cout << "a silver chandelier hanging above it." << endl;
	}
};
class foyer :public room{
public:
	foyer(string address){
		this->address = address;
		this->room_type = "foyer";
	}

	virtual void display_welcome_text(){
		cout << "You are in a foyer of the mansion." << endl;
		cout << "You hear the faint sounds of zombies moaning and stumbling." << endl;
		cout << "You hear one on the far east side and one on the far west." << endl;
		cout << "You would feel much safer if you could get rid of the zombies..." << endl;
		cout << endl;

	}
};
class hallway:public room{
private:
	bool has_casserole;
public:
	hallway(string address){
		this->address = address;
		this->room_type = "hallway";
		this->has_casserole = false;
	}

	void set_casserole_true(){ this->has_casserole = true; }
	bool get_casserole(){ return this->has_casserole; }

	virtual void display_welcome_text(){
		cout << "You are in a hallway." << endl;
		cout << "You notice a shelf on the wall." << endl;
	}

	virtual string display_derived_hud(){
		cout << "(s) Look at the shelf." << endl;

		return "s";
	}
};
class kitchen :public room{
private:

public:
	kitchen(string address){
		this->address = address;
		this->room_type = "kitchen";
	}

	virtual void display_welcome_text(){
		cout << "You are in a kitchen." << endl;
		cout << "Above the oven you see a recipe:" << endl;
		cout << endl;
		cout << "==== Tuna Fish Casserole Recipe ===" << endl;
		cout << "||  - Tuna Fish                   ||" << endl;
		cout << "||  - Cheese                      ||" << endl;
		cout << "||  - Noodles                     ||" << endl;
		cout << "||  - Soup                        ||" << endl;
		cout << "===================================" << endl;
		cout << endl;
	}

	virtual string display_derived_hud(){
		cout << "(o) Load backpack contents into the oven." << endl;

		return "o";
	}

};
class library :public room{
public:
	library(string address){
		this->address = address;
		this->room_type = "library";
	}


	virtual void display_welcome_text(){
		cout << "You are in a library." << endl;
		cout << "It smells of mahogany and leather." << endl;
	}
};
class stairwell :public room{
private:

public:
	stairwell(string address){
		this->address = address;
		this->room_type = "stairwell";
	}

	virtual void display_welcome_text(){
		cout << "You are in a stairwell." << endl;
		cout << "The stairs spiral upwards, but you are" << endl;
		cout << "unable to go up, because they are boarded up at the top." << endl;
	}
};
class zombie_room :public room{
public:
	zombie_room(string address){
		this->address = address;
		this->room_type = "zombie_room";
	}

	virtual void display_welcome_text(){
		cout << "You are in a room with a zombie!" << endl;
		cout << "Though it moves slowly, you can tell it hungers for you!" << endl;
		cout << "Also, it looks like it wants tuna-fish casserole. Weird." << endl;
		cout << "You stand near the door in order to escape quickly if need be." << endl;
	}
};
void final_setup(room* &current_room, vector<room*> &hallways){
	room* a1 = new zombie_room("a1");
	room* b1 = new hallway("b1");
	room* c1 = new hallway("c1");
	room* d1 = new hallway("d1");
	room* e1 = new hallway("e1");
	room* f1 = new dining_room("f1");
	room* g1 = new kitchen("g1");
	room* a2 = new bedroom("a2");
	room* b2 = new bedroom("b2");
	room* c2 = new library("c2");
	room* d2 = new foyer("d2");
	room* e2 = new courtyard("e2");
	room* f2 = new hallway("f2");
	room* g2 = new stairwell("g2");
	room* a3 = new bathroom("a3");
	room* b3 = new stairwell("b3");
	room* c3 = new library("c3");
	room* d3 = new foyer("d3");
	room* e3 = new bathroom("e3");
	room* f3 = new hallway("f3");
	room* g3 = new hallway("g3");
	room* a4 = new bathroom("a4");
	room* b4 = new bedroom("b4");
	room* c4 = new bedroom("c4");
	room* d4 = new foyer("d4");
	room* e4 = new bedroom("e4");
	room* f4 = new bedroom("f4");
	room* g4 = new zombie_room("g4");

	a1->set_room_vars(NULL, b1, NULL, NULL,"nothing");
	b1->set_room_vars(NULL, c1, b2, a1,"nothing");
	c1->set_room_vars(NULL, d1, NULL, b1,"nothing");
	d1->set_room_vars(NULL, e1, d2, c1,"crackers");
	e1->set_room_vars(NULL, f1, e2, d1,"nothing");
	f1->set_room_vars(NULL, g1, f2, e1,"nothing");
	g1->set_room_vars(NULL, NULL, NULL, f1,"nothing");
	a2->set_room_vars(NULL, b2, a3, NULL,"nothing");
	b2->set_room_vars(b1, NULL, NULL, a2,"nothing");
	c2->set_room_vars(NULL, d2, c3, NULL,"nothing");
	d2->set_room_vars(d1, NULL, d3, c2,"nothing");
	e2->set_room_vars(e1, f2, NULL, NULL,"nothing");
	f2->set_room_vars(f1, NULL, f3, e2,"nothing");
	g2->set_room_vars(NULL, NULL, g3, NULL,"lemons");
	a3->set_room_vars(a2, NULL, NULL, NULL,"cheese");
	b3->set_room_vars(NULL, c3, NULL, NULL,"nothing");
	c3->set_room_vars(c2, NULL, c4, b3,"chocolate");
	d3->set_room_vars(d2, NULL, d4, NULL,"noodles");
	e3->set_room_vars(NULL, NULL, e4, NULL,"tuna fish");
	f3->set_room_vars(f2, g3, f4, NULL,"nothing");
	g3->set_room_vars(g2, NULL, g4, f3,"nothing");
	a4->set_room_vars(NULL, b4, NULL, NULL,"soup");
	b4->set_room_vars(NULL, c4, NULL, a4,"nothing");
	c4->set_room_vars(c3, NULL, NULL, b4,"nothing");
	d4->set_room_vars(d3, NULL, NULL, NULL,"nothing");
	e4->set_room_vars(e3, f4, NULL, NULL,"wine");
	f4->set_room_vars(f3, NULL, NULL, e4,"nothing");
	g4->set_room_vars(g3, NULL, NULL, NULL,"nothing");

	
	//set starting room to d4, the first foyer
	current_room = d4;

	//load hallways into hallways vector
	hallways.push_back(b1);
	hallways.push_back(c1);
	hallways.push_back(d1);
	hallways.push_back(e1);
	hallways.push_back(f2);
	hallways.push_back(f3);
	hallways.push_back(g3);
	
}

