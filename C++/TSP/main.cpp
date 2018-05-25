/**************************************************************************
* File: main.cpp
*
* Desc: This is the main function that will be run by the makefile.
*		It takes list of vertices with x and y coordinates in a text file
*		and loads them into memory and also saves the vertex count as `vCount`.
*
*		It then runs the `near_greedy` function from a starting point:
*
*			Scenario A (if `vCount` is < 1000):
*			-Run `near_greedy` in a loop, trying every single vertex as a starting point
*				
*			Scenario B (if `vCount` is > 1000):
*			-Run `near_greedy` with start point at 0
*			(NEEDS OPTIMIZATION)
*
*		After running the algorithm, it prints to standard output:
*			-The total best route's distance
*			-The entire best route in order
*
* ************************************************************************/

#include <iostream> //cout
#include <string> //string
#include <vector> //vector
#include <ctime> //time()

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using std::time;

#include "load_tsp_input.h" //load_tsp_input
#include "near_greedy.h" //near_greedy

//main function
int main(int argc, char **argv){
	
	//get filename from command line
	string filename = argv[1];
	
	//init vectors for x and y coordinates and vertex index
	vector<long> xarr, yarr, idxarr;
	
	//load up vectors from filename and returns count of vertices
	int vCount = load_tsp_input(filename, xarr, yarr);
	for(int j=0; j<vCount; j++) idxarr.push_back(j); //fill vertex index
	
	//init vectors for current and best route
	vector<long> currRoute, bestRoute;
	long currDistance = 0, bestDistance = 0;
	
	//set clock
	clock_t totalC = clock(), cumuC;
	float seconds = 0;

	//start the loop
	long index = 0;
	bool keep_running = true;
	while(keep_running){
		
		cout << "Try starting point: " << index << endl;
		
		//get distance for this start point
		currDistance = near_greedy(xarr, yarr, vCount, currRoute, index, idxarr);
		
		cout << "bestDistance before OPT: " << bestDistance << endl;
		
		//optmize from here
		int runCount = 2;
		for(int r=0; r<runCount; r++){
			for(int m=0; m<vCount; m++){
				for(int n=0; n<vCount; n++) {

					//Swap2 will swap and return improvement
					currDistance += Swap2(m, n, xarr, yarr, currRoute);
				}
			}
			cout << "currDistance after OPT" << (r+1) << ": " << currDistance << endl;
		}
		
		//if this is the best, the save distance and route
		if(currDistance < bestDistance || bestDistance == 0){
			bestDistance = currDistance;
			bestRoute.swap(currRoute);
		}
		
		//clear the currRoute
		currRoute.clear();
		
		//increment index and get second
		index++;
		cumuC = clock() - totalC;
		seconds = float(cumuC) / CLOCKS_PER_SEC;
		
		//stop if index is done or time has run out
		if(seconds > 160 || index == vCount) keep_running = false;
	}
	
	//calc time
	totalC = clock() - totalC;
	seconds = float(totalC);
	seconds = seconds / CLOCKS_PER_SEC;
	
	//print elapsed seconds
	cout << "Elapsed seconds: " << seconds << endl;
	
	//init output stream
	ofstream ofs;
	ofs.open(filename + ".tour");

	//print bestDistance and bestRoute to output file
	ofs << bestDistance << endl;
	for(int i=0; i<vCount; i++) ofs << bestRoute[i] << endl;
	
	//close output stream and return
	ofs.close();
	return 0;
}
