#include "SubQueryFactory.h"

SubQueryFactory * SubQueryFactory::Get()
{
	static SubQueryFactory instance;
	return &instance;
}

SubQuery * SubQueryFactory::CreateSubQuery(string rawSubQuery, bool isFirst)
{
	/*
		Depending upon rawSubQuery, return object(pointer) of subQueryType
		<TODO: Merge Bhavya's code here>
	*/
	return NULL;
}
