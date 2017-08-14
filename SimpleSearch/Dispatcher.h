#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <list>
#include <string>
#include <map>

#include "BMAlgorithm.h"
using namespace std;


// <TODO: templatize this class by algorithm>
class Dispatcher{
public:
	static map<int, int> dispatch(list<int> filePool, FileScope scope, string keyWord, bool matchLowerCase);
};
#endif