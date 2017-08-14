#include "SubQuery.h"
#include "ValidateQuery.h"

SubQuery::SubQuery(string rawSubQuery, bool isFirst, FileScope scope) : _rawSubQuery(rawSubQuery), _isFirst(isFirst), _scope(scope)
{

}

void SubQuery::displaySubQuery(){
	cout << "\t" << _rawSubQuery << "\t" << _isFirst << endl;
}

ExactMatch::ExactMatch(string rawSubQuery, bool isFirst, FileScope scope) : SubQuery(rawSubQuery, isFirst, scope)
{
	cout << "Query of type ExactMatch: " << rawSubQuery << endl;
	if (rawSubQuery.size()>=2){
		_processedString = rawSubQuery.substr(1, rawSubQuery.size() - 2); 
	}
	else{
		// <XXX: Throw exception from here>
		_processedString = "";
	}
}

void ExactMatch::Free(){
	delete this;
}

void ExactMatch::handleQuery(int *fileOccurances, int fileOccurancesSize)
{
	list<int> filePool;
	for (int i = 0; i < fileOccurancesSize; i++){
		if (_isFirst || fileOccurances[i]!=0){
			filePool.push_back(i);
		}
	}
	// Dispatch using dispatcher: 
	map<int, int> rawCounts = Dispatcher::dispatch(filePool, this->_scope, this->_processedString, false); 

	list<int>::const_iterator iterator;
	for (iterator = filePool.begin(); iterator != filePool.end(); ++iterator) {
		// <XXX: Implemented logic of "AND" here directly, It should be done via different class
		//	maybe, call a function(templatized by operator) which updates the fileOccurances list>
		if (fileOccurances[*iterator]!=0){
			fileOccurances[*iterator] *= rawCounts[*iterator];
		}
		else{
			fileOccurances[*iterator] = rawCounts[*iterator];
		}
	}
}

void ExactMatch::Validate()
{
	ValidateQuery::ValidateQuery(_rawSubQuery);
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
	this->Validate();
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
	map<int, int> rawCounts = Dispatcher::dispatch(filePool, this->_scope, this->_rawSubQuery, true); 

	list<int>::const_iterator iterator;
	for (iterator = filePool.begin(); iterator != filePool.end(); ++iterator) {
		// <XXX: Implemented logic of "AND" here directly, It should be done via different class
		//	maybe, call a function(templatized by operator) which updates the fileOccurances list>
		if (fileOccurances[*iterator]!=0){
			fileOccurances[*iterator] *= rawCounts[*iterator];
		}
		else{
			fileOccurances[*iterator] = rawCounts[*iterator];
		}
	}
}

void Keyword::Validate()
{
	ValidateQuery::ValidateQuery(_rawSubQuery);
}
