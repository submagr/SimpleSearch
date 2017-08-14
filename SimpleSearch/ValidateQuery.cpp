 #include "ValidateQuery.h"
#include "common.h"
#include <string>
#include<algorithm>


ValidateQuery::ValidateQuery(string query){
	std::transform(query.begin(),
		query.end(),
		query.begin(),
		::tolower);
    bool in_trie = false;
    dictionaryTrie.search(query, in_trie);
    cout << query << in_trie << endl;
}
