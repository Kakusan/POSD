#ifndef LIST_H
#define LIST_H

#include <string>
#include "term.h"
#include "variable.h"
#include <vector>

using std::string;
using std::vector;

template<class T> 
class Iterator;

class List : public Term {
public:
  List(): Term() {}
  List (vector<Term *> const & elements): Term("[]") {
    if (elements.size() > 0) {
      for (int i = 0; i < elements.size(); i++) 
        _elements.push_back(elements[i]);
    }
  }

  Iterator<Term*>* createNormalIterator();
  Iterator<Term*>* createBFSIterator();
  Iterator<Term*>* createDFSIterator();

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

  string value() const {
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
    List* l = dynamic_cast<List*>(&term);
    if (v && !v->IsUsed()) {
      v->SetValue(this);
      return true;
    } else if (l) {
      bool isSame = true;
      if(_elements.size() != l->elements()->size())
        isSame = false;
      else {
        for (int i = 0; i < _elements.size(); i++) {
          if (!_elements[i]->match(*(l->elements()->at(i))))
            isSame = false;
        }
      }
      return isSame;
    } else if (term.value() == value())
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

  vector<Term *>* elements() {
    return &_elements;
  }

  Term *head() {
    if (_elements.size() > 0)
      return _elements[0]; 
    else
      throw string("Accessing head in an empty list");
    
  }

  List *tail() {
    if (_elements.size() > 0) {
      vector<Term *> elements = {};
      for (int i = 1; i < _elements.size(); i++)
        elements.push_back(_elements[i]);
      return new List(elements);
    } else 
      throw string("Accessing tail in an empty list");
  }

private:
  vector<Term *> _elements;
};

#endif