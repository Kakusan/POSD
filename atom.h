#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Atom : public Term {
public:
  Atom(string s) : Term(s) { _value = s; }
  bool match(Term &term) {
    if (term.symbol() == _symbol)
      return true;
    else
      return false;
  }
};

#endif
