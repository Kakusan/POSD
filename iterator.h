#ifndef ITERATOR_H
#define ITERATOR_H

#include <typeinfo>
#include "struct.h"
#include "list.h"
#include <vector>

using std::vector;

template<class T> 
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T> 
class NormalIterator : public Iterator<T> {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;
  
  void first() { _index = 0; }
  void next() { _index++; }

  T currentItem() const { 
    Struct* s = dynamic_cast<Struct*>(_t);
    List* l = dynamic_cast<List*>(_t);
    if (s)
      return s->args(_index);
    else if (l)
      return l->elements()->at(_index);
    else 
      return nullptr;
  }

  bool isDone() const { 
    Struct* s = dynamic_cast<Struct*>(_t);
    List* l = dynamic_cast<List*>(_t);
    if (s)
      return _index >= s->arity();
    else if (l)
      return _index >= l->elements()->size();
    else 
      return true;
   }

private:
  NormalIterator(T t): _index(0), _t(t) {}
  int _index;
  T _t;
};

template<class T> 
class BFSIterator : public Iterator<T> {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;

  void first() { 
    _index = 0; 

    Struct* s = dynamic_cast<Struct*>(_t);
    List* l = dynamic_cast<List*>(_t);
    vector<T> terms;
    if (s) {
      for (int i = 0; i < s->arity(); i++)
        terms.push_back(s->args(i));
    } else if (l) {
      for (int j = 0; j < l->elements()->size(); j++)
        terms.push_back(l->elements()->at(j));
    }
    _totalTerms = makeBFSTree(terms);
  
    // std::cout << "走訪順序為[ ";
    // for(int i = 0; i < _totalTerms.size() - 1; i++)
    //   std::cout << dynamic_cast<Term*>(_totalTerms[i])->symbol() << ", ";
    // std::cout << dynamic_cast<Term*>(_totalTerms[_totalTerms.size()-1])->symbol() << " ]喔" << std::endl;
  }

  void next() { _index++; }
  T currentItem() const { return _totalTerms[_index]; }
  bool isDone() const { return _index >= _totalTerms.size(); }

private:
  BFSIterator(T t): _index(0), _t(t) {}
  vector<T> makeBFSTree(vector<T> _inputTerms) {
    vector<T> outputTerms;
    vector<T> subTerms;

    for (T t : _inputTerms) {
      Struct* s = dynamic_cast<Struct*>(t);
      List* l = dynamic_cast<List*>(t);
      if (s) {
        outputTerms.push_back(new Atom(s->name().symbol()));
        for (int i = 0; i < s->arity(); i++)
          subTerms.push_back(s->args(i));
      } else if (l) {
        outputTerms.push_back(new List);
        for (int j = 0; j < l->elements()->size(); j++)
          subTerms.push_back(l->elements()->at(j));
      } else {
        outputTerms.push_back(t);
      }
    }
    if (subTerms.size() > 0) {
      vector<T> childrenTerms = makeBFSTree(subTerms);
      outputTerms.insert(outputTerms.end(), childrenTerms.begin(), childrenTerms.end());
    }
    return outputTerms;

  }
  int _index;
  T _t;
  vector<T> _totalTerms;
};

template<class T> 
class DFSIterator : public Iterator<T> {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;

  void first() { 
    _index = 0; 

    Struct* s = dynamic_cast<Struct*>(_t);
    List* l = dynamic_cast<List*>(_t);
    vector<T> terms;
    if (s) {
      for (int i = 0; i < s->arity(); i++)
        terms.push_back(s->args(i));
    } else if (l) {
      for (int j = 0; j < l->elements()->size(); j++)
        terms.push_back(l->elements()->at(j));
    }
    _totalTerms = makeDFSTree(terms);
  
    std::cout << "走訪順序為[ ";
    for(int i = 0; i < _totalTerms.size() - 1; i++)
      std::cout << dynamic_cast<Term*>(_totalTerms[i])->symbol() << ", ";
    std::cout << dynamic_cast<Term*>(_totalTerms[_totalTerms.size()-1])->symbol() << " ]喔" << std::endl;
  }

  void next() { _index++; }
  T currentItem() const { return _totalTerms[_index]; }
  bool isDone() const { return _index >= _totalTerms.size(); }

private:
  DFSIterator(T t): _index(0), _t(t) {}
  vector<T> makeDFSTree(vector<T> _inputTerms) {
    vector<T> outputTerms;
    vector<T> subTerms;

    for (T t : _inputTerms) {
      Struct* s = dynamic_cast<Struct*>(t);
      List* l = dynamic_cast<List*>(t);
      if (s) {
        outputTerms.push_back(new Atom(s->name().symbol()));
        for (int i = 0; i < s->arity(); i++)
          subTerms.push_back(s->args(i));
        vector<T> childrenTerms = makeDFSTree(subTerms);
        subTerms.clear();
        outputTerms.insert(outputTerms.end(), childrenTerms.begin(), childrenTerms.end());
      } else if (l) {
        outputTerms.push_back(new List);
        for (int j = 0; j < l->elements()->size(); j++)
          subTerms.push_back(l->elements()->at(j));
        vector<T> childrenTerms = makeDFSTree(subTerms);
        subTerms.clear();
        outputTerms.insert(outputTerms.end(), childrenTerms.begin(), childrenTerms.end());
      } else {
        outputTerms.push_back(t);
      }
    }
    return outputTerms;
  }

  int _index;
  T _t;
  vector<T> _totalTerms;
};

#endif