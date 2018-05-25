/**************************************************************************
* File: load_tsp_input.h
*
* Desc: This function `load_tsp_input` takes a text file as input and
*		loads two vectors (one each for x and y coordinates) with the
*		of the file.
*
* Params
*	`filename`: This is the string of the file that will be opened and read.
*				It must be in the format `<idx> <x> <y>` where <idx> is the
*				index number of the vertex, <x> is the x coordinate of the
*				vertex and <y> is the y coordinate of the vertex.
*	`xarr`:		This is the vector of long integers that will hold the
*				x coordinates.
*	`yarr`:		This is the vector of long integers that will hold the
*				y coordinates.
*
* Output: This function will return the total number of vertices in the graph
*			as a long integer.
*	
* Refs:
* http://www.cplusplus.com/faq/sequences/strings/split/#boost-split
*
* ************************************************************************/

#ifndef LOAD_TSP_INPUT
#define LOAD_TSP_INPUT

#include <iostream> //cout
#include <string> //string
#include <fstream> //ifstream
#include <vector> //vector
#include <cstdlib> //stol

#include <boost/algorithm/string.hpp>

using boost::algorithm::split;
using boost::algorithm::is_any_of;
using boost::algorithm::token_compress_on;

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::getline;

//loads vectors and returns vector count from filename
long load_tsp_input(string filename, vector<long> &xarr, vector<long> &yarr);

#endif




