#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <iostream>
#include <string>
#include "term.h"
#include "variable.h"
#include "iterator.h"

using std::string;

class Number : public Term {
public:
  Number(double db) : Term(db) {}

  Iterator* createIterator() {
    return new NullIterator(this);
  }

  bool match(Term &term) {
    Variable *v = dynamic_cast<Variable *>(&term);
    if (v)
      return v->match(*this);
    else
      return term.value() == value();
  }
};

#endif
