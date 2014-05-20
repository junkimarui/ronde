/*
SimpleTrieXS

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "../SimpleTrie.h"

using namespace std;
using namespace jm_trie;
SimpleTrie* trie;

extern "C" {
  int simpleTrieInit ();
  int simpleTrieRelease();
  int simpleTrieSet (char* key, int val);
  int simpleTrieGet (char* key);
  int simpleTrieIncrement(char* key);
}

int simpleTrieInit() {
  trie = new SimpleTrie();
  if (!trie) return 0;
  return 1;
}

int simpleTrieRelease () {
  delete trie;
  return 1;
}

int simpleTrieSet (char* key, int val) {
  trie->set(key,val);
  return 1;
}

int simpleTrieGet (char* key) {
  return trie->get(key);
}

int simpleTrieIncrement (char* key) {
  trie->increment(key);
  return 1;
}

