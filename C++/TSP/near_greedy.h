/**************************************************************************
* File: near_greedy.h
*
* Desc: This function `near_greedy` finds the best route in a graph from
*		a given starting vertex `start` using the greedy "nearest neighbour" approach.
*		It takes a vector of x coordinates `xarr`,
*		a vector of y coordinates `yarr` and the count of vertices `vCount`.
*		It loads the vector `route` with the order of the best route and 
*		returns a long integer of the distance of that route.
*
*		The basic strategy from the starting point `start`:
*			1) Mark `start` as "visited"
*			2) Set current vertex `currV` = `start`
*			3) Find the closest vertex to `currV` (ignoring "visited" vertices)
*				-Call this closest vertex `nextV`
*			4) Mark `nextV` as "visited"
*			5) Set `currV` = `nextV`
*			6) Go to step 3
*
* Params
*	`xarr`:		This is the vector of long integers that contains the
*				x coordinates.
*	`yarr`:		This is the vector of long integers that contains the
*				y coordinates.
*	`vCount`:	This is a long integer of the count of vertices in the graph
*	`route`:	This is the vector that the best route will be loaded into
*	`start`:	This is the starting point for the 
*
* Output: This function will return the total distance of the found route
*			as a long integer.
*	
*
* ************************************************************************/

#ifndef NEAR_GREEDY
#define NEAR_GREEDY

#include <iostream> //cout
#include <string> //string
#include <math.h> //lround, pow
#include <fstream> //ifstream
#include <vector> //vector
#include <cstdlib> //stol

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::getline;

//get long distance between 2 vertices, given their index numbers
long get_distance(vector<long> &xarr, vector<long> &yarr, long idx1, long idx2);

//near_greedy function
long near_greedy(vector<long> &xarr, vector<long> &yarr, long vCount, vector<long> &route, long start, vector<long> &idxarr);


long Swap2(long idx1, long idx2, vector<long> &xarr, vector<long> &yarr, vector<long> &bestRoute);
#endif

