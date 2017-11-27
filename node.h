#ifndef NODE_H
#define NODE_H

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
  public:
    Node(Operators op, Term* t):payload(op), term(t), left(0), right(0) {}
    Node(Operators op, Node* l, Node* r):payload(op), term(0), left(l), right(r) {}

    bool evaluate() {
      if (payload == EQUALITY) {
        std::cout << payload;
      }
    }
    
  public:
    Operators payload;
    Term* term;
    Node* left;
    Node* right;
};

#endif