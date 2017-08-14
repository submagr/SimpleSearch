#include "Trie.h"

Trie::~Trie() {
  for (int i=0; i<children.size(); ++i) {
    delete children[i];
  }
}

//void Trie::build_trie(string words[], int length) {
  //for (int i=0; i<length; ++i) {
    //insert(words[i]);
 // }
//}

void Trie::build_trie(std::vector< string > words) {
  for (int i=0; i<words.size(); i++) {
    insert(words[i]);
  }
}


void Trie::insert(string word) {
  map<char, Node*> *current_tree = &head.children;
  map<char, Node*>::iterator it;

  for (int i=0; i<word.length(); ++i) {
    char ch = word[i];

    if ((it = current_tree->find(ch)) != current_tree->end()) {
      current_tree = &it->second->children;
      continue;
    }

    if (it == current_tree->end()) {
      // Display inserting position in the tree, for debug use
      //
      // cout << "Inserting " << ch << endl;
      // cout << "on layer " << endl;
      // map<char, Node*>::iterator temp = current_tree->begin();
      // for (; temp != current_tree->end(); ++temp)
      //   cout << temp->first << endl;

      Node* new_node = new Node();
      new_node->ch = ch;
      (*current_tree)[ch] = new_node;

      // For continuous inserting a word.
      current_tree = &new_node->children;
      
      // For the ease of memory clean up.
      children.push_back(new_node);
    }
  }
}

void Trie::search(string word, bool &result) {
  map<char, Node*> current_tree = head.children;
  map<char, Node*>::iterator it;

  for (int i=0; i<word.length(); ++i) {
    if ((it = current_tree.find(word[i])) == current_tree.end()) {
      result = false;
      return;
    }
    current_tree = it->second->children;
  }

  result = true;
  return ;
}

void Trie::print_tree(map<char, Node*> tree) {
  if (tree.empty()) {
    return;
  }

  for (map<char, Node*>::iterator it=tree.begin(); it!=tree.end(); ++it) {
    cout << it->first << endl;
    print_tree(it->second->children);
  }
}

void Trie::print() {
  map<char, Node*> current_tree = head.children;
  print_tree(current_tree);
}