#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

template<class T> 
class Iterator;

class Atom : public Term {
public:
  Atom(string s) : Term(s) {}

  Iterator<Term>* createNormalIterator();
  Iterator<Term>* createBFSIterator();
  Iterator<Term>* createDFSIterator();

  bool match(Term &term) {
    Variable *v = dynamic_cast<Variable *>(&term);
    if (v)
      return v->match(*this);
    else
      return term.value() == value();
  }
};

#endif
