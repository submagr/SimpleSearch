#ifndef SUBQUERYFACTORY_H
#define SUBQUERYFACTORY_H

#include "SubQuery.h"
using namespace std;

// Factory for creating instances of IAnimal
class SubQueryFactory
{
private:
	SubQueryFactory();
	SubQueryFactory(const SubQueryFactory &) { }
	SubQueryFactory &operator=(const SubQueryFactory &) { return *this; }
public:
	static SubQueryFactory *Get();

	SubQuery * CreateSubQuery(string rawSubQuery, bool isFirst);
};

#endif