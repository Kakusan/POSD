#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include "variable.h"
#include <algorithm>
#include <iostream>
// #include "iterator.h"

using std::string;

class Variable : public Term {
public:
  Variable(string s) : Term(s) {}
  string value() const {
    if (isUsed)
      return realThing->value();
    else
      return symbol();
  }

  // Iterator* createIterator() {
  //   return new NullIterator(this);
  // }

  void BecomeCouple(Variable* v) { variables.push_back(v); }
  bool IsUsed() { return isUsed; }
  Term* RealThing() { return realThing; }
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
      if (isUsed && v->IsUsed()) {
        return realThing->match(*(v->RealThing()));
      } else if (!isUsed && v->IsUsed()) {
        SetValue(v->RealThing());
        return true;
      } else if (isUsed && !v->IsUsed()) {
        v->SetValue(this->RealThing());
        return true;
      } else if (!isUsed && !v->IsUsed()) {
        BecomeCouple(v);
        v->BecomeCouple(this);
        return true;
      } 
    } 
     //else if (l && l->isExist(this)) {return false;} 
    else if (!isUsed) {
      SetValue(&term);
      return true;
    } else
      return realThing->match(term);
  }

private:
  bool isUsed = false;
  Term* realThing;
  std::vector<Variable*> variables;

};

#endif
