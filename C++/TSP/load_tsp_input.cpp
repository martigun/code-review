/**************************************************************************
* File: load_tsp_input.cpp
*
* Header: load_tsp_input.h
* ************************************************************************/

#include "load_tsp_input.h"

//loads vectors and returns vCount from filename
long load_tsp_input(string filename, vector<long> &xarr, vector<long> &yarr){
	
	//init vCount
	int vCount = 0;
	
	//init stream
	ifstream ifs;
	ifs.open(filename);
	string input;
	
	//goes through each line in file
	while (getline(ifs, input)){
		
		//increment vCount
		vCount += 1;
		
		//create vector to hold results of split
		vector<string> fields;
		
		//split this line into the fields vector
		split(fields, input, is_any_of(" "), token_compress_on);
		
		//loop thru columns and load column 2 and 3 to x and y
		int columnCounter = 0;
		for(int i=0;i<fields.size();i++){
			
			//only load fields that have a value
			if(!fields[i].empty()){
				
				//increment the columnCounter
				columnCounter += 1;
				
				//load the 2nd column to x, 3rd column to y
				if(columnCounter == 2) xarr.push_back(stol(fields[i]));
				if(columnCounter == 3) yarr.push_back(stol(fields[i]));
			}
		}
	}
	
	//close stream and return vCount
	ifs.close();
	return vCount;
}

