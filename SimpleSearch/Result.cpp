#include "Result.h"

Result::Result(string fileLoc):_fileLocation(fileLoc){
}

void Result::display(){
	cout << "Total Matches for " << _fileLocation << " : " << _matchLocations.size() << endl;
	for (int i = 0; i < _matchLocations.size(); i++){
		cout << "\t" << i+1 << ". Shift = " << _matchLocations[i] << endl;
	}
}

void Result::addMatch(int matchLocation){
	_matchLocations.push_back(matchLocation);
}

void Results::addResult(Result result){
	_results.push_back(result);
}

void Results::display(){
	for (int i = 0; i < _results.size(); i++){
		_results[i].display();
	}
}


