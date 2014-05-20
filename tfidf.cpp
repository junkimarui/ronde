#include "SimpleHash.h"
#include "SimpleTrie.h"
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/time.h>

using namespace std;

SimpleTrie* trie = new SimpleTrie();
SimpleHash* hash = new SimpleHash(100000000);
map<string,int> m;

void incr_trie(string elm) {
  trie->increment(elm.c_str());
}

void incr_map(string elm) {
  m[elm]++;
}

void incr_hash(string elm) {
  hash->increment(elm.c_str());
}

/* http://shnya.jp/blog/?p=195 */
vector<string> split(const string &str, char delim){
  vector<string> res;
  size_t current = 0, found;
  while((found = str.find_first_of(delim, current)) != string::npos){
    res.push_back(string(str, current, found - current));
    current = found + 1;
  }
  res.push_back(string(str, current, str.size() - current));
  return res;
}

double increment(string filename, void (*p) (string)) {
  struct timeval s, e;
  gettimeofday(&s, NULL);
  ifstream ifs(filename.c_str());
  string line;
  while (ifs && getline(ifs,line)) {
    vector<string> k = split(line,' ');
    for (int i = 0; i < k.size(); i++) {
      (*p)(k[i]);
    }
  }
  gettimeofday(&e, NULL);
  return (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
}

int main(int argc, char** argv) {
  if (argc <= 2) {
    cout << "./count [trial number] [file]" << endl << "container type:t->trie,h->hash,m->map" << endl;
    return 0;
  }
  void (*p) (string);
  bool first_flag = false;
  if (argv[1][0] == '1')
    first_flag = true;
  vector<string> files;
  for (int i = 2; i < argc; i++)
    files.push_back(string(argv[i]));
  for (int i = 0; i < files.size(); i++) {
    cout << increment(files[i],incr_trie) << "\n" << flush;
    //cout << increment(files[i],incr_hash) << "\t" << flush;
    //if (first_flag) cerr << hash->count() << endl;
    //cout << increment(files[i],incr_map) << "\n";
  }
  /*
  cerr << "sort" << endl;
  trie->nodeSort();
  cerr << "output" << endl;
  cout << trie->toString() << endl;
  */
  return 0;
}
