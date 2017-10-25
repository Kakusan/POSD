#ifndef LIST_H
#define LIST_H

#include <string>
#include "term.h"
#include "variable.h"
#include <vector>

using std::string;
using std::vector;

class List : public Term {
public:
  List (vector<Term *> const & elements): Term("[]") {
    if (elements.size() > 0) {
      for (int i = 0; i < elements.size(); i++) 
        _elements.push_back(elements[i]);
    }
  }

  string symbol() const {
    string output = "[";
    if (_elements.size() > 0) {
      for (int i = 0; i < _elements.size() - 1; i++) 
        output += _elements[i]->symbol() + ", ";
      output += _elements[_elements.size() - 1]->symbol();
    }
    output += "]";
    return output;
  }

  string value() {
    string output = "[";
    if (_elements.size() > 0) {
      for (int i = 0; i < _elements.size() - 1; i++) 
        output += _elements[i]->value() + ", ";
      output += _elements[_elements.size() - 1]->value();
    }
    output += "]";
    return output;
  }

  bool match(Term& term) {
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

  bool isExist(Term* term) {
    bool flag = false;
    for (int i = 0; i < _elements.size(); i++) {
      if(_elements[i]->symbol() == term->symbol())
        flag = true;
    }
    return flag;
  }

public:
  Term* head() { return _elements[0]; }
  List* tail() { return this; }

private:
  vector<Term *> _elements;

};

#endif