#include "SubQueryFactory.h"

//SubQueryFactory * SubQueryFactory::Get()
//{
//	static SubQueryFactory instance;
//	return &instance;
//}

/*
	Depending upon rawSubQuery, return object(pointer) of subQueryType
*/
SubQuery * SubQueryFactory::CreateSubQuery(string rawSubQuery, bool isFirst, FileScope scope)
{
	if (rawSubQuery.front() == '"' && rawSubQuery.back() == '"')
	{
		return new ExactMatch(rawSubQuery, isFirst, scope);

		//word.erase(word.begin() + 0);
		//word.erase(word.end() - 1);
	}
	else if (rawSubQuery.find('*') != std::string::npos)
	{
		return new Stemming(rawSubQuery, isFirst, scope);
	}
	else
	{
		return new Keyword(rawSubQuery, isFirst, scope);
	}
	return NULL;
}