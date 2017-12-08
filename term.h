#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>

using std::string;

template<class T> 
class Iterator;

class Term {
  public:
    virtual string symbol() const { return _symbol; }
    virtual string value() const { return symbol(); }
    virtual bool match(Term &term) = 0;
    virtual Iterator<Term>* createNormalIterator() = 0;
    virtual Iterator<Term>* createBFSIterator() = 0;
    virtual Iterator<Term>* createDFSIterator() = 0;

  protected:
    Term (): _symbol("") {}
    Term (string s): _symbol(s) {}
    Term (double db) {
      std::ostringstream strs;
      strs << db;
      _symbol = strs.str();
    }
    string _symbol;
};

#endif