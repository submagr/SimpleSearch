#ifndef VALIDATEQUERY_H
#define VALIDATEQUERY_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class ValidateQuery{
    Trie trie;
    void static CreateDictionary();

public:
    ValidateQuery(string query);
 
};

#endif