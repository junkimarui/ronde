/*
jm_trie::SimpleTrie

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

%module SimpleTrie
%include <std_string.i>
%include <std_vector.i>
%include "paar.i"
namespace std {
  %template(vectorstr) vector<string>;
};
%template(vectorpaar) std::vector<ronde::paar>;
%{
#include "SimpleTrie.h"
%}
%include "SimpleTrie.h"
