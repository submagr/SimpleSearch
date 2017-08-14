 #include "Dictionary.h"
 #include "common.h"

Trie dictionaryTrie;
 Dictionary::Dictionary()
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
        dictionaryTrie.build_trie(words);
    }
    else cout << "Unable to open file";     
}

