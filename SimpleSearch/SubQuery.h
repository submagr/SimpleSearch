// <TODO: Split src from header>
#ifndef SUBQUERY_H
#define SUBQUERY_H

#include<string>
#include<list>
#include<map>
using namespace std;

class SubQuery{
protected:
	string _rawSubQuery;
	bool _isFirst; 
public:
	SubQuery(string rawSubQuery, bool isFirst);
	virtual void Free() = 0;

	/*	HandleQuery: 
		- To call the dispatcher on "processedSubQueryString" and a pool of fileIndexes. 
		- Handle the results from  dispatcher: Result will be fileIndex: #matches
		- Update the fileOccurances array
	*/
	virtual void handleQuery(int *fileOccurances, int fileOccurancesSize) = 0;
};

class ExactMatch : public SubQuery{
	string processedString; // The input to the algorithm
public:
	ExactMatch(string rawSubQuery, bool isFirst);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
};

class Stemming: public SubQuery{
public:
	Stemming(string rawSubQuery, bool isFirst);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
};

class Keyword : public SubQuery{
public:
	Keyword(string rawSubQuery, bool isFirst);
	void Free();
	void handleQuery(int *fileOccurances, int fileOccurancesSize);
};


#endif