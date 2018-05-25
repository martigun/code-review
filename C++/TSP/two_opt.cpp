/**************************************************************************
* File: two_opt.cpp
*
* Header: 2opt.h
* ************************************************************************/

#include "two_opt.h"

long get_path_distance(std::vector<long> &xarr, std::vector<long> &yarr, long idx1, long idx2){
	
	//square the differences
	double temp_double = pow((xarr[idx1] - xarr[idx2]), 2); //x coordinate
	temp_double += pow((yarr[idx1] - yarr[idx2]), 2); //y coordinate
	
	//take square root
	temp_double = pow(temp_double, 0.5);
	
	//round and cast as long
	return lround(temp_double);
}


long twoOptPairSwap(int idx1, int idx2, std::vector<long> &bestRoute, std::vector<long> &currRoute, std::vector<long> &xarr, std::vector<long> &yarr) {
	long newDistance = 0;

	for(int i=0; i<=(idx1-1); i++) {
		currRoute.push_back(bestRoute.at(i));
		if((int)currRoute.size() > 1) {
            newDistance += get_path_distance(xarr,yarr,(currRoute[i]),(currRoute[i-1]));
		}
	}
	//Add route[idx1] to route[idx2] to newRoute in reverse order
	for(int i=idx2; i >= idx1; i--) {
		currRoute.push_back(bestRoute.at(i));
        if((int)currRoute.size() > 1) {
            newDistance += get_path_distance(xarr,yarr,(currRoute[i]),(currRoute[i-1]));
		}
	}
	//Add route[idx2+1] to end to newRoute in order
	for(int i = idx2+1; i < bestRoute.size(); i++) {
		currRoute.push_back(bestRoute.at(i));
        if((int)currRoute.size() > 1) {
            newDistance += get_path_distance(xarr,yarr,(currRoute[i]),(currRoute[i-1]));
		}
	}

	//connect starting and end nodes.
	newDistance += get_path_distance(xarr,yarr,(currRoute.front()),(currRoute.back()));

    return newDistance;
}
