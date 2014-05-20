/*
jm_hash::SimpleHash

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef SIMPLE_HASH_H
#define SIMPLE_HASH_H
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "paar.h"
#define HASH_SIZE 3000000
#define number int

using namespace std;
using ronde::paar;

namespace jm_hash {
  class SHElement {
  public:
    char* str;
    number val;
    SHElement() {                                                                                                  
      str = NULL;
      val = 0;
    }
    SHElement(const char* key, number val) {
      this->str = new char[strlen(key)+1];
      strcpy(this->str,key);
      this->val = val;
    }
    ~SHElement() {
      delete[] str;
    }
  };
  
  class SimpleHash {
  public:
    SimpleHash() {
      table = new SHElement*[HASH_SIZE];
      size = HASH_SIZE;
      cnt = 0;
      for (int i = 0; i < size; i++)
	table[i] = NULL;
    }
    SimpleHash(int given_size) {
      table = new SHElement*[given_size];
      size = given_size;
      cnt = 0;
      for (int i = 0; i < size; i++)
	table[i] = NULL;
    }
    ~SimpleHash() {
      for (int i = 0; i < size; i++)
	if (table[i]!=NULL) delete table[i];
      delete[] table;
    }
    int hashCode(const char* str) const{
      unsigned long long hash = 0;
      for (int i = 0; i < strlen(str); i++)
	hash = hash * 257 + str[i];
      hash = hash % size;
      return hash;
    }
    
    vector<string> keySet() const;
    vector<string> keySetSorted() const;
    vector<paar> keyValSorted() const;
    
    const char* toString() const{
      stringstream ss;
      vector<string> keys = keySetSorted();
      for (int i = 0; i < keys.size(); i++)
	ss << keys[i] << "\t" << get(keys[i].c_str()) << endl;
      const string str = ss.str();
      int len = str.length();
      char* ret = new char[len+1];
      strncpy(ret,str.c_str(),len);
      ret[len] = 0;
      return ret;
    }

    void set(const char* key, number val) {
      int code = hashCode(key);
      while (table[code] != NULL && strcmp(table[code]->str,key) != 0 ) {
	code = (code + 1) % size;
      }
      if (table[code] == NULL) {
	SHElement* elm = new SHElement(key,val);
	table[code] = elm;
	cnt++;
      }
      else {
	table[code]->val = val;
      }
    }
    
    void increment(const char* key) {
      int code = hashCode(key);
      while (table[code] != NULL && strcmp(table[code]->str,key) != 0 ) {
	code = (code + 1) % size;
      }
      if (table[code] == NULL) {
	SHElement* elm = new SHElement(key,1);
	table[code] = elm;
	++cnt;
      }
      else {
	++table[code]->val;
      }
    }

    number get(const char* key) const{
      int code = hashCode(key);
      while (table[code] != NULL && strcmp(table[code]->str,key) != 0 ) {
	code = (code + 1) % size;
      }
      if (table[code] == NULL)
	return 0;
      return table[code]->val;
    }
    
    int count() const{
      return cnt;
    }
    
  private:
    SHElement** table;
    int size;
    int cnt;
  };
}

#endif

