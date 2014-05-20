/*
ronde::paar

Copyright (c) 2014 Junki Marui

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef ronde_paar_H
#define ronde_paar_H
#define number int

using namespace std;

namespace ronde {
  class paar {
  public:
    string first;
    number second;
    paar() {};
    paar(string first, number second){this->first = first; this->second = second;}
    string getFirst() const {return first;}
    number getSecond() const {return second;}
  };
}

#endif

