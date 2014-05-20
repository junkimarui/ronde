#include "SimpleHash.h"
#include "SimpleTrie.h"
#include "paar.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/time.h>

using namespace std;
using namespace jm_trie;
using namespace jm_hash;
using ronde::paar;

SimpleTrie* trie = new SimpleTrie();
SimpleHash* hash = new SimpleHash(100000000);

void incr_trie(string elm) {
  trie->increment(elm.c_str());
}

void incr_hash(string elm) {
  hash->increment(elm.c_str());
}

vector<paar> vsort_trie() {
  return trie->keyValSorted();
}

vector<paar> vsort_hash() {
  return hash->keyValSorted();
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

double termfreq(string filename, void (*incr) (string), vector<paar>(*vsort)()) {
  string filename_out = filename + ".tf";
  struct timeval s, e;
  gettimeofday(&s, NULL);
  ifstream ifs(filename.c_str());
  ofstream ofs(filename_out.c_str());
  string line;
  while (ifs && getline(ifs,line)) {
    vector<string> k = split(line,' ');
    for (int i = 0; i < k.size(); i++) {
      (*incr)(k[i]);
    }
  }
  vector<paar> dump = (*vsort)();
  gettimeofday(&e, NULL);
  for (uint i = 0; i < dump.size(); i++) {
    ofs << dump[i].first << "\t" << dump[i].second << endl;
  }
  return (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
}

int main(int argc, char** argv) {
  if (argc <= 2) {
    cout << "./tf [container type] [file1] [file2]..." << endl 
	 <<  "container type:t->trie,h->hash" << endl;
    return 0;
  }
  void (*p) (string);
  vector<paar> (*vsort)();
  if (argv[1][0] == 't') {
    p = incr_trie;
    vsort = vsort_trie;
  }
  else {
    p = incr_hash;
    vsort = vsort_hash;
  }
  vector<string> files;
  for (int i = 2; i < argc; i++)
    files.push_back(string(argv[i]));
  for (int i = 0; i < files.size(); i++) {
    cerr << "process time:" << termfreq(files[i],p,vsort) << "\n";
  }
  return 0;
}
