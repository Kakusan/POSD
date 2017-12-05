#ifndef ITERATOR_H
#define ITERATOR_H

#include <typeinfo>
#include "struct.h"
#include "list.h"
#include <vector>

using std::vector;

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T> 
class NormalIterator : public Iterator {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;
  
  void first() { _index = 0; }
  void next() { _index++; }

  Term* currentItem() const { 
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
  NormalIterator(T *t): _index(0), _t(t) {}
  int _index;
  T* _t;
};

template<class T> 
class BFSIterator : public Iterator {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;

  void first() { _index = 0; }
  void next() { 
    _index++; 
    Iterator it = currentItem().createBFSIterator()
    if(!it.isDone())
      _itList.push_back(currentItem().createBFSIterator());
  }

  Term* currentItem() const { 
    Struct* s = dynamic_cast<Struct*>(_t);
    List* l = dynamic_cast<List*>(_t);
    if (s) {
      if(s->args(_index))
      return s->args(_index);
    }
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
  BFSIterator(T *t): _index(0), _t(t) {}
  int _index;
  T* _t;
  vector<Iterator*> _itList;
  int _itListIndex = 0;
};

template<class T> 
class DFSIterator : public Iterator {
public:
  friend class Atom;
  friend class Number;  
  friend class Variable;
  friend class Struct;
  friend class List;
  
  void first() { _index = 0; }
  void next() { _index++; }

  Term* currentItem() const { 
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
  DFSIterator(T *t): _index(0), _t(t) {}
  int _index;
  T* _t;
};

#endif