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
    Node(Operators op, Node* l, Node* r):payload(op), term(0), left(l), right(r) {

        std::cout << "我的left是";
        std::cout << left->term;
        std::cout << "喔" << std::endl;
        std::cout << "我的right是";
        std::cout << right->term;
        std::cout << "喔" << std::endl;

    }

    bool evaluate() {

        std::cout << "我的left是";
        std::cout << left->term;
        std::cout << "喔" << std::endl;

        std::cout << "我的right是";
        std::cout << right->term;
        std::cout << "喔" << std::endl;

    }
    
  public:
    Operators payload;
    const Term* term;
    const Node* left;
    const Node* right;
};

#endif