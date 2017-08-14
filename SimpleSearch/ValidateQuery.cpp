 #include "ValidateQuery.h"
#include "common.h"

ValidateQuery::ValidateQuery(string query){
    CreateDictionary();
    bool in_trie = false;
    dictionaryTrie.search(query, in_trie);
    cout << query << in_trie << endl;
}
