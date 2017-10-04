#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s) : Term(s) {}
  bool match(Term &term) {
    if (!isUsed) {
      _value = term.value();
      isUsed = true;
      return true;
    } else
      return false;
  }

private:
  bool isUsed = false;
};

#endif
