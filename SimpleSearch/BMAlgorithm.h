#ifndef BMALGORITHM_H 
#define BMALGORITHM_H 

#include <list>
#include <map>
#include <fstream>
#include <string>
#include <streambuf>

#include "Files.h"
using namespace std;
# define NO_OF_CHARS 256

// <TODO: All methods should have been static>
class BMAlgorithm{
public:		
	static void Run(list<int> filePool, FileScope scope, string keyword, map<int, int>& counts);
	static int myMax(int a, int b);
	static int getFileSize(string fileName);
	static void badCharHeuristic(string str, int size, int badchar[256/*TODO:NO_OF_CHARS*/]);
	static int search(string fileName, string keyWord);
};

#endif
