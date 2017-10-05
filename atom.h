#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

class Atom : public Term {
public:
  Atom(string s) : Term(s) { _value = s; _termName = "atom"; }
  bool match(Term &term) {
    if (term.termName() == "variable" && !static_cast<Variable*>(&term)->IsUsed()) {
      static_cast<Variable *>(&term)->SetValue(_value);
      return true;
    }
    else if (term.value() == _value)
      return true;
    else
      return false;
  }
};

#endif
