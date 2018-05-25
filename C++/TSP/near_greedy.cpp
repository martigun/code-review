/**************************************************************************
* File: near_greedy.cpp
*
* Header: near_greedy.h
* ************************************************************************/

#include "near_greedy.h"

#define DEBUG2SWAP 0

long get_distance(vector<long> &xarr, vector<long> &yarr, long idx1, long idx2){
	
	//square the differences
	double temp_double = pow((xarr[idx1] - xarr[idx2]), 2); //x coordinate
	temp_double += pow((yarr[idx1] - yarr[idx2]), 2); //y coordinate
	
	//take square root
	temp_double = pow(temp_double, 0.5);
	
	//round and cast as long
	return lround(temp_double);
	
}

long Swap2(long idx1, long idx2, vector<long> &xarr, vector<long> &yarr, vector<long> &bestRoute){
	
	long vCount = bestRoute.size();
	long lastIdx = vCount - 1;
	
	//declare variables for keeping track of vertices
	long alpha, bravo, charlie;
	long india, juliet, kilo;
	
	
	//get vertex index numbers for swapping
	bravo = bestRoute[idx1];
	juliet = bestRoute[idx2];
	if(idx1 == 0) alpha = bestRoute[lastIdx]; else alpha = bestRoute[idx1-1];
	if(idx1 == lastIdx) charlie = bestRoute[0]; else charlie = bestRoute[idx1+1];
	if(idx2 == 0) india = bestRoute[lastIdx]; else india = bestRoute[idx2-1];
	if(idx2 == lastIdx) kilo = bestRoute[0]; else kilo = bestRoute[idx2+1];
	
	if(DEBUG2SWAP) cout << "alpha idx: " << alpha << " | bravo idx: " << bravo << " | charlie idx: " << charlie << endl;
	if(DEBUG2SWAP) cout << "india idx: " << india << " | juliet idx: " << juliet << " | kilo idx: " << kilo << endl;
	
	//get vars for orig and swap distances
	long origDist, swapDist;
	
	//if juliet is alpha
	if(juliet == alpha){
		
		//orig is india->juliet->bravo->charlie
		origDist = get_distance(xarr, yarr, india, juliet);
		origDist += get_distance(xarr, yarr, juliet, bravo);
		origDist +=  get_distance(xarr, yarr, bravo, charlie);
		
		//swap is india->bravo->juliet->charlie
		swapDist = get_distance(xarr, yarr, india, bravo);
		swapDist += get_distance(xarr, yarr, bravo, juliet);
		swapDist +=  get_distance(xarr, yarr, juliet, charlie);
	
	//if juliet is charlie
	} else if(juliet == charlie){
		
		//orig is alpha->bravo->juliet->kilo
		origDist = get_distance(xarr, yarr, alpha, bravo);
		origDist +=  get_distance(xarr, yarr, bravo, juliet);
		origDist +=  get_distance(xarr, yarr, juliet, kilo);
		
		//swap is alpha->juliet->bravo->kilo
		swapDist = get_distance(xarr, yarr, alpha, juliet);
		swapDist += get_distance(xarr, yarr, juliet, bravo);
		swapDist +=  get_distance(xarr, yarr, bravo, kilo);
		
	//"normal case"
	} else {
		
		//get original distance
		origDist = get_distance(xarr, yarr, alpha, bravo); //alpha to bravo
		origDist +=  get_distance(xarr, yarr, bravo, charlie); //bravo to charlie
		origDist +=  get_distance(xarr, yarr, india, juliet); //india to juliet
		origDist +=  get_distance(xarr, yarr, juliet, kilo); //juliet to kilo
		
		//get swap distance (swap bravo with juliet)
		swapDist =  get_distance(xarr, yarr, alpha, juliet); //alpha to juliet
		swapDist +=  get_distance(xarr, yarr, juliet, charlie); //juliet to charlie
		swapDist +=  get_distance(xarr, yarr, india, bravo); //india to bravo
		swapDist +=  get_distance(xarr, yarr, bravo, kilo); //bravo to kilo
	}

	
	long distChange = swapDist - origDist;	
	
	if(DEBUG2SWAP) cout << "origDist: " << origDist << endl;
	if(DEBUG2SWAP) cout << "swapDist: " << swapDist << endl;
	if(DEBUG2SWAP) cout << "distChange: " << distChange << endl;
	
	if(DEBUG2SWAP) cout << "-----" << endl;
	if(DEBUG2SWAP) for(int i=0; i<vCount; i++) cout << bestRoute[i] << endl;
	
	//if the swap improved it
	if(distChange < 0){
		
		bestRoute[idx1] = juliet; //change idx1 to juliet
		bestRoute[idx2] = bravo; //change idx2 to bravo
		
		if(DEBUG2SWAP) cout << "--- Improved --- " << bravo << " & " << juliet << endl;
		if(DEBUG2SWAP) for(int i=0; i<vCount; i++) cout << bestRoute[i] << endl;
		if(DEBUG2SWAP) cout << "------- By:" << distChange << endl;
		if(DEBUG2SWAP) cout << "------- By:" << distChange << endl;
		
		//return the improvement to main
		return distChange;
	} else {
		
		//return zero if no improvement
		return 0;		
	
	}
}

long near_greedy(vector<long> &xarr, vector<long> &yarr, long vCount, vector<long> &route, long start, vector<long> &idxarr){
	
	//vector for toVisit for each vertex and distance
	vector<long> toVisit = idxarr;
	long visitedDistance = 0;
	
	//set currV to the starting vertex and add to route
	long currV = start;
	route.push_back(start);
	
	//set position toVisit to starting vertex and remove from toVisit
	long nextToVisit = start;
	toVisit.erase(toVisit.begin() + nextToVisit);

	//loop until toVisit is empty
	while(!toVisit.empty()){
		
		//var for bestDistance
		long bestDistance = 0;
		
		//cycle thru every vertex in toVisit
		for(int i=0; i<toVisit.size(); i++){
			
			//get distance to this target vertex
			int thisDistance = get_distance(xarr, yarr, currV, toVisit[i]);
			
			//if this is the best
			if(thisDistance < bestDistance || bestDistance == 0){
				
				//update bestDistance and nextToVisit
				bestDistance = thisDistance;
				nextToVisit = i;
			}
		}
		
		//set currV to nextToVisit and update visitedDistance
		currV = toVisit[nextToVisit];
		visitedDistance += bestDistance;
		
		//add vertex to route and remove it from toVisit
		route.push_back(currV);
		toVisit.erase(toVisit.begin() + nextToVisit);
	}
	
	//add the distance for the last vertex back to the starting point
	visitedDistance += get_distance(xarr, yarr, currV, start);
	
	//return the total distance of visited vertices
	return visitedDistance;
}

