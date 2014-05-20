/*
SimpleTrieXS

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#define PERL_NO_GET_CONTEX
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"
#include <stdlib.h>
#include "SimpleTrieBind.h"
extern int simpleTrieInit ();
extern int simpleTrieRelease();
extern int simpleTrieSet (char* key, int val);
extern int simpleTrieGet (char* key);
extern int simpleTrieIncrement(char* key);

MODULE = SimpleTrieXS		PACKAGE = SimpleTrieXS		

int
init()
CODE:
  RETVAL = simpleTrieInit();
OUTPUT:
RETVAL

int
release()
CODE:
RETVAL = simpleTrieRelease();
OUTPUT:
RETVAL

int
set(key, val)
  char* key
  int val
CODE:
  RETVAL = simpleTrieSet(key,val);
OUTPUT:
RETVAL

int
get(key)
  char * key
CODE:
  RETVAL = simpleTrieGet(key);
OUTPUT:
RETVAL

int
increment(key)
  char* key
CODE:
  RETVAL = simpleTrieIncrement(key);
OUTPUT:
RETVAL
