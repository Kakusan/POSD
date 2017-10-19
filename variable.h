#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include "variable.h"
#include <algorithm>

using std::string;

class Variable : public Term {
public:
  Variable(string s) : Term(s) { _value = s;}
  string symbol() const { return _symbol; }
  string value() { return _value; }
  void BecomeCouple(Variable* v) { variables.push_back(v); }
  bool IsUsed() { return isUsed; }
  void SetValue(string s) { 
    std::for_each(variables.begin(), variables.end(), SetValueToVariables(s));
    _value = s; 
    isUsed = true; 
  }

  bool match(Term &term) {
    Variable* v = dynamic_cast<Variable*>(&term);
    if (v) {
      if (!isUsed) {
        if (v->IsUsed())
          SetValue(v->value());
        else if (_symbol != v->symbol()) {
          BecomeCouple(v);
          //v->BecomeCouple(this);
        }
        return true;
      } else if (v->IsUsed()) {
        if (v->value() == _value)
          return true;
        else
          return false;
      } else {
        v->SetValue(_value);
        return true;
      }
    } else if (!isUsed) {
      SetValue(term.value());
      return true;
    } else if (term.value() == _value)
      return true;
    else
      return false;
  }

private:
  struct SetValueToVariables {
    string value;
    SetValueToVariables(string s) : value(s) {}
    void operator() (Variable* v) {
      v->SetValue(value);
    }
  };
  bool isUsed = false;
  std::vector<Variable*> variables;

};

#endif
