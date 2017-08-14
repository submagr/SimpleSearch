 #include "ValidateQuery.h"

 void static ValidateQuery::CreateDictionary()
{
    std::vector< string > words;
    string line;
    ifstream myfile ("words.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            words.push_back(line);
        }
        myfile.close();
        trie.build_trie(words);
    }
    else cout << "Unable to open file";     
}

ValidateQuery::ValidateQuery(string query){
    CreateDictionary();
    bool in_trie = false;
    trie.search(query, in_trie);
    cout << query << in_trie << endl;
}
