#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "utParser.h"
#include "node.h"

using std::string;

class Parser {
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm() {
    int token = _scanner.nextToken();
    _currentToken = token;
    if (token == VAR) {
      return new Variable(symtable[_scanner.tokenValue()].first);
    } else if (token == NUMBER) {
      return new Number(_scanner.tokenValue());
    } else if (token == ATOM || token == ATOMSC) {
      Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
      if (_scanner.currentChar() == '(') {
        return structure();
      } else
        return atom;
    } else if (token == '[') {
      return list();
    } return nullptr;
  }

  Term* structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if (_currentToken == ')') {
      vector<Term*> args(_terms.begin() + startIndexOfStructArgs, _terms.end());

      for (int i = 0; i < args.size(); i++) {
        for (int j = 0; j < _totalArgs.size() - 1; j++) {
          if(args[i]->symbol() == _totalArgs[j]->symbol())
            args[i] = _totalArgs[j];
        }
      }

      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term* list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if (_currentToken == ']') {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  void matchings() {
    do {
      if (_currentToken == ',') {
        currentOperator = ',';
        _currentToken = '0';
        Node* currentNode = _node;
        matchings();
        Node* nextNode = _node;
        _node = new Node(COMMA, currentNode, nextNode);
      } else if (_currentToken == ';') {
        _totalArgs.clear();
        currentOperator = ';';
        _currentToken = '0';
        Node* currentNode = _node;
        matchings();
        Node* nextNode = _node;
        _node = new Node(SEMICOLON, currentNode, nextNode);
      } else {
        Term* currentTerm = createTerm();
        if (currentTerm != nullptr) {
          currentTerm = searchForSameTerms(currentTerm);
          _totalArgs.push_back(currentTerm);
          _terms.push_back(currentTerm);
          Node *currentNode = new Node(TERM, searchForSameTerms(currentTerm));
          if ((_currentToken = _scanner.nextToken()) == '=') {
            Term* nextTerm = createTerm();    
            nextTerm = searchForSameTerms(nextTerm);
            _totalArgs.push_back(nextTerm);
            _terms.push_back(nextTerm);
            Node *nextNode = new Node(TERM, searchForSameTerms(nextTerm));
            _node = new Node(EQUALITY, currentNode, nextNode);
          }
        }
      }
    } while ((_currentToken = _scanner.nextToken()) == ',' || _currentToken == ';');
  }

  Term* searchForSameTerms(Term* t) {
    for (int i = 0; i < _totalArgs.size(); i++) {
      if(_totalArgs[i]->symbol() == t->symbol())
        t = _totalArgs[i];
    }
    return t;
  }

  Node* expressionTree() {
    return _node;
  }

  vector<Term*>& getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest, ListOfTermsEmpty);
  FRIEND_TEST(ParserTest, listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if (term != nullptr) {
      _terms.push_back(term);
      _totalArgs.push_back(term);
      while ((_currentToken = _scanner.nextToken()) == ',') {
        Term* nextTerm = createTerm();
        _terms.push_back(nextTerm);
        _totalArgs.push_back(nextTerm);
      }
    }
  }

private:
  vector<Term*> _terms;
  vector<Term*> _totalArgs;
  Scanner _scanner;
  int _currentToken;
  int currentOperator;
  Node* _node;

};

#endif