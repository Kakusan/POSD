#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <iostream>
#include <string>
#include "term.h"
#include "variable.h"

using std::string;

class Number : public Term {
public:
  Number(double i) : Term("") {
    std::stringstream ss;
    ss << i;
    _value = ss.str();
    _symbol = ss.str();
  }
  string symbol() const { return _symbol; }
  string value() { return _value; }
  bool match(Term &term) {
    Variable* v = dynamic_cast<Variable*>(&term);
    if (v && !v->IsUsed()) {
      v->SetValue(this);
      return true;
    }
    else if (term.value() == value())
      return true;
    else
      return false;
  }
};

#endif
