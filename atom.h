#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

class Atom : public Term {
public:
  Atom(string s) : Term(s) { _value = s;}
  string symbol() const { return _symbol; }
  string value() { return _value; }
  bool match(Term &term) {
    Variable* v = dynamic_cast<Variable*>(&term);
    if (v && !v->IsUsed()) {
      v->SetValue(_value);
      return true;
    }
    else if (term.value() == _value)
      return true;
    else
      return false;
  }
};

#endif
