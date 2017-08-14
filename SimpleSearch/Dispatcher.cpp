#include "Dispatcher.h"

// <TODO: templatize dispatcher, query type class>
map<int, int> Dispatcher::dispatch(list<int> filePool, FileScope scope, string keyWord, bool matchLowerCase){
	map<int, int> fileMatches;
	BMAlgorithm::Run(filePool, scope, keyWord, fileMatches, matchLowerCase);
	return fileMatches;
}