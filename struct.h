#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct : public Term
{
public:
  Struct(Atom const &name, std::vector<Term *> args):Term(name.symbol()), _name(name), _args(args) {
  }

  Term* args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }

  string symbol() const {
    string output =_name.symbol() + "(";
    for (int i = 0; i < _args.size() - 1 ; i++){
        output += _args[i]->symbol() + ", ";
    }
    output += _args[_args.size()-1]-> symbol() + ")";
    return output;
  }

  string value() {
    string output =_name.value() + "(";
    for (int i = 0; i < _args.size() - 1 ; i++){
        output += _args[i]->value() + ", ";
    }
    output += _args[_args.size()-1]-> value() + ")";
    return output;
  }

  bool match(Term &term) {
    Struct * ps = dynamic_cast<Struct *>(&term);
    Variable* v = dynamic_cast<Variable*>(&term);
    bool isSame = true;
    if (ps && _name.match(ps->_name) && _args.size() == ps->_args.size()) {
        for (int i = 0; i < _args.size(); i++) {
            if (_args[i]->symbol() != ps->_args[i]->symbol())
                isSame = false;
        }
    } else if (v && !v->IsUsed()) {
      v->SetValue(this);
      return true;
    } else
      isSame = false;
    return isSame;
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif