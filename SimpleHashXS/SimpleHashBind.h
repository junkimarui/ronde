/*
SimpleHashXS

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "../SimpleHash.h"

using namespace std;
using namespace jm_hash;
SimpleHash* hash;

extern "C" {
  int simpleHashInit (int size);
  int simpleHashRelease();
  int simpleHashSet (char* key, int val);
  int simpleHashGet (char* key);
  int simpleHashIncrement(char* key);
}

int simpleHashInit(int size) {
  hash = new SimpleHash(size);
  if (!hash) return 0;
  return 1;
}

int simpleHashRelease () {
  delete hash;
  return 1;
}

int simpleHashSet (char* key, int val) {
  hash->set(key,val);
  return 1;
}

int simpleHashGet (char* key) {
  return hash->get(key);
}

int simpleHashIncrement (char* key) {
  hash->increment(key);
  return 1;
}

