#ifndef FILES_H
#define FILES_H

#include<iostream>
#include<vector>
#include<string>
#include<dirent.h>
using namespace std;
/*  This is a factory class
	Will take input string and return the query object
*/

class listFiles{
public:
	vector<string> _fileLocs; // <TODO: Make this private and provide a function that returns iterator>
	listFiles(string scope);
};
#endif 
