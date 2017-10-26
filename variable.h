#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include "variable.h"
#include <algorithm>
#include <iostream>

using std::string;

class Variable : public Term {
public:
  Variable(string s) : Term(s) {}
  string value() {
    if (isUsed)
      return realThing->value();
    else
      return symbol();
  }
  void BecomeCouple(Variable* v) { variables.push_back(v); }
  bool IsUsed() { return isUsed; }
  void SetValue(Term* t) {
    if (!isUsed) {
      realThing = t;
      isUsed = true;
      for (Variable *v : variables) 
        v->SetValue(t);
    }
  }

  bool match(Term &term) {
    Variable* v = dynamic_cast<Variable*>(&term);
    //List* l = dynamic_cast<List*>(&term);
    if (v) {
      if (!isUsed) {
        if (v->IsUsed())
          SetValue(v);
        else if (_symbol != v->symbol()) {
          BecomeCouple(v);
          v->BecomeCouple(this);
        }
        return true;
      } else if (v->IsUsed()) {
        if (v->value() == value())
          return true;
        else
          return false;
      } else {
        v->SetValue(this);
        return true;
      }
    }
     //else if (l && l->isExist(this)) {return false;} 
    else if (!isUsed) {
      SetValue(&term);
      return true;
    } else if (term.value() == value())
      return true;
    else
      return false;
  }

private:
  bool isUsed = false;
  Term* realThing;
  std::vector<Variable*> variables;

};

#endif
