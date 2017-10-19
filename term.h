#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>

using std::string;

class Term {
  public:
    Term(string s): _symbol(s) {}
    virtual string symbol() const = 0;
    virtual string value() = 0;
    virtual bool match(Term &term) = 0;
  
  protected:
    string _symbol;
    string _value;
};

#endif