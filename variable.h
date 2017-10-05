#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

class Variable : public Term {
public:
  Variable(string s) : Term(s) { _termName = "variable"; }
  bool IsUsed() { return isUsed; }
  void SetValue(string v) { _value = v; isUsed = true; }
  bool match(Term &term) {
    if (!isUsed) {
      if(!(term.termName() == "variable" && !static_cast<Variable*>(&term)->IsUsed())) {
        _value = term.value();
        isUsed = true;
      }
      return true;
    } 
    else if (term.value() == _value)
      return true;
    else 
      return false;
  }

private:
  bool isUsed = false;
};

#endif
