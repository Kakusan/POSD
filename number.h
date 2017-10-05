#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

class Number : public Term {
public:
  Number(int i) : Term(std::to_string(i)) { _value = std::to_string(i); _termName = "number"; }
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
