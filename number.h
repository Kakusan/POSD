#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include "term.h"
using std::string;

class Number : public Term {
public:
  Number(int i) : Term(i) {}
  bool match(Term &term) {
    if (term.symbol() == _symbol)
      return true;
    else
      return false;
  }
};

#endif
