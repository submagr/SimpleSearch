#include "SubQuery.h"

SubQuery::SubQuery(string rawSubQuery, bool isFirst, FileScope scope) : _rawSubQuery(rawSubQuery), _isFirst(isFirst), _scope(scope)
{

}

void SubQuery::displaySubQuery(){
	cout << "\t" << _rawSubQuery << "\t" << _isFirst << endl;
}

ExactMatch::ExactMatch(string rawSubQuery, bool isFirst, FileScope scope) : SubQuery(rawSubQuery, isFirst, scope)
{
	// Preprocess the rawSubQuery
}

void ExactMatch::Free(){
	delete this;
}

void ExactMatch::handleQuery(int *fileOccurances, int fileOccurancesSize)
{
	// Preprocess the rawSubQUery depending upon the subQueryType		
	// Define a function in base class that will dispatch the query to individual files 
	//	and populate the fileOccurance Array.
	list<int> filePool;
	for (int i = 0; i < fileOccurancesSize; i++){
		if (_isFirst || fileOccurances[i]!=0){
			filePool.push_back(i);
		}
	}
	// Dispatch using dispatcher: 
	map<int, int> rawCounts; 
	// <TODO: Replace above after implementation of Dispatcher> map<int, int> rawCounts = Dispatcher<BM>::Dispatch(filePool, processedString);
	list<int>::const_iterator iterator;
	for (iterator = filePool.begin(); iterator != filePool.end(); ++iterator) {
		// <XXX: Implemented logic of "AND" here directly, It should be done via different class
		//	maybe, call a function(templatized by operator) which updates the fileOccurances list>
		fileOccurances[*iterator] *= rawCounts[*iterator];
	}
}


Stemming::Stemming(string rawSubQuery, bool isFirst, FileScope scope) : SubQuery(rawSubQuery, isFirst, scope)
{
	// Preprocess the rawSubQuery
}

void Stemming::Free(){
	delete this;
}

void Stemming::handleQuery(int *fileOccurances, int fileOccurancesSize)
{
	list<int> filePool;
	for (int i = 0; i < fileOccurancesSize; i++){
		if (_isFirst || fileOccurances[i]!=0){
			filePool.push_back(i);
		}
	}
	// Dispatch using dispatcher: 
	map<int, int> rawCounts; 
	// <TODO: Replace above after implementation of Dispatcher> map<int, int> rawCounts = Dispatcher<BM>::Dispatch(filePool, processedString);
	list<int>::const_iterator iterator;
	for (iterator = filePool.begin(); iterator != filePool.end(); ++iterator) {
		// <XXX: Implemented logic of "AND" here directly, It should be done via different class
		//	maybe, call a function(templatized by operator) which updates the fileOccurances list>
		fileOccurances[*iterator] *= rawCounts[*iterator];
	}
}
Keyword::Keyword(string rawSubQuery, bool isFirst, FileScope scope) : SubQuery(rawSubQuery, isFirst, scope)
{
	// Preprocess the rawSubQuery
}

void Keyword::Free(){
	delete this;
}

void Keyword::handleQuery(int *fileOccurances, int fileOccurancesSize)
{
	list<int> filePool;
	for (int i = 0; i < fileOccurancesSize; i++){
		if (_isFirst || fileOccurances[i]!=0){
			filePool.push_back(i);
		}
	}
	// Dispatch using dispatcher: 
	map<int, int> rawCounts = Dispatcher::dispatch(filePool, this->_scope, this->_rawSubQuery); 

	list<int>::const_iterator iterator;
	for (iterator = filePool.begin(); iterator != filePool.end(); ++iterator) {
		// <XXX: Implemented logic of "AND" here directly, It should be done via different class
		//	maybe, call a function(templatized by operator) which updates the fileOccurances list>
		fileOccurances[*iterator] *= rawCounts[*iterator];
	}
}
