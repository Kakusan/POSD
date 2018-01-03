#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

#include "atom.h"

class Expression {
public:
  virtual bool evaluate() = 0;
  virtual string getExpression() = 0;
};


class MatchExpression : public Expression {
public:
  MatchExpression(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate() {
    return _left->match(*_right);
  }

  string getExpression() {

      return _right->value();

  }

private:
  Term* _left;
  Term* _right;
};

class ConjExpression : public Expression {
public:
  ConjExpression(Expression *left, Expression *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getExpression() {
    return "ConjExpression";
  }


private:
  Expression * _left;
  Expression * _right;
};

class DisjExpression : public Expression {
public:
  DisjExpression(Expression *left, Expression *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  string getExpression() {
    return "DisjExpression";
  }

private:
  Expression * _left;
  Expression * _right;
};

#endif