#ifndef FILES_H
#define FILES_H

#include<iostream>
#include<vector>
#include<string>
#include<dirent.h>
#include<map>
using namespace std;

class FileScope{
public:		
	string _scopeLoc;
	vector<string> _fileLocs; // <TODO: Make this private and provide a function that returns iterator>
	map<int, string> _fileLocsHash;
	FileScope(string scopeLoc);
	string getFileLocFromIndex(int index);
	/* listFiles::
		 Populate the _fileLocs recursively from scopeLoc
	*/
	void listFiles();
	void createFileLocsHash();
	int getNumberOfFiles();
};

#endif 
