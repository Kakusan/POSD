#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>

using std::string;

class Term {
  public:
    Term(string s): _symbol(s) {}
    string symbol() { return _symbol; }
    string value() { return _value; }
    string termName() { return _termName; }
    virtual bool match(Term &term) = 0;
  
  protected:
    string _termName;
    string _symbol;
    string _value;
};

#endif