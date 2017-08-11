#ifndef SUBQUERYFACTORY_H
#define SUBQUERYFACTORY_H

#include "SubQuery.h"
#include "Files.h"
using namespace std;

// Factory for creating instances of IAnimal
class SubQueryFactory
{
//private:
//	SubQueryFactory();
//	SubQueryFactory(const SubQueryFactory &) { }
//	SubQueryFactory &operator=(const SubQueryFactory &) { return *this; }
public:
	// static SubQueryFactory * Get();
	static SubQuery * CreateSubQuery(string rawSubQuery, bool isFirst, FileScope scope);
};

// SubQueryFactory subQueryFactory;


// <XXX: Currently declaring a global variable for factory class instance; Elegant way possible>
// SubQueryFactory subQueryFactory;

// Initialization of the static factory instance
// SubQueryFactory SubQueryFactory::subQueryFactory;

#endif