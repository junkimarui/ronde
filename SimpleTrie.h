/*
jm_trie::SimpleTrie

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef SIMPLE_TRIE_H
#define SIMPLE_TRIE_H
#include <vector>
#include <string>
#include "paar.h"
#define number int

using namespace std;
using ronde::paar;

namespace jm_trie {
  class Element {
  public:
    char ch;
    vector<Element*> children;
    number val;
    bool term;
    Element();
    Element(char);
    Element(char,number);
    ~Element();
    bool hasChild(char);
    Element* getChild(char);
    Element* binaryGetChild(char);
    Element* appendChild(char);
  };

  class SimpleTrieIterator {
  private:
    Element** elmseq;
    char* charseq;
    int* idxseq;
    int depth;
    int rootdepth;
    bool first;
  public:
    SimpleTrieIterator(Element* root,const char* key);
    ~SimpleTrieIterator();
    Element* nextNode();
    const char* next();
    const char* str();
  };

  class SimpleTrie {
  private:
    Element* root;
    int cnt;
  public:
    SimpleTrie();
    ~SimpleTrie();
    const char* toString() const;
    Element* find(const char* key) const;
    Element* findAndCreate(const char* key);
    void set(const char* key, number val);
    void increment(const char* key);
    void incrementAll(vector<string> keys);
    number get(const char* key) const;
    number fget(const char* key) const;
    SimpleTrieIterator* prefix_search(const char* key) const;
    int count() const;
    void nodeSort();
    vector<paar> keyValSorted() const;
  };
}

#endif

