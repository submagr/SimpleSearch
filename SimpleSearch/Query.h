#ifndef QUERY_H
#define QUERY_H

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


class Query{
	FileScope _scope;
	string _keyword;	
	int * _result;
	int _resultSize;
public:
	Query(FileScope scope, string keyword);
	map<int, list<SubQuery *>> root;
	void setParams(string scope, string keyword);
	FileScope getScope();
	string getKeyword();
	void displayParsedQuery();
	void resolveQuery();
	void displayResult(); // <XXX: This is breaking SRP>
	~Query();
};

class QueryParser{
public:
	static void parse(Query &q);
	static void CheckPhrase(Query &q);
	static vector<string> split(string str);
	static void CreateTree(Query &q);
};

#endif 