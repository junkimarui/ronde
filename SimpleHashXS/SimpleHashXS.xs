/*
SimpleHashXS

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"
#include "SimpleHashBind.h"
extern int simpleHashInit (int size);
extern int simpleHashRelease();
extern int simpleHashSet (char* key, int val);
extern int simpleHashGet (char* key);
extern int simpleHashIncrement(char* key);

MODULE = SimpleHashXS		PACKAGE = SimpleHashXS		

int
init(size)
  int size
CODE:
  RETVAL = simpleHashInit(size);
OUTPUT:
RETVAL

int
release()
CODE:
  RETVAL = simpleHashRelease();
OUTPUT:
RETVAL

int
set(key, val)
     char* key
     int val
CODE:
  RETVAL = simpleHashSet(key,val);
OUTPUT:
RETVAL

int
get(key)
     char * key
CODE:
  RETVAL = simpleHashGet(key);
OUTPUT:
RETVAL

int
increment(key)
     char* key
CODE:
  RETVAL = simpleHashIncrement(key);
OUTPUT:
RETVAL
