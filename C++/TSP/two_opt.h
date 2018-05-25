/**************************************************************************
* File: two_opt.h
*
* Desc: 

*
* Params
*	``:		
*
*
* Output: 
*	
*
* ************************************************************************/

#ifndef TWO_OPT
#define TWO_OPT

#include <iostream> //cout
#include <string> //string
#include <vector> //vector
#include <math.h> //lround, pow

long get_path_distance(std::vector<long> &xarr, std::vector<long> &yarr, long idx1, long idx2);

long twoOptPairSwap(int idx1, int idx2, std::vector<long> &bestRoute, std::vector<long> &currRoute, std::vector<long> &xarr, std::vector<long> &yarr);

#endif
