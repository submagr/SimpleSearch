#include "Dispatcher.h"

map<int, int> Dispatcher::dispatch(list<int> filePool, FileScope scope, string keyWord){
	map<int, int> fileMatches;
	BMAlgorithm::Run(filePool, scope, keyWord, fileMatches);
	return fileMatches;
}