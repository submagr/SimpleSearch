#ifndef QUERY_H
#define QUERY_H

#include<string>
#include<iostream>
#include "Result.h"
#include<fstream>
#include "Files.h"
using namespace std;

# define NO_OF_CHARS 256

class Query{
	string _scope;
	string _keyword;
public:
	void setParams(string scope, string keyword);
	string getScope();
	string getKeyword();
};

class QueryParser{
public:
	Query parse(int argc, char *argv[]);
};

class ProcessQuery{
public:		
	listFiles _files;
	Query _query;
	Results _results;

	ProcessQuery(listFiles files, Query query);
	int myMax(int a, int b);
	int getFileSize(string fileName);
	void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]);
	Result search(string fileName, string pat);
	void ProcessFile(int i);
};

#endif 