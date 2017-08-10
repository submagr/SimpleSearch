#ifndef QUERY_H
#define QUERY_H

#include "Result.h"
#include "Files.h"
#include "SubQuery.h"
#include "SubQueryFactory.h"

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <sstream>
using namespace std;

# define NO_OF_CHARS 256

class Query{
	string _scope;
	string _keyword;
public:
	map<int, list<SubQuery *>> root;
	void setParams(string scope, string keyword);
	string getScope();
	string getKeyword();
	void displayParsedQuery();
};

class QueryParser{
public:
	Query parse(string scope, string query);
	void CheckPhrase(Query &q);
	vector<string> split(string str);
	void CreateTree(Query &q);
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