#ifndef RESULT_H
#define RESULT_H 

#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Result{
public:
	string _fileLocation;
	vector<int> _matchLocations;
	Result(string fileLoc);
	void display();
	void addMatch(int matchLocation);
};

class Results{
public:
	vector<Result> _results;
	void addResult(Result result);
	void display();
};

#endif 
