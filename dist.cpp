#include "SimpleHash.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace jm_hash;

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

void distribution(string filename) {
  SimpleHash* hash = new SimpleHash(100000000);
  ifstream ifs(filename.c_str());
  string line;
  while (ifs && getline(ifs,line)) {
    vector<string> k = split(line,'\t');
    if (k.size() > 1)
      hash->increment(k[1].c_str());
  }
  vector<string> keys = hash->keySet();
  sort(keys.begin(),keys.end(),
       [](const string& x, const string& y){return atoi(x.c_str()) < atoi(y.c_str());});
  for (uint i = 0; i < keys.size(); i++) {
    cout << keys[i] << "\t" << hash->get(keys[i].c_str()) << endl;
  }
  delete hash;
}

int main(int argc, char** argv) {
  if (argc <= 1) {
    cout << "./dist [file]" << endl
	 << "file format:" << endl
	 << "\"element1\"\t\"count1\"" << endl
	 << "\"element2\"\t\"count2\"" << endl;
    return 0;
  }
  vector<string> files;
  for (int i = 1; i < argc; i++)
    files.push_back(string(argv[i]));
  for (int i = 0; i < files.size(); i++) {
    distribution(files[i]);
  }
  return 0;
}
