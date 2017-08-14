// <TODO: Split src from header>
#ifndef SUBQUERY_H
#define SUBQUERY_H

#include<string>
#include<list>
#include<map>
#include<iostream>

#include "Files.h"
#include "Dispatcher.h"
using namespace std;

class SubQuery{
protected:
	string _rawSubQuery;
	bool _isFirst; 
	FileScope _scope;
public:
	SubQuery(string rawSubQuery, bool isFirst, FileScope scope);
	virtual void Free() = 0;

	/*	HandleQuery: 
		- To call the dispatcher on "processedSubQueryString" and a pool of fileIndexes. 
		- Handle the results from  dispatcher: Result will be fileIndex: #matches
		- Update the fileOccurances array
	*/
	virtual void handleQuery(int *fileOccurances, int fileOccurancesSize) = 0;
	void displaySubQuery();
};

class ExactMatch : public SubQuery{
	string processedString; // The input to the algorithm
public:
	ExactMatch(string rawSubQuery, bool isFirst, FileScope scope);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
	void ValidateQuery();
};

class Stemming: public SubQuery{
public:
	Stemming(string rawSubQuery, bool isFirst, FileScope scope);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
};

class Keyword : public SubQuery{
public:
	Keyword(string rawSubQuery, bool isFirst, FileScope scope);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
	void ValidateQuery();
};


#endif
