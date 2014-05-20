#include "SimpleHash.h"
#include <algorithm>
using namespace std;
using namespace jm_hash;

vector<string> SimpleHash::keySet() const {
  vector<string> keys;
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL)
      keys.push_back(table[i]->str);
  }
  return keys;
}

vector<string> SimpleHash::keySetSorted() const {
  vector<string> keys = keySet();
  sort(keys.begin(),keys.end());
  return keys;
}

vector<paar> SimpleHash::keyValSorted() const {
  vector<paar> keyval;
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      paar p(string(table[i]->str),table[i]->val);
      keyval.push_back(p);
    }
  }
  sort(keyval.begin(),keyval.end(),
       [](const paar& x, const paar& y) {return x.second > y.second;});
  return keyval;
}

