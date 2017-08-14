#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node {
  char ch;
  map<char, Node*> children;
};

class Trie {
  public:
    Trie() { head.ch = -1; };
    ~Trie();

    //void build_trie(string words[], int length);
    void build_trie(std::vector< string > words);
    void insert(string word);
    void search(string word, bool &result);

    void print_tree(map<char, Node*> tree);
    void print();

  protected:
    Node head;
    // Keep all newly created node in an array, for the ease of
    // memory release.
    vector<Node*> children;
};

#endif
