#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
using std::string;

class Term {
  public:
    Term(string s): _symbol(s) {}
    Term(int i) { _symbol = i + ""; }
    string symbol() { return _symbol; }
    string value() { return _value; }
    virtual bool match(Term &term) = 0;
  
  protected:
    string const _symbol;
    string _value;
};

#endif