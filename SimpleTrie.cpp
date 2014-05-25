#include "SimpleTrie.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_LENGTH 1000

using namespace jm_trie;

Element::Element() {
  this->val = 0;
  this->term = false;
}

Element::Element(char ch) {
  this->ch = ch;
  this->val = 0;
  this->term = false;
}

Element::Element(char ch,number val) {
  this->ch = ch;
  this->val = val;
  this->term = false;
}

Element::~Element() {
  for (uint i = 0; i < children.size(); i++)
    delete children[i];
}

bool Element::hasChild(char ch) {
  for (uint i = 0; i < children.size(); i++) {
    if (children[i]->ch == ch)
      return true;
  }
  return false;
}

Element* Element::getChild(char ch) {
for (uint i = 0; i < children.size(); i++) {
    if (children[i]->ch == ch)
      return children[i];
  }
  return NULL;
}

Element* Element::binaryGetChild(char ch) {
  vector<Element*>::iterator it =
    lower_bound(children.begin(),children.end(),ch,
		[](const Element* elm, char c) {return elm->ch < c;});
  return *it;
}

Element* Element::appendChild(char ch) {
  Element* newChild = new Element(ch);
  children.push_back(newChild);
  return newChild;
}

SimpleTrieIterator::SimpleTrieIterator(Element* elm, const char* key) {
  elmseq = new Element*[MAX_LENGTH];
  charseq = new char[MAX_LENGTH];
  idxseq = new int[MAX_LENGTH];
  for (int i = 0; i < MAX_LENGTH; i++)
    idxseq[i] = 0;
  rootdepth = strlen(key);
  depth = rootdepth;
  strncpy(charseq,key,rootdepth);
  elmseq[rootdepth] = elm;
  first = true;
}

SimpleTrieIterator::~SimpleTrieIterator() {
  delete[] elmseq;
  delete[] charseq;
  delete[] idxseq;
}

Element* SimpleTrieIterator::nextNode() {
  if (first) {
    first = false;
    return elmseq[rootdepth];
  }
  Element* nextElm = NULL;
  while (1) {
    //deeper element
    if (idxseq[depth] < elmseq[depth]->children.size()) {
      elmseq[depth+1] = elmseq[depth]->children[idxseq[depth]];
      charseq[depth] = elmseq[depth+1]->ch;
      depth++;
      nextElm = elmseq[depth];
      break;
    }
    else if (depth > rootdepth) { // go to parent
      idxseq[depth-1]++;
      idxseq[depth] = 0;
      depth--;
    }
    else {
      return NULL;
    }
  }
  return nextElm;
}

const char* SimpleTrieIterator::next() {
  const Element* node = NULL;
  do {
    node = nextNode();
  } while (node != NULL && !node->term);
  if (node == NULL) return NULL;
  char* buf = new char[depth+1];
  strncpy(buf,charseq,depth);
  buf[depth] = 0;
  return buf;
}

const char* SimpleTrieIterator::str() {
  char* buf = new char[depth+1];
  strncpy(buf,charseq,depth);
  buf[depth] = 0;
  return buf; 
}

SimpleTrie::SimpleTrie() {
  this->root = new Element(0);
  this->cnt = 0;
}

SimpleTrie::~SimpleTrie() {
  delete this->root;
}

const char* SimpleTrie::toString() const{
  SimpleTrieIterator* it = prefix_search("");
  if (it == NULL) return "";
  stringstream ss;
  while (const char* key = it->next()) {
    ss << key << "\t" << get(key) << endl;
    delete[] key;
  }
  delete it;
  const string str = ss.str();
  int len = str.length();
  char* ret = new char[len+1];
  strncpy(ret,str.c_str(),len);
  ret[len] = 0;
  return ret;
}

Element* SimpleTrie::findAndCreate(const char* key){
  int len = strlen(key);
  Element* elm = root;
  Element* child;
  for (int i = 0; i < len; i++) {
    if ((child = elm->getChild(key[i])) != NULL) {
      elm = child;
    }
    else {
      elm = elm->appendChild(key[i]);
      cnt++;
    }
  }
  return elm;
}

Element* SimpleTrie::find(const char* key) const{
  int len = strlen(key);
  Element* elm = root;
  Element* child;
  if (len == 0) return root;
  for (int i = 0; i < len; i++) {
    if ((child = elm->getChild(key[i])) != NULL) {
      elm = child;
    }
    else {
      return NULL;
    }
  }
  return elm;
}

void SimpleTrie::set(const char* key, number val) {
  Element* elm = this->findAndCreate(key);
  elm->val = val;
  elm->term = true;
}

void SimpleTrie::increment(const char* key) {
  Element* elm = this->findAndCreate(key);
  elm->val++;
  elm->term = true;
}

void SimpleTrie::incrementAll(vector<string> keys) {
  for (int i = 0; i < keys.size(); i++)
    increment(keys[i].c_str());
}

number SimpleTrie::get(const char* key) const{
  Element* elm = find(key);
  if (elm == NULL || !elm->term)
    return 0;
  return elm->val;
}

number SimpleTrie::fget(const char* key) const{
  int len = strlen(key);
  Element* elm = root;
  Element* child;
  for (int i = 0; i < len; i++) {
    if ((child = elm->binaryGetChild(key[i])) != NULL) {
      elm = child;
    }
    else {
      return 0;
    }
  }
  if (!elm->term)
    return 0;
  return elm->val;
}

SimpleTrieIterator* SimpleTrie::prefix_search(const char* key) const {
  Element* elm;
  if (strlen(key) == 0) return new SimpleTrieIterator(root,"");
  elm = this->find(key);
  if (elm == NULL) return NULL;
  return new SimpleTrieIterator(elm,key);
}

vector<string> SimpleTrie::common_prefix_search(const char* key) const {
  vector<string> candidates;
  string str(key);
  Element* elm = root;
  Element* child;
  for (int i = 0; i < strlen(key); i++) {
    if ((child = elm->getChild(key[i])) != NULL) {
      elm = child;
      if (elm->term)
	candidates.push_back(str.substr(0,i+1));
    }
    else {
      break;
    }
  }
  return candidates;
}

int SimpleTrie::count() const{
  return cnt;
}

void SimpleTrie::nodeSort() {
  SimpleTrieIterator* it = new SimpleTrieIterator(root,"");
  Element* node;
  while (node = it->nextNode()) {
    sort(node->children.begin(),node->children.end(),
	 [](const Element* x, const Element* y) {return (unsigned char)x->ch < (unsigned char)y->ch;});
  }
}

vector<paar> SimpleTrie::keyValSorted() const {
  vector<paar> keyval;
  SimpleTrieIterator* it = new SimpleTrieIterator(root,"");
  Element* node;
  while (node = it->nextNode()) {
    if (!node->term) continue;
    const char* tmp = it->str();
    keyval.push_back(paar(string(tmp), node->val));
    delete[] tmp;
  }
  sort(keyval.begin(),keyval.end(),
       [](const paar& x, const paar& y){return x.second > y.second;});
  return keyval;
}
